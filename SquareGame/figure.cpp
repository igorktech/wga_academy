#include "figure.h"

FIGURE::FIGURE()
{

}

void FIGURE::paintFigure(QPainter & painter,int x,int y,char num){
painter.fillRect(x*W,y*W,W-2,W-2,mass[num]);
}
