#ifndef KVDB_CONNECTION_H
#define KVDB_CONNECTION_H

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <utility>
#include "cmd/CommandManager.hpp"

class connection {
    struct hide_me {
    };
public:
    typedef std::shared_ptr<connection> pointer;

    connection(boost::asio::io_service &io_service, std::shared_ptr<CommandManager> command_manager, hide_me);

    class Factory {
    public:
        Factory(boost::asio::io_service &io_service, std::shared_ptr<CommandManager> command_manager)
                : io_service(io_service), command_manager(std::move(command_manager)) {
        }

        pointer create() {
            return std::make_shared<connection>(std::ref(io_service), command_manager, hide_me());
        }

    private:
        boost::asio::io_service &io_service;
        std::shared_ptr<CommandManager> command_manager;
    };

    boost::asio::ip::tcp::socket &socket() {
        return socket_;
    }

    void run();

private:
    boost::asio::ip::tcp::socket socket_;
    boost::asio::streambuf buf;
    std::shared_ptr<CommandManager> command_manager;
};


#endif //KVDB_CONNECTION_H
