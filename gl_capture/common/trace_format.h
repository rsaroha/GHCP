#pragma once
#include <cstdint>

// On-disk trace format. Shared between the interceptor (writer) and the
// replay tool (reader).
//
//   [8 bytes]  magic "GLCAP001"
//   records...
//
// Each record:
//   uint16_t func_id      (GLFuncId value, or kFrameEndMarker)
//   uint16_t reserved
//   uint32_t data_len
//   uint8_t  data[data_len]

namespace tracefmt {

constexpr char kMagic[8] = {'G', 'L', 'C', 'A', 'P', '0', '0', '1'};
constexpr uint16_t kFrameEndMarker = 0xFFFF;
constexpr uint16_t kTypedRecordFlag = 0x0001;

struct RecordHeader {
    uint16_t func_id;
    uint16_t reserved;
    uint32_t data_len;
};

} // namespace tracefmt
