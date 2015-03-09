#include "privatechat.h"
#include <QCloseEvent>
#include <QTimer>
#include "ui_privatechat.h"

PrivateChat::PrivateChat(int intervalMsec, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PrivateChat)
{
    ui->setupUi(this);
    timer.setInterval(intervalMsec);
    connect(&timer, SIGNAL(timeout()), this, SLOT(checkReceiverStatus()));
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
