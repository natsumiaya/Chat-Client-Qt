#include "publicchat.h"
#include "ui_publicchat.h"
#include <QCloseEvent>

PublicChat::PublicChat(int maxCharacterLength, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PublicChat)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(), this->height());

    connect(ui->message_box, SIGNAL(textChanged()), this, SLOT(MessageTextChanged()));
    connect(ui->message_box, SIGNAL(returnKeyPressed()), this, SLOT(checkMessage()));
    connect(ui->send_button, SIGNAL(clicked()), this, SLOT(checkMessage()));
    connect(ui->user_list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(createNewPrivateWindow(QListWidgetItem*)));
    maxCharacterMessageLength = maxCharacterLength;
}

PublicChat::~PublicChat()
{
    delete ui;
}

void PublicChat::MessageTextChanged(){
    int length = ui->message_box->toPlainText().length();
    if(length > maxCharacterMessageLength){
        QString message = ui->message_box->toPlainText();
        message.remove(maxCharacterMessageLength, length - maxCharacterMessageLength);
        ui->message_box->setPlainText(message);
        ui->tex_number_label->setText(QString::number(maxCharacterMessageLength) + "/" + QString::number(maxCharacterMessageLength));
    }
    else{
        ui->tex_number_label->setText(QString::number(length) + "/" + QString::number(maxCharacterMessageLength));
    }
}

void PublicChat::checkMessage(){
    QString message = ui->message_box->toPlainText();
    this->addMessage(message);
    emit sendMessage(message);
}

void PublicChat::setUsername(QString username){
    this->username = username;
}

void PublicChat::PrivateWindowClosed(QObject *window){
    privateList.removeOne((PrivateChat*) window);
}

void PublicChat::closeEvent(QCloseEvent *event){

    this->disconnect();
    for(PrivateChat* privateWindow : privateList){
        privateWindow->close();
    }
    event->accept();
}


void PublicChat::addMessage(QString username, QString messageContent){
    //Add message to TextBrowser
    ui->chat_box->append("<b><style= 'color:red'>" + username + "</style></b><br/>");
    ui->chat_box->append(messageContent + "<br/>");
}

void PublicChat::addMessage(QString messageContent){
    ui->chat_box->append("<b><style= 'color:green'>" + this->username + "</style></b><br/>");
    ui->chat_box->append(messageContent + "<br/>");

}

void PublicChat::createNewPrivateWindow(QListWidgetItem *item){
    PrivateChat* newPrivateChat = new PrivateChat(this->username);
    newPrivateChat->setReceiver(item->text());
    newPrivateChat->show();
    privateList.append(newPrivateChat);
    emit newPrivateWindow((QObject*)newPrivateChat);
}

QStringList *PublicChat::getUserList(){
    return &userList;
}

QList<PrivateChat*>* PublicChat::getPrivateChatList(){
    return &privateList;
}

PrivateChat* PublicChat::addPrivateChat(QString username){
    PrivateChat* newPrivateWindow = new PrivateChat(username);
    privateList.append(newPrivateWindow);
    newPrivateWindow->show();
    return newPrivateWindow;
}

void PublicChat::updateUserList(QStringList userList){
    ui->user_list->clear();
    ui->user_list->addItems(userList);
}
