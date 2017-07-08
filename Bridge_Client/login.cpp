#include "login.h"

Login::Login(QWidget *parent) : Subscriber(parent)
{
    QFont font;
    font.setPointSize(14);

    exitbtn = new QPushButton("Exit");
    exitbtn->setFixedHeight(100);
    exitbtn->setFont(font);
    exitbtn->setToolTip("Quit the Game");
    connect(exitbtn,SIGNAL(clicked()),this,SLOT(quit_game()));

    loginbtn = new QPushButton("Login");
    loginbtn->setFixedHeight(100);
    loginbtn->setFont(font);
    loginbtn->setToolTip("Login to the Server");
    connect(loginbtn,SIGNAL(clicked()),this,SLOT(login_to_server()));

    registerbtn = new QPushButton("Register");
    registerbtn->setFixedHeight(100);
    registerbtn->setFont(font);
    registerbtn->setToolTip("Register a Account");
    connect(registerbtn,SIGNAL(clicked()),this,SLOT(register_to_server()));

    QRegExpValidator *validator = new QRegExpValidator(QRegExp("\\w+"));

    account = new QLineEdit(this);
    account->setPlaceholderText("your account:");
    account->setFixedSize(300,50);
    account->setMaxLength(15);
    account->setValidator(validator);

    password = new QLineEdit(this);
    password->setPlaceholderText("your password:");
    password->setEchoMode(QLineEdit::Password);
    password->setFixedSize(300,50);
    password->setMaxLength(15);
    password->setValidator(validator);

    status = new QLabel(this);
    status->setFixedSize(300,100);
    status->setFont(font);

    hlayout = new QHBoxLayout;
    hlayout->addWidget(exitbtn);
    hlayout->addWidget(loginbtn);
    hlayout->addWidget(registerbtn);
    hlayout->setSpacing(100);

    vlayout = new QVBoxLayout;
    vlayout->addWidget(account);
    vlayout->addWidget(password);
    vlayout->addWidget(status);
    vlayout->addLayout(hlayout);
    vlayout->setMargin(50);

    setLayout(vlayout);
}

void Login::login_to_server()
{
    int result;
    char acc[15],pwd[15];
    strcpy(acc,account->text().toStdString().c_str());
    strcpy(pwd,password->text().toStdString().c_str());
    result = thread->send_account(0,acc,pwd);

    switch (result) {
    case 1:
        status->setText("");
        emit stage_change(1);
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
    char acc[15],pwd[15];
    strcpy(acc,account->text().toStdString().c_str());
    strcpy(pwd,password->text().toStdString().c_str());
    result = thread->send_account(1,acc,pwd);

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

void Login::quit_game(void)
{
    thread->send_quit();
    QApplication::quit();
}
