#ifndef LOGIN_H
#define LOGIN_H

#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

private slots:
    int connect_to_server(void);
private:
    QPushButton *exitbtn,*loginbtn,*registerbtn;
    QLineEdit *account,*password;
};

#endif // LOGIN_H
