#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets/QMainWindow>
#include <QTcpSocket>
#include <QTime>
#include <QHostAddress>
#include <QDataStream>
#include "ui_Client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_lineEdit_returnPressed();
private:
    Ui::ClientClass *ui;
    QTcpSocket *socket;
    QByteArray SData;
    void SendToServer(QString str);
    quint16 nextBlockSize;

public slots:
    void slotReadyRead();
};
#endif // CLIENT_H