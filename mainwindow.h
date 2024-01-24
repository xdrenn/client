#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHostAddress>
#include <QStyle>
#include "DeviceController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_IPAddress_textChanged(const QString &arg1);

    void on_btnConnect_clicked();

    void device_connected();
    void device_disconnected();
    void device_stateChanged(QAbstractSocket::SocketState);
    void device_error(QAbstractSocket::SocketError socketError);
    void device_dataReady(QByteArray);

    void on_btnSend_clicked();

private:
    Ui::MainWindow *ui;
    DeviceController _controller;

    void setDeviceController();
};
#endif // MAINWINDOW_H
