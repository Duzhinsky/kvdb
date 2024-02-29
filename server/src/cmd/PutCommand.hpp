#ifndef KVDB_PUTCOMMAND_HPP
#define KVDB_PUTCOMMAND_HPP


#include "CommandProcessor.h"
#include "spdlog/spdlog.h"
#include "../storage/storage.h"

class PutCommand : public CommandProcessor {
public:
    explicit PutCommand(std::shared_ptr<storage> data_storage) : CommandProcessor("put"), data_storage(std::move(data_storage)) {}

    void execute(const std::string &data) override {
        size_t delim = data.find(' ');
        std::string key = data.substr(0, delim);
        std::string value = data.substr(delim + 1);
        spdlog::info("Put {} to {}", value, key);
        data_storage->put(key, value);
    }

private:
    std::shared_ptr<storage> data_storage;
};


#endif //KVDB_PUTCOMMAND_HPP
