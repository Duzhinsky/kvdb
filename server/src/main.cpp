#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <csignal>

#include "server_msg.h"

static void do_something(int connfd) {
    char rbuf[64] = {};
    ssize_t n = read(connfd, rbuf, sizeof(rbuf) - 1);
    if (n < 0) {
        server::io::msg("read() error");
        return;
    }
    printf("client says: %s\n", rbuf);

    char wbuf[] = "Hello from C";
    write(connfd, wbuf, strlen(wbuf));
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
        server::io::die("bind()");
    }

    rv = listen(fd, SOMAXCONN);
    if (rv) {
        server::io::die("listen()");
    }
    return fd;
}

int main() {
    int fd = init_socket();
    while (true) {
        // accept
        struct sockaddr_in client_addr = {};
        socklen_t addrlen = sizeof(client_addr);
        int connfd = accept(fd, (struct sockaddr *)&client_addr, &addrlen);
        if (connfd < 0) {
            continue;
        }

        do_something(connfd);
        close(connfd);
    }
    return 0;
}
