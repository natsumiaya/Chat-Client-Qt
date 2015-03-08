#include "publicchat.h"
#include "ui_publicchat.h"

PublicChat::PublicChat(int maxCharacterLength, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PublicChat)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(), this->height());

    connect(ui->message_box, SIGNAL(textChanged()), this, SLOT(MessageTextChanged()));
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
