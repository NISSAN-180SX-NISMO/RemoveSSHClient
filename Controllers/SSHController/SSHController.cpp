//
// Created by User on 13.01.2024.
//

#include <iostream>
#include "SSHController.h"


SSHController::SSHController(SSHConnection connection) {
    this->connection = connection;
    this->session = ssh_new();

    ssh_options_set(this->session, SSH_OPTIONS_HOST, this->connection.serverIp.c_str());
    ssh_options_set(this->session, SSH_OPTIONS_USER, this->connection.username.c_str());
    ssh_options_set(this->session, SSH_OPTIONS_HOSTKEYS, this->connection.privateKeyPath.c_str());
}

SSHController::~SSHController() {
    this->closeChannel();
    this->disconnect();
}

void SSHController::connect() {
    this->tryConnect();
    this->tryAuthenticate();
}

void SSHController::tryConnect() {
    if (ssh_connect(this->session) != SSH_OK) {
        ssh_free(this->session);
        throw SSHControllerException("Failed to connect to remote host", this->connection);
    }
}

void SSHController::tryAuthenticate() {
    if (ssh_userauth_publickey_auto(this->session, NULL, NULL) != SSH_AUTH_SUCCESS) {
        ssh_disconnect(this->session);
        ssh_free(this->session);
        throw SSHControllerException("Failed to authenticate", this->connection);
    }
}

void SSHController::disconnect() {
    if (this->session) {
        ssh_disconnect(this->session);
        ssh_free(this->session);
    }
}



std::string SSHController::executeCommand(std::string command) {
    this->tryOpenChannel();
    this->tryExecuteCommand(command);
    auto output = this->redCommandOutput();
    this->closeChannel();
    return output;
}

void SSHController::tryOpenChannel() {
    channel = ssh_channel_new(this->session);
    if (ssh_channel_open_session(channel) != SSH_OK) {
        ssh_channel_free(channel);
        throw SSHControllerException("Failed to open SSH channel", this->connection);
    }
}

void SSHController::tryExecuteCommand(std::string command) {
    if (ssh_channel_request_exec(channel, command.c_str()) != SSH_OK) {
        ssh_channel_close(channel);
        ssh_channel_free(channel);
        throw SSHControllerException(std::string("Failed to execute command \"" + command + "\"").c_str(), this->connection);
    }
}

std::string SSHController::redCommandOutput() {
    char buffer[256];
    int nbytes;
    std::string output;
    while ((nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0)) > 0)
        output.append(buffer, nbytes);
    return output;
}

void SSHController::closeChannel() {
    if (this->channel) {
        ssh_channel_send_eof(channel);
        ssh_channel_close(channel);
        ssh_channel_free(channel);
    }
}

