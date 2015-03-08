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
    void setUsername(QString username);
    void addMessage(QString username, QString messageContent);
    void updateUserList(QList<QString> userList);
    PrivateChat* addPrivateChat(QString username);
    QList<PrivateChat*>* getPrivateChatList();

private:
    Ui::PublicChat *ui;
    int maxCharacterMessageLength;
    QString username;
    QList<PrivateChat*> privateList;

private:
    void closeEvent(QCloseEvent* event);

signals:
    void sendMessage(QString messageContent);
    void newPrivateWindow(QObject* privateWindow);

public slots:
    void MessageTextChanged();
    void checkMessage();
    void PrivateWindowClosed(QObject* window);
};

#endif // PUBLICCHAT_H
