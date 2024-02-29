#include "storage.h"

#include <utility>

storage::storage() = default;

storage::~storage() = default;

void storage::put(const std::string &key, std::string value) {
    hashmap[key] = std::move(value);
}

std::optional<std::string> storage::get(const std::string &key) {
    auto it = hashmap.find(key);
    if (it == hashmap.end())
        return std::nullopt;
    return { it->second };
}

