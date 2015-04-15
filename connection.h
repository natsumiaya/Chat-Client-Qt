#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <openssl/rsa.h>

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(int refreshRate_msec = 1000, QObject *parent = 0);
    ~Connection();
    bool connectToHost(QString IP, quint16 Port, QString Username);
    void setServerKeyPair(char* key, size_t key_len);
    int InitRSA();

private:
    QTimer timer;
    QTcpSocket* socket;
    bool isApplicationRunning;
    QString username;
    RSA* ServKey;
    RSA* keypair;

signals:

public slots:
    void incomingMessage();
    void checkUserList();
    void disconnected();
    void outgoingPublicMessage(QString messageContent);
    void outgoingPrivateMessage(QString receiver, QString messageContent);
    void newPrivateWindow(QObject* privateWindow);
};

#endif // CONNECTION_H
