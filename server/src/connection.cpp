#include "connection.h"

#include <spdlog/spdlog.h>
#include <boost/regex.hpp>

connection::connection(boost::asio::io_service &io_service, connection::hide_me) :
        io_service(io_service), socket_(io_service) {
}

void connection::run() {
    try {
        boost::asio::read_until(socket_, buf, boost::regex("\r\n"));
        std::string buf_str(boost::asio::buffers_begin(buf.data()),
                            boost::asio::buffers_begin(buf.data()) + buf.size());
        spdlog::trace("Received \"{}\" from a connection {}", buf_str, socket_.remote_endpoint().address().to_string());
        boost::asio::write(socket_, boost::asio::buffer("Hello from C++"), boost::asio::transfer_all());
        socket_.close();
    } catch (std::exception &x) {
        spdlog::error("Error during processing a connection: {}", x.what());
    }
}
