#include <boost/asio.hpp>
#include <spdlog/spdlog.h>

#include "server.h"

int main() {
    spdlog::set_level(spdlog::level::trace);
    try {
        boost::asio::io_service io_service;
        server s(io_service, 1234);
        io_service.run();
    } catch (std::exception& e) {
        spdlog::error("Failed to create the server. Message: {}", e.what());
    }
    return 0;
}
