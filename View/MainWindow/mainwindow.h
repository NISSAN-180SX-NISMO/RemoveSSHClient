//
// Created by User on 13.01.2024.
//

#ifndef REMOTESSHCLIENT_MAINWINDOW_H
#define REMOTESSHCLIENT_MAINWINDOW_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
};


#endif //REMOTESSHCLIENT_MAINWINDOW_H
