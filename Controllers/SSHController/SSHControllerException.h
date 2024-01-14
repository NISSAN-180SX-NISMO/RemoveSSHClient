//
// Created by User on 14.01.2024.
//

#ifndef REMOTESSHCLIENT_SSHCONTROLLEREXCEPTION_H
#define REMOTESSHCLIENT_SSHCONTROLLEREXCEPTION_H

#include <exception>
#include "../../Model/SSHConnection/SSHConnection.h"

class SSHControllerException : public std::exception {
private:
    const char* message;
    SSHConnection connection;
public:
    explicit SSHControllerException(const char* message, SSHConnection connection) : std::exception() {
        this->message = message;
        this->connection = connection;
    }
    virtual const char* what() const noexcept override {
        return message;
    }
    virtual SSHConnection getConnection() const noexcept {
        return connection;
    }
};

#endif //REMOTESSHCLIENT_SSHCONTROLLEREXCEPTION_H
