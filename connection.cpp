#include "connection.h"
#include "publicchat.h"
#include <QMessageBox>

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
        timer.start();
        return true;
    }
    return false;
}

void Connection::disconnected(){
    if(isApplicationRunning){
        QMessageBox alert("Disconnected");
        alert.setText("You have been disconnected from server\nTrying to reconnect");

        alert.exec();
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
    QString message(data);
    for(const QString oneMessage : message.split("\r\n.\r\n")){
        if(oneMessage == NULL) continue;
        QStringList stringList = oneMessage.split("\r\n");
        if(stringList.at(0) == "Mode: Public"){
            //Send message to the window
        }
        else if(stringList.at(0) == "Mode: Private"){
            //Check private window
            //Create new window if necessary
            //Send message to the window
        }
        else if(stringList.at(0) == "Mode: List"){
            //Contain user list in QList
            //Send the list to PublicChat
        }
    }
}

void Connection::outgoingPrivateMessage(QString receiver, QString messageContent){
    QString message("Mode: Private\r\nUser: " + receiver + "\r\n" + messageContent + "\r\n.\r\n");
    socket->write(message.toUtf8());
}

void Connection::checkUserList(){
    QString message("Mode: GetList\r\n.\r\n");
    socket->write(message.toUtf8());
}

void Connection::newPrivateWindow(QObject *privateWindow){
    //Add signal listener to the new window
}
