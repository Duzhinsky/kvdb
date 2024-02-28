#ifndef KVDB_GETCOMMAND_HPP
#define KVDB_GETCOMMAND_HPP

#include <string>
#include <spdlog/spdlog.h>

#include "CommandProcessor.h"

class GetCommand : public CommandProcessor {
public:
    GetCommand() : CommandProcessor("get") {}

    void execute(const std::string &data) override {
        spdlog::info("Get {}", data);
    }
};

#endif // KVDB_GETCOMMAND_HPP