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

    this->username = ((PublicChat*)parent)->getUsername();
    this->messageReceiver = username;
    ui->messageReceiver->setText(username);
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
    ui->message_box->clear();
    emit sendMessage(this->messageReceiver, message);
}

void PrivateChat::addUserMessage(QString messageContent){
    ui->chat_box->setAlignment(Qt::AlignLeft);
    ui->chat_box->setTextColor(Qt::green);
    ui->chat_box->setFontWeight(QFont::Bold);
    ui->chat_box->append(this->username + " :");
    ui->chat_box->setTextColor(Qt::black);
    ui->chat_box->setFontWeight(QFont::Normal);
    ui->chat_box->append(messageContent + "\n");
}

void PrivateChat::addMessage(QString messageContent){
    ui->chat_box->setAlignment(Qt::AlignRight);
    ui->chat_box->setTextColor(Qt::red);
    ui->chat_box->setFontWeight(QFont::Bold);
    ui->chat_box->append(this->messageReceiver + " :");
    ui->chat_box->setTextColor(Qt::black);
    ui->chat_box->setFontWeight(QFont::Normal);
    ui->chat_box->append(messageContent + "\n");
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
