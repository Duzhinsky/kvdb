#include "connection.h"

#include <spdlog/spdlog.h>
#include <utility>

connection::connection(boost::asio::io_service &io_service,
                       std::shared_ptr<CommandManager> command_manager,
                       connection::hide_me) :
        socket_(io_service), command_manager(std::move(command_manager)) {
}

void connection::run() {
    try {
        // Read length of command
        uint8_t cmd_len;
        boost::system::error_code ec;
        boost::asio::read(socket_, boost::asio::buffer(&cmd_len, 1), ec);

        // Read command
        boost::asio::streambuf cmd_buf;
        boost::asio::read(socket_, cmd_buf, boost::asio::transfer_exactly(cmd_len), ec);
        std::string cmd(
                boost::asio::buffers_begin(cmd_buf.data()),
                boost::asio::buffers_begin(cmd_buf.data()) + cmd_buf.size()
        );

        // Read length of arguments
        uint8_t arg_len;
        boost::asio::read(socket_, boost::asio::buffer(&arg_len, 1), ec);

        // Read arguments
        boost::asio::streambuf args_buf;
        boost::asio::read(socket_, args_buf, boost::asio::transfer_exactly(arg_len), ec);
        std::string args(
                boost::asio::buffers_begin(args_buf.data()),
                boost::asio::buffers_begin(args_buf.data()) + args_buf.size()
        );

        command_manager->process(cmd, args); // tmp for tests
        boost::asio::write(
                socket_,
                boost::asio::buffer("OK"),
                boost::asio::transfer_all()
        );
        socket_.close();
    } catch (std::exception &x) {
        spdlog::error("Error during processing a connection: {}", x.what());
    }
}
