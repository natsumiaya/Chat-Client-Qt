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
    void connectToHost(QString IP, quint16 Port, QString Username);

private:
    QTimer timer;
    QTcpSocket* socket;

signals:

public slots:
    void incomingMessage();
    void checkUserList();
    void disconnected();
};

#endif // CONNECTION_H
