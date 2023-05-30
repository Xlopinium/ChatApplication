#include <QCoreApplication>
#include "server.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    server myServer;
    if (!myServer.isListening())
    {
        qDebug() << "Server could not start!";
        return -1;
    }

    qDebug() << "Server started on port" << myServer.serverPort();

    return a.exec();
}
