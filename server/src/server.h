#ifndef KVDB_SERVER_H
#define KVDB_SERVER_H

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>

#include "connection.h"
#include "cmd/CommandManager.hpp"

class server : private boost::noncopyable {
public:
    explicit server(boost::asio::io_service& io_service, std::shared_ptr<connection::Factory> connection_factory, int port=1234);

private:
    void handle_accept(const boost::system::error_code &e);

    boost::asio::io_service &io_service;
    boost::asio::ip::tcp::acceptor acceptor;
    connection::pointer new_connection;
    std::shared_ptr<connection::Factory> connection_factory;
};


#endif //KVDB_SERVER_H
