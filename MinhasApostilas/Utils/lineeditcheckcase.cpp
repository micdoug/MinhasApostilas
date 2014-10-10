#include "lineeditcheckcase.h"
#include <QKeyEvent>

namespace Utils {

LineEditCheckCase::LineEditCheckCase(QWidget *parent) :
    QLineEdit(parent)
{
}

void LineEditCheckCase::keyPressEvent(QKeyEvent *event)
{
    if(event->key() >= Qt::Key_A && event->key() <= Qt::Key_Z)
    {
        QLineEdit::keyPressEvent(new QKeyEvent(QKeyEvent::KeyPress, event->key(), event->modifiers(), event->text().toUpper()));
    }
    else
    {
        QLineEdit::keyPressEvent(event);
    }
}

} // namespace Utils
