#include "frame.h"
#include "QPainter"
FRAME::FRAME(QWidget *parent) : QWidget(parent)
{
    fig = new FIGURE();

}

FRAME::~FRAME(){
    delete fig;
}
void FRAME::paintEvent(QPaintEvent*event){
   QPainter painter(this);
        for(char k = 0;k<5;k++){
                fig->paintFigure(painter,k, 0, frame[k]);
        }
}
