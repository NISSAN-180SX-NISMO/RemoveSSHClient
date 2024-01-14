#include <QApplication>
#include <iostream>
#include "View/MainWindow/mainwindow.h"

#include "Model/SSHConnection/SSHConnection.h"



int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow mainWindow;

    SSHConnection ssh("testuser", "158.160.143.11", "C:/Users/User/.ssh/id_ed25519");

    mainWindow.show();
    return QApplication::exec();
}
