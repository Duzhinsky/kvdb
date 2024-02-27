#ifndef KVDB_SERVER_H
#define KVDB_SERVER_H

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>

#include "connection.h"

class server : private boost::noncopyable {
public:
    explicit server(boost::asio::io_service& io_service, int port=1234);

private:
    void handle_accept(const boost::system::error_code& e);

    boost::asio::io_service& io_service;
    boost::asio::ip::tcp::acceptor acceptor;
    connection::pointer new_connection;
};


#endif //KVDB_SERVER_H
