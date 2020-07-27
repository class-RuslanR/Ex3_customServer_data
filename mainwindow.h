#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QTime>
#include <QRandomGenerator>
#include <QTimer>

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
    void on_connectBotton_clicked();
    void myConnected();
    void sendData(int x);
    //void on_startBotton_clicked();
    void generateData();

    void on_startBotton_clicked();

private:
    QTimer* _timer;
    QTime _time;
    Ui::MainWindow *ui;
    QTcpSocket* _socket = nullptr;
    uint16_t _port = 2525;
};
#endif // MAINWINDOW_H
