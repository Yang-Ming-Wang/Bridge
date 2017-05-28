#include "login.h"

Login::Login(QWidget *parent) : QWidget(parent)
{

    exitbtn = new QPushButton("Exit",parent);
    exitbtn->setGeometry(50,450,200,100);
    exitbtn->setToolTip("Quit the Game");
    connect(exitbtn,SIGNAL(clicked()),QApplication::instance(),SLOT(quit()));

    loginbtn = new QPushButton("Login",parent);
    loginbtn->setGeometry(300,450,200,100);
    loginbtn->setToolTip("Login to the Server");
    connect(loginbtn,SIGNAL(clicked()),this,SLOT(login_to_server()));

    registerbtn = new QPushButton("Register",parent);
    registerbtn->setGeometry(550,450,200,100);
    registerbtn->setToolTip("Register a Account");

    account = new QLineEdit(parent);
    account->setPlaceholderText("your account:");
    account->setGeometry(100,100,300,50);
    account->setMaxLength(15);

    password = new QLineEdit(parent);
    password->setPlaceholderText("your password:");
    password->setEchoMode(QLineEdit::Password);
    password->setGeometry(100,200,300,50);
    password->setMaxLength(15);

    status = new QLabel(parent);
    status->setGeometry(300,300,200,100);

}

void Login::login_to_server()
{
    int socket;
    socket = connect_to_server();
    qDebug(account->text().toLatin1());
    qDebug(password->text().toLatin1());
    if (socket >= 0) {
        char buf[10] = "Qt_Client";
        write(socket,buf,10);
        hide_everything();
        emit stage_change();
    } else {
        status->setStyleSheet("QLabel {color:red}");
        status->setText("failed login");
    }

    return ;
}

int Login::connect_to_server()
{
    int sockfd;
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0 )
        qDebug("socket error");

    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9877);

    if (inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr) <= 0)
        printf("inet_ption error for 127.0.0.1\n");

    if (::connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0) {
        qDebug("connect error");
        return -1;
    }
    return sockfd;
}

void Login::hide_everything(void)
{
    exitbtn->hide();
    loginbtn->hide();
    registerbtn->hide();

    account->hide();
    password->hide();

    status->hide();

    return ;
}

void Login::show_everything(void)
{
    exitbtn->show();
    loginbtn->show();
    registerbtn->show();

    account->show();
    password->show();

    status->show();
}
