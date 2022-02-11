#ifndef FRAME_H
#define FRAME_H

#include <QWidget>
#include "figure.h"
#include <QPaintEvent>
class FRAME : public QWidget
{
    Q_OBJECT
    FIGURE *fig;

public:
    explicit FRAME(QWidget *parent = nullptr);
~FRAME();
    void paintEvent(QPaintEvent*event);
signals:

};

#endif // FRAME_H
