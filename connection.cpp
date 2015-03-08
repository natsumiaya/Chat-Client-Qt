#include "connection.h"
#include "publicchat.h"

Connection::Connection(int refreshRate, QObject *parent) : QObject(parent)
{
    timer.setInterval(refreshRate * 1000);
    connect(&timer, SIGNAL(timeout()), this, SLOT(checkUserList()));
}

Connection::~Connection()
{

}

void Connection::connectToHost(QString IP, quint16 Port, QString Username){
    PublicChat* theParent = parent();
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(incomingMessage()));
    socket->connectToHost(IP, Port);
    if(socket->waitForConnected()){
        socket->write(Username.toUtf8() + "\r\n.\r\n");
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    }

}
