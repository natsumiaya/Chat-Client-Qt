#include "privatechat.h"
#include "ui_privatechat.h"

PrivateChat::PrivateChat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PrivateChat)
{
    ui->setupUi(this);
}

PrivateChat::~PrivateChat()
{
    delete ui;
}
