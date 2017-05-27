#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setFixedSize(800,600);

    login = new Login(this);

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
    char buf[10] = "Client\n";
    write(sockfd,buf,10);
}

MainWindow::~MainWindow()
{

}
