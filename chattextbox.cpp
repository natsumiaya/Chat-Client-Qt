#include "chattextbox.h"
#include <QKeyEvent>

ChatTextBox::ChatTextBox(QObject *parent):
    QTextEdit(parent)
{

}

ChatTextBox::~ChatTextBox()
{

}

void ChatTextBox::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        if(event->modifiers().testFlag(Qt::ShiftModifier)){
            QTextEdit::keyPressEvent(event);
        }
        else{
            emit returnKeyPressed();
        }
    }
    else{
        QTextEdit::keyPressEvent(event);
    }
}
