#include "Client.h"
#include "ui_Client.h"

Client::Client(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ClientClass)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    nextBlockSize = 0;
}

Client::~Client()
{
    delete ui;
}

void Client::on_pushButton_clicked()
{
    socket->connectToHost("127.0.0.1", 5555);
}

void Client::SendToServer(QString str)
{
    SData.clear();
    QDataStream out(&SData, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(SData.size() - sizeof(quint16));
    socket->write(SData);
    ui->lineEdit->clear();
}

void Client::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if (in.status() == QDataStream::Ok)
    {
        for (;;)
        {
            if (nextBlockSize == 0)
            {
                if (socket->bytesAvailable() < 2)
                {
                    break;
                }
                in >> nextBlockSize;
            }
            if (socket->bytesAvailable() < nextBlockSize)
            {
                break;
            }
            QString str;
            QTime time;
            in >> time >> str;
            nextBlockSize = 0;
            ui->textBrowser->append(time.toString() + " " + str);
            break;
        }
    }
    else
    {
        ui->textBrowser->append("read error");
    }
}

void Client::on_pushButton_2_clicked()
{
    SendToServer(ui->lineEdit->text());
}

void Client::on_lineEdit_returnPressed()
{
    SendToServer(ui->lineEdit->text());
}