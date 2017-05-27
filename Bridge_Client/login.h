#ifndef LOGIN_H
#define LOGIN_H

#include <QPushButton>

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

private:
    QPushButton *exitbtn,*loginbtn,*registerbtn;
};

#endif // LOGIN_H
