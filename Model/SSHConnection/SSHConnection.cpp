//
// Created by User on 14.01.2024.
//

#include "SSHConnection.h"

SSHConnection::SSHConnection(std::string username, std::string serverIp, std::string privateKeyPath) {
    this->username = username;
    this->serverIp = serverIp;
    this->privateKeyPath = privateKeyPath;
}

SSHConnection::SSHConnection() {
    this->username = "";
    this->serverIp = "";
    this->privateKeyPath = "";
}

SSHConnection::SSHConnection(const SSHConnection &connection) {
    this->username = connection.username;
    this->serverIp = connection.serverIp;
    this->privateKeyPath = connection.privateKeyPath;
}
