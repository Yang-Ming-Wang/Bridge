#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QLabel>
#include <QImage>

class Card : public QWidget
{
    Q_OBJECT
public:
    explicit Card(QWidget *parent = nullptr);
    void setImage(int);

protected:
    void mousePressEvent(QMouseEvent*) override;
    void enterEvent(QEvent*) override;
    void leaveEvent(QEvent*) override;

signals:
    void selected_card(int);
private:
    QLabel *label;
    int cardID;
};

#endif // CARD_H
