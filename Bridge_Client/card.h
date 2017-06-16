#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QLabel>
#include <QImage>

class Card : public QWidget
{
    Q_OBJECT
public:
    explicit Card(QWidget *parent = nullptr,int idx = 0);
    void setImage(int);

protected:
    void mousePressEvent(QMouseEvent*) override;
    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;

signals:
    void selected_card(int,int);
private:
    QLabel *label;
    int cardID,index;
};

#endif // CARD_H
