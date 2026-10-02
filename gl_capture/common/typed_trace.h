#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

namespace tracefmt {

// Versioned payload format used by registry-generated handlers. The legacy
// GLCAP001 records remain byte-compatible; typed records carry enough
// metadata for replay to distinguish scalars, object names, strings, and
// pointer data without relying on a hand-maintained decoder.
constexpr uint16_t kTypedSchemaVersion = 1;

enum class ValueKind : uint8_t {
    Scalar = 1,
    ObjectId = 2,
    InputBytes = 3,
    OutputBytes = 4,
    InOutBytes = 5,
    String = 6,
    ReturnValue = 7,
};

#pragma pack(push, 1)
struct TypedCallHeader {
    uint16_t schema_version;
    uint16_t argument_count;
    uint32_t payload_size;
};

struct TypedValueHeader {
    uint8_t kind;
    uint8_t flags;
    uint16_t type_id;
    uint32_t byte_length;
};
#pragma pack(pop)

class TypedCallBuilder {
public:
    explicit TypedCallBuilder(uint16_t argumentCount)
        : argumentCount_(argumentCount) {}

    template <typename T>
    void Scalar(uint16_t typeId, T value) {
        Add(ValueKind::Scalar, typeId, &value, sizeof(value));
    }

    void ObjectId(uint16_t typeId, uint32_t value) {
        Add(ValueKind::ObjectId, typeId, &value, sizeof(value));
    }

    void Bytes(ValueKind kind, uint16_t typeId, const void* data, size_t size) {
        Add(kind, typeId, data, size);
    }

    void String(uint16_t typeId, const char* value, size_t size) {
        Add(ValueKind::String, typeId, value, size);
    }

    const std::vector<uint8_t>& Data() const { return data_; }
    uint16_t ArgumentCount() const { return argumentCount_; }

private:
    void Add(ValueKind kind, uint16_t typeId, const void* data, size_t size) {
        if (size > 0xFFFFFFFFu || data_.size() > 0xFFFFFFFFu - sizeof(TypedValueHeader) - size) {
            return;
        }
        TypedValueHeader header{
            static_cast<uint8_t>(kind), 0, typeId, static_cast<uint32_t>(size)};
        const auto oldSize = data_.size();
        data_.resize(oldSize + sizeof(header) + size);
        std::memcpy(data_.data() + oldSize, &header, sizeof(header));
        if (size != 0 && data != nullptr) {
            std::memcpy(data_.data() + oldSize + sizeof(header), data, size);
        }
    }

    uint16_t argumentCount_;
    std::vector<uint8_t> data_;
};

} // namespace tracefmt
