#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = 0);
    ~Connection();

signals:

public slots:
};

#endif // CONNECTION_H
