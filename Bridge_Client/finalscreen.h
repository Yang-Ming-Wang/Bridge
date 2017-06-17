#ifndef FINALSCREEN_H
#define FINALSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class FinalScreen : public QWidget
{
    Q_OBJECT
public:
    explicit FinalScreen(QWidget *parent = nullptr);

signals:
    void back_to_lobby(void);
public slots:
    void show_everything(int);
private slots:
    void hide_everything(void);
private:
    QLabel *label;
    QPushButton *back;
};

#endif // FINALSCREEN_H
