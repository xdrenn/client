#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QStyle>
#include <QMetaEnum>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setDeviceController();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_IPAddress_textChanged(const QString &arg1)
{
    QString state = "0";
    if(arg1 == "..."){
        state = "";
    } else {
        QHostAddress address(arg1);
        if(QAbstractSocket::IPv4Protocol == address.protocol()) {
            state = "1";
    }
    }
    ui->IPAddress->setProperty("state", state);
    style()->polish(ui->IPAddress);
}


void MainWindow::on_btnConnect_clicked()
{
    if(_controller.isConnected()){
        _controller.disconnect();
    } else {
    auto ip = ui->IPAddress->text();
    auto port = ui->spinPort->value();
    _controller.connectToDevice(ip, port);
    }
}

void MainWindow::device_connected()
{
    ui->console->addItem("Connect to Device");
    ui->btnConnect->setText("Disconnect");
}

void MainWindow::device_disconnected()
{
    ui->console->addItem("Disconnect from Device");
    ui->btnConnect->setText("Connect");
}

void MainWindow::device_stateChanged(QAbstractSocket::SocketState state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    ui->console->addItem(metaEnum.valueToKey(state));
}
void MainWindow::device_error(QAbstractSocket::SocketError socketError)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError>();
    ui->console->addItem(metaEnum.valueToKey(socketError));
}

void MainWindow::device_dataReady(QByteArray data)
{
    ui->console->addItem(QString(data));
}

void MainWindow::setDeviceController()
{
    connect(&_controller, &DeviceController::connected, this, &MainWindow::device_connected);
    connect(&_controller, &DeviceController::disconnected, this, &MainWindow::device_disconnected);
    connect(&_controller, &DeviceController::stateChanged, this, &MainWindow::device_stateChanged);
    connect(&_controller, &DeviceController::error, this, &MainWindow::device_error);
    connect(&_controller, &DeviceController::dataReady, this, &MainWindow::device_dataReady);
}



