#include "login.h"

Login::Login(QWidget *parent) : QWidget(parent)
{
    exitbtn = new QPushButton("Exit",parent);
    exitbtn->setGeometry(50,450,200,100);
    exitbtn->setToolTip("Quit the Game");

    loginbtn = new QPushButton("Login",parent);
    loginbtn->setGeometry(300,450,200,100);
    loginbtn->setToolTip("Login to the Server");

    registerbtn = new QPushButton("Register",parent);
    registerbtn->setGeometry(550,450,200,100);
    registerbtn->setToolTip("Register a Account");

}
