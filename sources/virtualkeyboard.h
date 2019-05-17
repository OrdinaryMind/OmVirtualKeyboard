#ifndef VIRTUALKEYBOARD_H
#define VIRTUALKEYBOARD_H

#include <QFrame>

namespace Ui {
class VirtualKeyboard;
}

class VirtualKeyboard : public QFrame
{
    Q_OBJECT

public:
    explicit VirtualKeyboard(QWidget *parent = nullptr);
    ~VirtualKeyboard();

private:
    Ui::VirtualKeyboard *ui;
};

#endif // VIRTUALKEYBOARD_H
