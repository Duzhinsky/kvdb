#ifndef KVDB_SERVER_MSH_H
#define KVDB_SERVER_MSH_H

namespace server::io {
    void msg(const char *msg);
    void die(const char *msg);
}

#endif
