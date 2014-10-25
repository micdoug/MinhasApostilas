#include "lineeditcheckcase.h"
#include <QKeyEvent>

namespace Utils {

LineEditCheckCase::LineEditCheckCase(QWidget *parent) :
    QLineEdit(parent)
{
}

void LineEditCheckCase::keyPressEvent(QKeyEvent *event)
{
    if(event->text().at(0).isLetter())
    {
        QLineEdit::keyPressEvent(new QKeyEvent(QKeyEvent::KeyPress, event->key(), event->modifiers(), event->text().toUpper()));
    }
    else
    {
        QLineEdit::keyPressEvent(event);
    }
}

} // namespace Utils
