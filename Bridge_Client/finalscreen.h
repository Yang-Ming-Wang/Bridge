#ifndef FINALSCREEN_H
#define FINALSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QPushButton>

class FinalScreen : public QWidget
{
    Q_OBJECT
public:
    explicit FinalScreen(QWidget *parent = nullptr);

signals:
    void stage_change(int);
public slots:
    void setWinner(int);
private slots:
    void back_to_lobby(void);
private:
    QLabel *label;
    QPushButton *back;
};

#endif // FINALSCREEN_H
