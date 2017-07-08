#ifndef LOGIN_H
#define LOGIN_H

#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QRegExpValidator>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    void setsocket(int);
signals:
    void stage_change(int);
private slots:
    void login_to_server(void);
    void register_to_server(void);
    void quit_game(void);
private:
    int send_account(int);
    QPushButton *exitbtn,*loginbtn,*registerbtn;
    QLineEdit *account,*password;
    QLabel *status;
    QHBoxLayout *hlayout;
    QVBoxLayout *vlayout;
    int sockfd;
};

#endif // LOGIN_H
