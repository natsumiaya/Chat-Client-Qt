#ifndef PRIVATECHAT_H
#define PRIVATECHAT_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class PrivateChat;
}

class PrivateChat : public QMainWindow
{
    Q_OBJECT

public:
    explicit PrivateChat(int intervalMsec = 5000, QWidget *parent = 0);
    ~PrivateChat();
    QString getReceiver();
    void setReceiver(QString messageReceiver);
    void setTimerIntrval(int msec);
    void addMessage(QString messageContent);

signals:
    void sendMessage(QString messageReceiver, QString messageContent);
    void windowClosed(QObject* window);

public slots:
    void checkMessageText();
    void checkReceiverStatus();

private:
    Ui::PrivateChat *ui;
    QString messageReceiver;
    QTimer timer;
    QList<QString>* userList;

private:
    void showEvent(QShowEvent* event);
    void closeEvent(QCloseEvent* event);
};

#endif // PRIVATECHAT_H
