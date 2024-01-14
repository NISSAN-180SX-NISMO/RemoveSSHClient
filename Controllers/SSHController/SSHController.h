//
// Created by User on 13.01.2024.
//

#ifndef REMOTESSHCLIENT_SSHCONTROLLER_H
#define REMOTESSHCLIENT_SSHCONTROLLER_H


#include "../../Model/SSHConnection/SSHConnection.h"
#include "SSHControllerException.h"
#include <libssh/libssh.h>

class SSHController {
private:
    SSHConnection connection;

    ssh_session session;
    void tryConnect();
    void tryAuthenticate();

    ssh_channel channel;
    void tryOpenChannel();
    void tryExecuteCommand(std::string command);
    std::string redCommandOutput();
    void closeChannel();
public:
    explicit SSHController(SSHConnection connection);
    ~SSHController();
    void connect();
    void disconnect();
    std::string executeCommand(std::string command);
};


#endif //REMOTESSHCLIENT_SSHCONTROLLER_H
