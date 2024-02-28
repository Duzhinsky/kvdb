#include "server.h"

#include <boost/thread.hpp>
#include <utility>
#include <spdlog/spdlog.h>

server::server(boost::asio::io_service &io_service, std::shared_ptr<connection::Factory> connection_factory, int port) :
        io_service(io_service),
        acceptor(
                io_service,
                boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)
        ),
        new_connection(connection_factory->create()),
        connection_factory(std::move(connection_factory)) {
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

    boost::thread t([](const connection::pointer &conn) {
        conn->run();
    }, new_connection);
    new_connection = connection_factory->create();
    acceptor.async_accept(
            new_connection->socket(),
            [this](const boost::system::error_code &e) {
                handle_accept(e);
            }
    );
}
