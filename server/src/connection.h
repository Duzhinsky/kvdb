#ifndef KVDB_CONNECTION_H
#define KVDB_CONNECTION_H

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>

class connection {
    struct hide_me {};
public:
    typedef std::shared_ptr<connection> pointer;

    connection(boost::asio::io_service& io_service, hide_me);

    static pointer create(boost::asio::io_service& io_service) {
        return std::make_shared<connection>(std::ref(io_service), hide_me());
    }

    boost::asio::ip::tcp::socket& socket() {
        return socket_;
    }

    void run();

private:
    boost::asio::io_service& io_service;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf buf;
};


#endif //KVDB_CONNECTION_H
