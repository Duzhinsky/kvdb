#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <csignal>
#include <spdlog/spdlog.h>
#include "spdlog/fmt/ostr.h" // must be included


static void respond(const int& conn_fd, const char *&&buf) {
    spdlog::trace("Sending \"{}\" to connection {}", buf, conn_fd);
    write(conn_fd, buf, strlen(buf));
}

static ssize_t read_to(const int& conn_fd, char *buffer, const int buffer_len) {
    ssize_t n = read(conn_fd, buffer, buffer_len);
    spdlog::trace("Received \"{}\" from connection {}", buffer, conn_fd);
    return n;
}

static void do_something(const int& conn_fd) {
    char read_buffer[64] = {};
    ssize_t n = read_to(conn_fd, read_buffer, sizeof(read_buffer) - 1);
    if (n < 0) {
        spdlog::error("Error during reading a connection");
        return;
    }
    spdlog::info("Client says: {}", read_buffer);
    respond(conn_fd, "Hello from C");
}

static int init_socket() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    struct sockaddr_in addr = {
            .sin_family = AF_INET,
            .sin_port = ntohs(1234),
            .sin_addr {
                    .s_addr = ntohl(0)
            }
    };
    int rv = bind(fd, (const sockaddr *) &addr, sizeof(addr));
    if (rv) {
        spdlog::critical("Cannot bind a socket!");
        abort();
    }

    rv = listen(fd, SOMAXCONN);
    if (rv) {
        spdlog::critical("Cannot listen a socket!");
        abort();
    }
    return fd;
}

int main() {
    spdlog::set_level(spdlog::level::trace);
    int fd = init_socket();
    spdlog::info("Server has started and ready to accept connections");
    while (true) {
        // accept
        struct sockaddr_in client_addr = {};
        socklen_t addrlen = sizeof(client_addr);
        int conn_fd = accept(fd, (struct sockaddr *) &client_addr, &addrlen);
        if (conn_fd < 0) {
            continue;
        }

        do_something(conn_fd);
        close(conn_fd);
    }
    return 0;
}
