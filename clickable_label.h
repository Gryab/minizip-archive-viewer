#ifndef CLICKABLE_LABEL_H
#define CLICKABLE_LABEL_H

#include <QLabel>
#include <QWidget>
#include <Qt>

class ClickableLabel : public QLabel { 
    Q_OBJECT 

public:
    explicit ClickableLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags()) : QLabel(parent) {};
    ~ClickableLabel(){};

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event)
    {
        emit clicked();
    };

};

#endif
