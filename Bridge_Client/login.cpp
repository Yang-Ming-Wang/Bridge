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
    connect(loginbtn,SIGNAL(clicked()),this,SLOT(connect_to_server()));

    registerbtn = new QPushButton("Register",parent);
    registerbtn->setGeometry(550,450,200,100);
    registerbtn->setToolTip("Register a Account");

}

int Login::connect_to_server()
{
    int sockfd;
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0 )
        printf("socket error\n");

    bzero(&servaddr,sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9877);

    if (inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr) <= 0)
        printf("inet_ption error for 127.0.0.1\n");

    if (::connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr)) < 0)
        printf("connect error\n");
    else
        printf("Successful Login.\n");
    //test socket
    char buf[10] = "Client";
    write(sockfd,buf,10);
    return sockfd;
}
