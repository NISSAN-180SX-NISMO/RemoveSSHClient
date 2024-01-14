//
// Created by User on 13.01.2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

#include "mainwindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->disconnectPushButton->setEnabled(false);
    ui->connectPushButton->setEnabled(false);

    ui->commandOutputTextBrowser->setReadOnly(true);
    ui->commandOutputTextBrowser->setText("Соединение не установлено.");

    QRegularExpression ipRegExp("\\b(?:[0-9]{1,3}\\.){3}[0-9]{1,3}\\b");
    auto *ipValidator = new QRegularExpressionValidator(ipRegExp, this);
    ui->serverIpLineEdit->setValidator(ipValidator);

    QRegularExpression usernameRegExp("^[a-z][-a-z0-9]*$");
    auto *usernameValidator = new QRegularExpressionValidator(usernameRegExp, this);
    ui->usernameLineEdit->setValidator(usernameValidator);

    this->controller = nullptr;

    ui->privateSSHKeyPathLineEdit->setReadOnly(true);
    ui->privateSSHKeyPathLineEdit->setPlaceholderText("Select private key");

    this->fileDialog = new QFileDialog(this);
    this->fileDialog->setFileMode(QFileDialog::ExistingFile);
    this->fileDialog->setNameFilter(tr("Private key (*)"));
    connect(fileDialog, &QFileDialog::fileSelected, this, &MainWindow::setPrivateKeyPath);

    connect(ui->privateSSHKeyPathLineEdit, &QLineEdit::textChanged, this, &MainWindow::updateConnectingButtons);
    connect(ui->usernameLineEdit, &QLineEdit::textChanged, this, &MainWindow::updateConnectingButtons);
    connect(ui->serverIpLineEdit, &QLineEdit::textChanged, this, &MainWindow::updateConnectingButtons);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_browsePushButton_clicked() {
    this->fileDialog->exec();
}

void MainWindow::setPrivateKeyPath(const QString &path) {
    ui->privateSSHKeyPathLineEdit->setText(path);
}

void MainWindow::on_connectPushButton_clicked() {
    SSHConnection connection(ui->usernameLineEdit->text().toStdString(),
                             ui->serverIpLineEdit->text().toStdString(),
                             ui->privateSSHKeyPathLineEdit->text().toStdString());
    try {
        this->controller = new SSHController(connection);
        controller->connect();
        auto res = controller->executeCommand("sudo apt show libssh-4");
        ui->commandOutputTextBrowser->setText(QString::fromStdString(res));
        ui->connectPushButton->setEnabled(false);
        ui->disconnectPushButton->setEnabled(true);
    } catch (SSHControllerException &exception) {
        ui->commandOutputTextBrowser->setText("Ошибка соединения!");
        QMessageBox::critical(this, "Error", exception.what());
    }
}

void MainWindow::on_disconnectPushButton_clicked() {
    controller->disconnect();
    ui->connectPushButton->setEnabled(true);
    ui->disconnectPushButton->setEnabled(false);
    ui->commandOutputTextBrowser->setText("Соединение не установлено.");
}

void MainWindow::updateConnectingButtons() {
    ui->connectPushButton->setEnabled(formIsFilled());
}

bool MainWindow::formIsFilled() {
    if (ui->usernameLineEdit->text().isEmpty())
        return false;
    if (ui->serverIpLineEdit->text().isEmpty())
        return false;
    if (ui->privateSSHKeyPathLineEdit->text().isEmpty())
        return false;
    return true;
}


