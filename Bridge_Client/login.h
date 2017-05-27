#ifndef LOGIN_H
#define LOGIN_H

#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

private slots:
    void login_to_server(void);
private:
    int connect_to_server(void);
    QPushButton *exitbtn,*loginbtn,*registerbtn;
    QLineEdit *account,*password;
    QLabel *status;
};

#endif // LOGIN_H
