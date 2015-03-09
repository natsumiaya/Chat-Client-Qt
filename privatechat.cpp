#include "privatechat.h"
#include <QCloseEvent>
#include <QTimer>
#include "ui_privatechat.h"
#include "publicchat.h"

PrivateChat::PrivateChat(QString username, int intervalMsec, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PrivateChat)
{
    ui->setupUi(this);
    timer.setInterval(intervalMsec);
    connect(&timer, SIGNAL(timeout()), this, SLOT(checkReceiverStatus()));
    connect(ui->message_box, SIGNAL(returnKeyPressed()), this, SLOT(checkMessageText()));
    connect(ui->send_button, SIGNAL(clicked()), this, SLOT(checkMessageText()));

    this->username = username;
}

PrivateChat::~PrivateChat()
{
    delete ui;
}

void PrivateChat::closeEvent(QCloseEvent *event){
    emit windowClosed((QObject*)this);
    event->accept();
}

void PrivateChat::showEvent(QShowEvent *event){
    timer.start();
    event->accept();
}

void PrivateChat::setReceiver(QString messageReceiver){
    this->messageReceiver = messageReceiver;
    ui->messageReceiver->setText(messageReceiver);
    ui->receiverStatus->setText("Unknown");
}

void PrivateChat::checkMessageText(){
    QString message = ui->message_box->toPlainText();
    this->addUserMessage(message);
    emit sendMessage(this->messageReceiver, message);
}

void PrivateChat::addUserMessage(QString messageContent){
    ui->message_box->append("<b><style= 'color:green'>" + this->username + "</style></b><br/>");
    ui->message_box->append(messageContent + "<br/>");
}

void PrivateChat::addMessage(QString messageContent){
    ui->message_box->append("<b><style= 'color:red'>" + this->messageReceiver + "</style></b><br/>");
    ui->message_box->append(messageContent + "<br/>");
}

void PrivateChat::checkReceiverStatus(){
    QStringList* userList = ((PublicChat*)parent())->getUserList();
    if(userList->contains(messageReceiver)){
        ui->receiverStatus->setText("Online");
    }
    else{
        ui->receiverStatus->setText("Offline");
    }
}

QString PrivateChat::getReceiver(){
    return messageReceiver;
}
