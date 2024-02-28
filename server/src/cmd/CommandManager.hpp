#ifndef KVDB_COMMANDMANAGER_HPP
#define KVDB_COMMANDMANAGER_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include <spdlog/spdlog.h>

#include "CommandProcessor.h"

class CommandManager {
public:

    void process(const std::string &cmd_name, const std::string &args) {
        std::unique_ptr<CommandProcessor> &proc = commands[cmd_name];
        if (proc) {
            proc->execute(args);
        } else {
            spdlog::warn("Received unknown command '{}'", cmd_name);
        }
    }

    void reg_command(std::unique_ptr<CommandProcessor> processor) {
        commands[processor->name()] = std::move(processor);
    }

private:
    std::unordered_map<std::string, std::unique_ptr<CommandProcessor>> commands;
};


#endif //KVDB_COMMANDMANAGER_HPP
