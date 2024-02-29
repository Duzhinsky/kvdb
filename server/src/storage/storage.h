#ifndef KVDB_STORAGE_H
#define KVDB_STORAGE_H

#include <memory>
#include <string>
#include <unordered_map>
#include <optional>

class storage {
public:
    storage();

    ~storage();

    void put(const std::string &key, std::string value);

    std::optional<std::string> get(const std::string &key);

private:
    std::unordered_map<std::string, std::string> hashmap;
};


#endif //KVDB_STORAGE_H
