#include "server_msg.h"

namespace server::io {
    void msg(const char *msg) {
        fprintf(stderr, "%s\n", msg);
    }

    void die(const char *msg) {
        int err = errno;
        fprintf(stderr, "[%d] %s\n", err, msg);
        abort();
    }
}