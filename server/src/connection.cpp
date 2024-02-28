#include "connection.h"

#include <spdlog/spdlog.h>
#include <boost/regex.hpp>
#include <utility>

connection::connection(boost::asio::io_service &io_service,
                       std::shared_ptr<CommandManager> command_manager,
                       connection::hide_me) :
        socket_(io_service), command_manager(std::move(command_manager)) {
}

void connection::run() {
    try {
        boost::asio::read(socket_, buf, boost::asio::transfer_exactly(3));
        std::string buf_str(boost::asio::buffers_begin(buf.data()),
                            boost::asio::buffers_begin(buf.data()) + buf.size());
        spdlog::trace("Received \"{}\" from a connection {}", buf_str, socket_.remote_endpoint().address().to_string());
        command_manager->process(buf_str, ""); // tmp for tests
        boost::asio::write(
                socket_,
                boost::asio::buffer("Hello from C++"),
                boost::asio::transfer_all()
        );
        socket_.close();
    } catch (std::exception &x) {
        spdlog::error("Error during processing a connection: {}", x.what());
    }
}
