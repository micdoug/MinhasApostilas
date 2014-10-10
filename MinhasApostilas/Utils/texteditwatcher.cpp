#include "texteditwatcher.h"

namespace Utils {

TextEditWatcher::TextEditWatcher(QWidget *parent) :
    QPlainTextEdit(parent)
{}

TextEditWatcher::~TextEditWatcher()
{}

void TextEditWatcher::focusOutEvent(QFocusEvent *event)
{
    emit editingFinished(toPlainText());
    QPlainTextEdit::focusOutEvent(event);
}

void TextEditWatcher::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Tab)
    {
        event->ignore();
    }
    else if(event->key() >= Qt::Key_A && event->key() <= Qt::Key_Z)
    {
        QPlainTextEdit::keyPressEvent(new QKeyEvent(QKeyEvent::KeyPress, event->key(), event->modifiers(), event->text().toUpper()));
    }
    else
    {
        QPlainTextEdit::keyPressEvent(event);
    }
}

} // namespace Utils
