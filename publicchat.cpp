#include "publicchat.h"
#include "ui_publicchat.h"

PublicChat::PublicChat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PublicChat)
{
    ui->setupUi(this);

}

PublicChat::~PublicChat()
{
    delete ui;
}
