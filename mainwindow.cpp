#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Client");
    ui->line_ip->setText("localhost");
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &MainWindow::generateData);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_connectBotton_clicked()
{
    _socket = new QTcpSocket(this);
    _socket->connectToHost(ui->line_ip->text(),_port);
    connect(_socket,SIGNAL(connected()),SLOT(myConnected()));
}

void MainWindow::myConnected()
{
    setWindowTitle("Connected " + ui->line_ip->text());
}

void MainWindow::sendData(int x)
{
    QByteArray arrblock;
    QDataStream out(&arrblock, QIODevice::WriteOnly);
    out << x << (_time.elapsed() / 1000);
    _socket->write(arrblock);
}


void MainWindow::generateData()
{
    int8_t x = QRandomGenerator::global()->bounded(-50,50);
    sendData(x);
    ui->textBrowser->append(QString::number(x, 10) + "  " +
                            QString::number(_time.elapsed() / 1000));
    //ui->textBrowser->append(QString::number(x, 10) + "  " + _time.toString());
}



void MainWindow::on_startBotton_clicked()
{
    if(ui->startBotton->isChecked())
    {
        ui->startBotton->setText("Stop");
        _timer->start(1000);
        _time.restart();
    }
    else
    {
        ui->startBotton->setText("Start");
        _timer->stop();
    }
}
