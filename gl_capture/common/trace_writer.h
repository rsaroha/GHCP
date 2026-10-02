#pragma once
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <mutex>
#include <vector>

#include "gl_ids.h"
#include "trace_format.h"
#include "typed_trace.h"

// Buffers one GL call's serialized arguments before it's flushed to the
// trace file. Not thread-safe on its own; TraceWriter::EndCall() takes a
// lock when it writes out.
struct TraceCall {
    GLFuncId id;
    std::vector<uint8_t> data;
    uint16_t typedArgumentCount = 0;
    bool typed = false;
};

class TraceWriter {
public:
    bool Open(const char* path) {
        std::lock_guard<std::mutex> lock(mu_);
        f_ = fopen(path, "wb");
        if (!f_) return false;
        // Unbuffered: the traced process can crash at any point (that's
        // often exactly why someone's capturing a trace), and losing
        // whatever sat in a full stdio buffer at that moment is the worst
        // possible place to lose data. Every call is written straight
        // through instead.
        setvbuf(f_, nullptr, _IONBF, 0);
        fwrite(tracefmt::kMagic, 1, sizeof(tracefmt::kMagic), f_);
        return true;
    }

    void Close() {
        std::lock_guard<std::mutex> lock(mu_);
        if (f_) { fflush(f_); fclose(f_); f_ = nullptr; }
    }

    TraceCall BeginCall(GLFuncId id) {
        TraceCall c;
        c.id = id;
        return c;
    }

    void ConfigureCaptureMode(const char* mode) {
        std::lock_guard<std::mutex> lock(mu_);
        bool oneFrame = false;
        if (mode) {
#ifdef _WIN32
            oneFrame = (_stricmp(mode, "oneframe") == 0) || (_stricmp(mode, "one_frame") == 0);
#else
            oneFrame = (strcmp(mode, "oneframe") == 0) || (strcmp(mode, "one_frame") == 0);
#endif
        }
        captureAll_ = !oneFrame;
        frameArmed_ = false;
        capturingFrame_ = false;
    }

    bool IsOneFrameMode() const {
        std::lock_guard<std::mutex> lock(mu_);
        return !captureAll_;
    }

    void ArmOneFrame() {
        std::lock_guard<std::mutex> lock(mu_);
        if (!captureAll_) frameArmed_ = true;
    }

    TraceCall BeginTypedCall(GLFuncId id, uint16_t argumentCount) {
        TraceCall c;
        c.id = id;
        c.typed = true;
        c.typedArgumentCount = argumentCount;
        return c;
    }

    template <typename T>
    void WriteVal(TraceCall& c, T v) {
        size_t off = c.data.size();
        c.data.resize(off + sizeof(T));
        memcpy(c.data.data() + off, &v, sizeof(T));
    }

    void WriteBlob(TraceCall& c, const void* p, size_t n) {
        if (n == 0) return;
        size_t off = c.data.size();
        c.data.resize(off + n);
        memcpy(c.data.data() + off, p, n);
    }

    void EndCall(TraceCall& c) {
        std::lock_guard<std::mutex> lock(mu_);
        if (!f_) return;
        if (!captureAll_ && !capturingFrame_) {
            if (!frameArmed_) return;
            frameArmed_ = false;
            capturingFrame_ = true;
        }

        if (c.typed) {
            tracefmt::TypedCallHeader typedHeader{
                tracefmt::kTypedSchemaVersion,
                c.typedArgumentCount,
                static_cast<uint32_t>(c.data.size())};
            std::vector<uint8_t> payload(sizeof(typedHeader) + c.data.size());
            memcpy(payload.data(), &typedHeader, sizeof(typedHeader));
            if (!c.data.empty()) memcpy(payload.data() + sizeof(typedHeader), c.data.data(), c.data.size());
            WriteRecordUnlocked(c.id, tracefmt::kTypedRecordFlag, payload.data(), payload.size());
            return;
        }
        WriteRecordUnlocked(c.id, 0, c.data.data(), c.data.size());
    }

    void MarkFrameEnd() {
        std::lock_guard<std::mutex> lock(mu_);
        if (!f_) return;
        if (!captureAll_ && !capturingFrame_) return;
        tracefmt::RecordHeader hdr{tracefmt::kFrameEndMarker, 0, 0};
        fwrite(&hdr, sizeof(hdr), 1, f_);
        fflush(f_); // frame boundaries are a good point to make partial traces recoverable
        if (!captureAll_) capturingFrame_ = false;
    }

private:
    void WriteRecordUnlocked(GLFuncId id, uint16_t flags, const void* data, size_t size) {
        if (!f_) return;
        if (size > 0xFFFFFFFFu) return; // absurd, drop rather than corrupt the file
        tracefmt::RecordHeader hdr{static_cast<uint16_t>(id), flags, static_cast<uint32_t>(size)};
        fwrite(&hdr, sizeof(hdr), 1, f_);
        if (size != 0) fwrite(data, 1, size, f_);
    }

    void WriteRecord(GLFuncId id, uint16_t flags, const void* data, size_t size) {
        if (size > 0xFFFFFFFFu) return; // absurd, drop rather than corrupt the file
        std::lock_guard<std::mutex> lock(mu_);
        WriteRecordUnlocked(id, flags, data, size);
    }

    mutable std::mutex mu_;
    FILE* f_ = nullptr;
    bool captureAll_ = true;
    bool frameArmed_ = false;
    bool capturingFrame_ = false;
};
