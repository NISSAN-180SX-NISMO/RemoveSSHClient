//
// Created by User on 13.01.2024.
//

#ifndef REMOTESSHCLIENT_MAINWINDOW_H
#define REMOTESSHCLIENT_MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "../../Controllers/SSHController/SSHController.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;
private slots:
    void on_connectPushButton_clicked();

    void on_disconnectPushButton_clicked();

    void on_browsePushButton_clicked();

    void setPrivateKeyPath(const QString &path);
private:
    Ui::MainWindow *ui;
    QFileDialog *fileDialog;
    SSHController *controller;
};


#endif //REMOTESSHCLIENT_MAINWINDOW_H
