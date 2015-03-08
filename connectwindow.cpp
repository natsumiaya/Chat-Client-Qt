#include "connectwindow.h"
#include "ui_connectwindow.h"
#include <QMessageBox>

ConnectWindow::ConnectWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConnectWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), this->height());
    ui->address_line->setPlaceholderText("Address");
    ui->port_line->setPlaceholderText("Port");
    ui->username_line->setPlaceholderText("Username");
    ui->address_line->setFocus();

    connect(ui->username_line, SIGNAL(returnPressed()), this, SLOT(ConnectToHost()));
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(ConnectToHost()));
    ui->port_line->setValidator(new QIntValidator(0, 65535));
}

ConnectWindow::~ConnectWindow()
{
    delete ui;
}

void ConnectWindow::ConnectToHost(){
    QString IP = ui->address_line->text();
    quint16 port = ui->port_line->text().toUInt();
    QString name = ui->username_line->text();

    if(IP == "" || port == 0 || name == ""){
        QMessageBox alert;
        alert.setText("Please fill out all the field");
        alert.exec();
    }

}
