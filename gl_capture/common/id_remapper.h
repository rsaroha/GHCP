#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>

// Object names (buffer/texture/program/... ids) captured from the traced
// app won't match the ids the replay tool's driver hands out when it
// re-issues glGen*/glCreate* calls. IdRemapper tracks captured-id ->
// replay-id per object namespace so later calls that reference an id can
// be translated. Id 0 always means "none/default" in GL and is never
// remapped.
class IdRemapper {
public:
    void Map(const std::string& ns, uint32_t capturedId, uint32_t realId) {
        if (capturedId == 0) return;
        table_[ns][capturedId] = realId;
    }

    uint32_t Get(const std::string& ns, uint32_t capturedId) const {
        if (capturedId == 0) return 0;
        auto it = table_.find(ns);
        if (it == table_.end()) return capturedId;
        auto it2 = it->second.find(capturedId);
        return it2 == it->second.end() ? capturedId : it2->second;
    }

    bool Has(const std::string& ns, uint32_t capturedId) const {
        if (capturedId == 0) return true;
        auto it = table_.find(ns);
        if (it == table_.end()) return false;
        return it->second.find(capturedId) != it->second.end();
    }

    // Drops a mapping, e.g. once the corresponding glDelete* call replays --
    // otherwise a resource inspector enumerating this namespace would keep
    // listing objects that no longer exist.
    void Unmap(const std::string& ns, uint32_t capturedId) {
        auto it = table_.find(ns);
        if (it == table_.end()) return;
        it->second.erase(capturedId);
    }

    // All live (capturedId -> realId) mappings in a namespace, for
    // enumerating "every buffer/texture/... known so far" -- e.g. to drive
    // a resource inspector. Empty if the namespace has no entries.
    const std::unordered_map<uint32_t, uint32_t>& All(const std::string& ns) const {
        auto it = table_.find(ns);
        if (it == table_.end()) {
            static const std::unordered_map<uint32_t, uint32_t> kEmpty;
            return kEmpty;
        }
        return it->second;
    }

private:
    std::unordered_map<std::string, std::unordered_map<uint32_t, uint32_t>> table_;
};
