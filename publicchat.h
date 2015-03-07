#ifndef PUBLICCHAT_H
#define PUBLICCHAT_H

#include <QMainWindow>

namespace Ui {
class PublicChat;
}

class PublicChat : public QMainWindow
{
    Q_OBJECT

public:
    explicit PublicChat(QWidget *parent = 0);
    ~PublicChat();

private:
    Ui::PublicChat *ui;
};

#endif // PUBLICCHAT_H
