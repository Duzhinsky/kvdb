#ifndef KVDB_COMMANDPROCESSOR_H
#define KVDB_COMMANDPROCESSOR_H

#include <string>
#include <utility>

class CommandProcessor {
public:
    explicit CommandProcessor(std::string name) : name_(std::move(name)) {}
    virtual ~CommandProcessor() = default;

    std::string name() {
        return name_;
    }
    virtual void execute(const std::string &data) = 0;

private:
    std::string name_;
};

#endif //KVDB_COMMANDPROCESSOR_H
