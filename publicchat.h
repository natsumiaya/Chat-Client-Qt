#ifndef PUBLICCHAT_H
#define PUBLICCHAT_H

#include <QMainWindow>
#include "privatechat.h"

namespace Ui {
class PublicChat;
}

class PublicChat : public QMainWindow
{
    Q_OBJECT

public:
    explicit PublicChat(int maxCharacterLength = 1024, QWidget *parent = 0);
    ~PublicChat();

private:
    Ui::PublicChat *ui;
    int maxCharacterMessageLength;


public slots:
    void MessageTextChanged();
};

#endif // PUBLICCHAT_H
