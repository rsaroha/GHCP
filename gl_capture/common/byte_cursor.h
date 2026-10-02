#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>

// Sequential reader over a decoded call's raw argument bytes.
struct ByteCursor {
    const uint8_t* p;
    size_t remaining;

    template <typename T>
    T Read() {
        T v{};
        memcpy(&v, p, sizeof(T));
        p += sizeof(T);
        remaining -= sizeof(T);
        return v;
    }

    // Returns a pointer into the underlying buffer and advances past it;
    // the caller must copy out anything it needs to keep past this call's
    // lifetime.
    const uint8_t* ReadBytes(size_t n) {
        const uint8_t* start = p;
        p += n;
        remaining -= n;
        return start;
    }
};
