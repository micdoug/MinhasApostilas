/* ----------------------------------------------------------------------
 * Arquivo: texteditwatcher.h
 * Descrição: Arquivo de declaração da classe Utils::TextEditWatcher
 *
 * Autor: Michael Dougras da Silva
 * Contato: micdoug.silva@gmail.com
 * ----------------------------------------------------------------------*/

#ifndef UTILS_TEXTEDITWATCHER_H
#define UTILS_TEXTEDITWATCHER_H

#include <QPlainTextEdit>

namespace Utils {

class TextEditWatcher : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit TextEditWatcher(QWidget *parent = 0);
    virtual ~TextEditWatcher();

signals:
    void editingFinished(const QString &plaintext);

protected:
    void focusOutEvent(QFocusEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

} // namespace Utils

#endif // UTILS_TEXTEDITWATCHER_H
