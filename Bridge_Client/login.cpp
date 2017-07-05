#include "login.h"

Login::Login(QWidget *parent) : QWidget(parent)
{

    exitbtn = new QPushButton("Exit",this);
    exitbtn->setGeometry(100,500,200,100);
    exitbtn->setToolTip("Quit the Game");
    connect(exitbtn,SIGNAL(clicked()),this,SLOT(quit_game()));

    loginbtn = new QPushButton("Login",this);
    loginbtn->setGeometry(500,500,200,100);
    loginbtn->setToolTip("Login to the Server");
    connect(loginbtn,SIGNAL(clicked()),this,SLOT(login_to_server()));

    registerbtn = new QPushButton("Register",this);
    registerbtn->setGeometry(900,500,200,100);
    registerbtn->setToolTip("Register a Account");
    connect(registerbtn,SIGNAL(clicked()),this,SLOT(register_to_server()));

    QRegExp rx("\\w+");
    QRegExpValidator *validator = new QRegExpValidator(rx);

    account = new QLineEdit(this);
    account->setPlaceholderText("your account:");
    account->setGeometry(150,100,300,50);
    account->setMaxLength(15);
    account->setValidator(validator);

    password = new QLineEdit(this);
    password->setPlaceholderText("your password:");
    password->setEchoMode(QLineEdit::Password);
    password->setGeometry(150,200,300,50);
    password->setMaxLength(15);
    password->setValidator(validator);

    QFont font;
    font.setPointSize(14);
    status = new QLabel(this);
    status->setGeometry(200,300,300,100);
    status->setFont(font);

}

void Login::login_to_server()
{
    int result;
    result = send_account(0);

    switch (result) {
    case 1:
        status->setText("");
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
    case 4:
        status->setStyleSheet("QLabel {color:red}");
        status->setText("Already login!!");
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

void Login::setsocket(int sock)
{
    sockfd = sock;
}

void Login::quit_game(void)
{
    int isreg = -1;
    qInfo("quit games");
    if (sockfd >= 0) {
        write(sockfd,&isreg,sizeof(int));
        ::close(sockfd);
    }
    QApplication::quit();
}
