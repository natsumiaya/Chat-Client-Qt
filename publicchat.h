#ifndef PUBLICCHAT_H
#define PUBLICCHAT_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "privatechat.h"
#include "rc4algorithm.h"
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
    void updateUserList(QStringList userList);
    PrivateChat* addPrivateChat(QString username);
    QList<PrivateChat*>* getPrivateChatList();
    QStringList* getUserList();
    QString getUsername();
    RC4Algorithm* getRC4();

private:
    Ui::PublicChat *ui;
    int maxCharacterMessageLength;
    QString username;
    QList<PrivateChat*> privateList;
    QStringList userList;
    RC4Algorithm *rc4;
private:
    void closeEvent(QCloseEvent* event);
    void addMessage(QString messageContent);

signals:
    void sendMessage(QString messageContent);
    void newPrivateWindow(QObject* privateWindow);

public slots:
    void MessageTextChanged();
    void checkMessage();
    void PrivateWindowClosed(QObject* window);
    void createNewPrivateWindow(QListWidgetItem* item);
};

#endif // PUBLICCHAT_H
