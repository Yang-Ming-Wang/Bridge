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
    connect(registerbtn,SIGNAL(clicked()),this,SLOT(register_to_server()));

    QRegExp rx("\\w+");
    QRegExpValidator *validator = new QRegExpValidator(rx,parent);

    account = new QLineEdit(parent);
    account->setPlaceholderText("your account:");
    account->setGeometry(100,100,300,50);
    account->setMaxLength(15);
    account->setValidator(validator);

    password = new QLineEdit(parent);
    password->setPlaceholderText("your password:");
    password->setEchoMode(QLineEdit::Password);
    password->setGeometry(100,200,300,50);
    password->setMaxLength(15);
    password->setValidator(validator);

    status = new QLabel(parent);
    status->setGeometry(300,300,200,100);

    sockfd = connect_to_server();
}

void Login::login_to_server()
{
    int result;
    result = send_account(0);

    switch (result) {
    case 1:
        hide_everything();
        emit stage_change();
        break;
    case 2:
        status->setStyleSheet("QLabel {color:red}");
        status->setText("Account not exist!!");
        break;
    case 3:
        status->setStyleSheet("QLabel {color:red}");
        status->setText("Password Incorrect!!");
        break;
    default:
        status->setStyleSheet("QLabel {color:red}");
        status->setText("Socket error!!");
    }
    return ;
}

void Login::register_to_server()
{
    int result;
    result = send_account(1);

    switch (result) {
    case 1:
        status->setStyleSheet("QLabel {color:green}");
        status->setText("register success!!");
        break;
    case 2:
        status->setStyleSheet("QLabel {color:red}");
        status->setText("try another account!!");
        break;
    default:
        status->setStyleSheet("QLabel {color:red}");
        status->setText("Socket error!!");
    }
    return ;
}

int Login::send_account(int isreg)
{
    char buffer[15];
    int success;

    if (sockfd >= 0) {
        write(sockfd,&isreg,sizeof(int));

        bzero(buffer,15);
        strcpy(buffer,account->text().toStdString().c_str());
        write(sockfd,buffer,15);

        bzero(buffer,15);
        strcpy(buffer,password->text().toStdString().c_str());
        write(sockfd,buffer,15);

        read(sockfd,&success,sizeof(int));
        return success;
    }
    return -1;
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
