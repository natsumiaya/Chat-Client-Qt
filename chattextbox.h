#ifndef CHATTEXTBOX_H
#define CHATTEXTBOX_H

#include <QTextEdit>

class ChatTextBox : public QTextEdit
{
    Q_OBJECT
public:
    ChatTextBox(QObject*parent = 0);
    ~ChatTextBox();

private:
    void keyPressEvent(QKeyEvent* event);

signals:
    void returnKeyPressed();
};

#endif // CHATTEXTBOX_H
