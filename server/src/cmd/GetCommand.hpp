#ifndef KVDB_GETCOMMAND_HPP
#define KVDB_GETCOMMAND_HPP

#include <string>
#include <spdlog/spdlog.h>

#include "CommandProcessor.h"
#include "../storage/storage.h"

class GetCommand : public CommandProcessor {
public:
    explicit GetCommand(std::shared_ptr<storage> data_storage) : CommandProcessor("get"), data_storage(std::move(data_storage)) {}

    void execute(const std::string &data) override {
        std::optional<std::string> found_value = data_storage->get(data);
        if (found_value.has_value()) {
            spdlog::info("Found {} for key {}", found_value.value(), data);
        } else {
            spdlog::info("Not found a value for key {}", data);
        }
    }

private:
    std::shared_ptr<storage> data_storage;
};

#endif // KVDB_GETCOMMAND_HPP