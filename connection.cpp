#include "connection.h"
#include "publicchat.h"

Connection::Connection(int refreshRate, QObject *parent) : QObject(parent)
{
    timer.setInterval(refreshRate * 1000);
    connect(&timer, SIGNAL(timeout()), this, SLOT(checkUserList()));
    isApplicationRunning = false;
}

Connection::~Connection()
{

}

bool Connection::connectToHost(QString IP, quint16 Port, QString Username){
    socket = new QTcpSocket(this);
    this->username = Username;
    connect(socket, SIGNAL(readyRead()), this, SLOT(incomingMessage()));
    socket->connectToHost(IP, Port);
    if(socket->waitForConnected()){
        socket->write(Username.toUtf8() + "\r\n.\r\n");
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
        PublicChat* thePublic = parent();
        connect(thePublic, SIGNAL(sendMessage(QString)), this, SLOT(outgoingPublicMessage(QString)));
        isApplicationRunning = true;
        return true;
    }
    return false;
}

void Connection::disconnected(){
    if(isApplicationRunning){
        while(!socket->reset() && isApplicationRunning);
        socket->write(username.toUtf8() + "\r\n.\r\n");
    }
    else{
        socket->deleteLater();
    }
}

void Connection::outgoingPublicMessage(QString messageContent){
    QString message("Mode: Public\r\n" + messageContent + "\r\n.\r\n");
    socket->write(message.toUtf8());
}

void Connection::incomingMessage(){
    QByteArray data = socket->readAll();

}
