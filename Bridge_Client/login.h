#ifndef LOGIN_H
#define LOGIN_H

#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QRegExpValidator>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    int getsocket();
public slots:
    void show_everything(void);
signals:
    void stage_change(void);
private slots:
    void login_to_server(void);
    void register_to_server(void);
private:
    int connect_to_server(void);
    int send_account(int);
    void hide_everything(void);
    QPushButton *exitbtn,*loginbtn,*registerbtn;
    QLineEdit *account,*password;
    QLabel *status;
    int sockfd;
};

#endif // LOGIN_H
