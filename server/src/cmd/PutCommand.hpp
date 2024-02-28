#ifndef KVDB_PUTCOMMAND_HPP
#define KVDB_PUTCOMMAND_HPP


#include "CommandProcessor.h"
#include "spdlog/spdlog.h"

class PutCommand : public CommandProcessor {
public:
    PutCommand() : CommandProcessor("put") {}

    void execute(const std::string &data) override {
        spdlog::info("Put {}", data);
    }
};


#endif //KVDB_PUTCOMMAND_HPP
