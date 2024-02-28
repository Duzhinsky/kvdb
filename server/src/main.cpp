#include <boost/asio.hpp>
#include <spdlog/spdlog.h>

#include "server.h"
#include "cmd/GetCommand.hpp"
#include "cmd/PutCommand.hpp"

int main() {
    spdlog::set_level(spdlog::level::trace);
    try {
        boost::asio::io_service io_service;

        std::shared_ptr<CommandManager> commandManager = std::make_shared<CommandManager>();
        std::unique_ptr<CommandProcessor> cmds[] = {
                std::make_unique<GetCommand>(),
                std::make_unique<PutCommand>()
        };
        for (std::unique_ptr<CommandProcessor> &cmd: cmds)
            commandManager->reg_command(std::move(cmd));

        std::shared_ptr<connection::Factory> connectionFactory
                = std::make_shared<connection::Factory>(io_service, commandManager);

        server s(io_service, connectionFactory, 1234);
        io_service.run();
    } catch (std::exception &e) {
        spdlog::error("Failed to create the server. Message: {}", e.what());
    }
    return 0;
}
