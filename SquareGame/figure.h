#ifndef FIGURE_H
#define FIGURE_H

#include <QColor>
#include <QPainter>


class FIGURE //класс фигурки, содержит цвета фигурок
{
         uint W = 60;
         QColor mass[5] = {
             QColor(176,176,176),
             QColor(0,100,100),
             QColor(230,0,0),
             QColor(230,230,50),
             QColor(50,230,38)
                          };
public:
    FIGURE();
 void paintFigure(QPainter & painter,int x,int y,char num); //отрисовка каждой фигурки
 uint width(void){
     return W;
 }
};

#endif // FIGURE_H
