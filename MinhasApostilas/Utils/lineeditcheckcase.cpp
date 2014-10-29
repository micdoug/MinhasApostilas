#include "lineeditcheckcase.h"
#include <QKeyEvent>

namespace Utils {

LineEditCheckCase::LineEditCheckCase(QWidget *parent) :
    QLineEdit(parent)
{
}

void LineEditCheckCase::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() >= Qt::Key_A && event->key() <= Qt::Key_Z) || event->text().compare("ç", Qt::CaseInsensitive)==0)
    {
        QLineEdit::keyPressEvent(new QKeyEvent(QKeyEvent::KeyPress, event->key(), event->modifiers(), event->text().toUpper()));
    }
    else
    {
        QLineEdit::keyPressEvent(event);
    }
}

} // namespace Utils
