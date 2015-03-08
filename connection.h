#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(int refreshRate = 5, QObject *parent = 0);
    ~Connection();
    bool connectToHost(QString IP, quint16 Port, QString Username);

private:
    QTimer timer;
    QTcpSocket* socket;
    bool isApplicationRunning;
    QString username;

signals:

public slots:
    void incomingMessage();
    void checkUserList();
    void disconnected();
    void outgoingPublicMessage(QString messageContent);
};

#endif // CONNECTION_H
