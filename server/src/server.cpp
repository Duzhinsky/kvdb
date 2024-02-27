#include "server.h"

#include <boost/thread.hpp>
#include <spdlog/spdlog.h>

server::server(boost::asio::io_service &io_service, int port) :
        io_service(io_service),
        acceptor(
                io_service,
                boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)
        ),
        new_connection(connection::create(io_service)) {
    acceptor.async_accept(
            new_connection->socket(),
            [this](const boost::system::error_code &e) {
                handle_accept(e);
            }
    );
    spdlog::info("Server is ready to accept connections!");
}

void server::handle_accept(const boost::system::error_code &e) {
    if (e) {
        spdlog::error("Error accepting a connection: {}", e.message());
        return;
    }

    boost::thread t([](const connection::pointer& conn) {
        conn->run();
    }, new_connection);
    new_connection = connection::create(io_service);
    acceptor.async_accept(
            new_connection->socket(),
            [this](const boost::system::error_code &e) {
                handle_accept(e);
            }
    );
}
