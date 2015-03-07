#include "connectwindow.h"
#include "ui_connectwindow.h"

ConnectWindow::ConnectWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(ConnectToHost()));

}

ConnectWindow::~ConnectWindow()
{
    delete ui;
}

void ConnectWindow::ConnectToHost(){
    QString IP = ui->address_line->text();

}
