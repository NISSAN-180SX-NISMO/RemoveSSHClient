//
// Created by User on 14.01.2024.
//

#ifndef REMOTESSHCLIENT_SSHCONNECTION_H
#define REMOTESSHCLIENT_SSHCONNECTION_H

#include <string>

struct SSHConnection {
    std::string username;
    std::string serverIp;
    std::string privateKeyPath;
    SSHConnection();
    SSHConnection(std::string username, std::string serverIp, std::string privateKeyPath);
    SSHConnection(const SSHConnection& connection);
};


#endif //REMOTESSHCLIENT_SSHCONNECTION_H
