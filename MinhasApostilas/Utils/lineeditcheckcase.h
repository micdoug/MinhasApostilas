#ifndef UTILS_LINEEDITCHECKCASE_H
#define UTILS_LINEEDITCHECKCASE_H

#include <QLineEdit>

namespace Utils {

class LineEditCheckCase : public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEditCheckCase(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);

};

} // namespace Utils

#endif // UTILS_LINEEDITCHECKCASE_H
