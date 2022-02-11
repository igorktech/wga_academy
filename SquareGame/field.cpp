#include "field.h"


FIELD::FIELD(QWidget *parent) : QWidget(parent)
{
    fig = new FIGURE();
    dialog = new QDialog(this); //диалоговое окно для вывода картники в конце
    dialog->setWindowFlags(Qt::Sheet| Qt::FramelessWindowHint);
    dialog->hide();
    movie = new QMovie(":/images/giff.gif");
    processLabel = new QLabel();
    processLabel->setMovie(movie);
    QVBoxLayout* vlay = new QVBoxLayout();
    dialog->setLayout(vlay);
    vlay->setObjectName("v lay");
    button = new QPushButton("new game",this);
    button->setObjectName("new game");
    vlay->addWidget(processLabel);
    vlay->addWidget(button);
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(slotFigureInit()));
    QObject::connect(button,SIGNAL(clicked()),this,SLOT(closeDialog()));
    QObject::connect(this, SIGNAL(signalFigureInit()),
                        this, SLOT(slotFigureInit()), Qt::QueuedConnection);
            emit signalFigureInit();
}

void FIELD::paintEvent(QPaintEvent*event){
    QPainter painter(this);
    if(!end_game){
        for(char k = 0;k<N;k++){
                fig->paintFigure(painter,k, 0, frame[k]);
        }
        for(char i = 0;i<N;i++){
            for(char k = 0;k<N;k++){
                fig->paintFigure(painter,k, i+2, field[i][k]);
            }
        }
    }
}
FIELD::~FIELD(){
    delete fig;
}
void FIELD::slotFigureInit(){
    qsrand(QTime::currentTime().msec());
    field.clear();
    end_game = 0;
    num_step = 0;
    setValue(num_step);
    std::copy(std::begin(level), std::end(level),
              std::back_inserter(field));
    char num = 0;
    char num2 = 0;
    num_yellow = 0;
    num_green = 0;
    num_red = 0;
    for(char i = 0;i<N;i++){  // рандомно заполняем карту (меняем 2 на 2/3/4)
        for(char k = 0;k<N;k++){

            if(field[i][k] == 2){
                            num2++;
                while(num2 != (num_red+num_yellow+num_green)){
                field[i][k] = qrand()%3+2;
                //qDebug()<<num;
                if((field[i][k] == 2)&&(num_red!=5)){
                    num_red++;
                }
                else if((field[i][k] == 3)&&(num_yellow!=5)){
                    num_yellow++;
                }
                else if((field[i][k] == 4)&&(num_green!=5)){
                    num_green++;
                }
            }
            }

        }
    }
    repaint();
}
void FIELD::mousePressEvent(QMouseEvent *event){
if(!end_game){
if((event->QMouseEvent::button()& Qt::LeftButton)){
    cursor_pos = event->QMouseEvent::pos();
    if(cursor_pos.y()>(fig->width()*2)){ // если хотим нажать за игровым полем, пропумкаем этот шаг
    if(flag == 0){
        flag = 1;
        choose[0] =  cursor_pos;


    }
    else if(flag== 1){
                //qDebug()<< cursor_pos;
        flag = 0;
        choose[1] =  cursor_pos;
        if(((field[choose[0].y()/60%7-2][choose[0].x()/60%5]!=1)&&
                (field[choose[1].y()/60%7-2][choose[1].x()/60%5]!=1))&& // если ни один из блоков не является недопустимым для шага

                ((field[choose[0].y()/60%7-2][choose[0].x()/60%5]==0)||
                 (field[choose[1].y()/60%7-2][choose[1].x()/60%5]==0))&& // если один из блоков свободен

                 // предотвращение шага по диагонали и ограничение шагов больше чем на один шаг
                ((abs((choose[1].y()/60%7-2) - (choose[0].y()/60%7-2))==1)||(abs(choose[1].x()/60%5 - choose[0].x()/60%5)==1))&&
                ((abs((choose[1].y()/60%7-2) - (choose[0].y()/60%7-2))==0)||(abs(choose[1].x()/60%5 - choose[0].x()/60%5)==0))){

            char tmp = field[choose[0].y()/60%7-2][choose[0].x()/60%5]; // меняем блоки местами
            field[choose[0].y()/60%7-2][choose[0].x()/60%5] = field[choose[1].y()/60%7-2][choose[1].x()/60%5];
            field[choose[1].y()/60%7-2][choose[1].x()/60%5] = tmp;
            num_step++;
            setValue(num_step);
        }

    }
    end_game = 1;
    for(char k =  0; (k < N); k+=2){ //проверяем, все ли блоки на своих местах
        for(char i = 0; (i < N); i++){
            end_game &= bool(field[i][k] & frame[k]);

        }

    }
    if(!end_game){ //если не все, то перерисовываем картинку
        repaint();
    }
    else{ // иначе выводим изображение
        emit openDialog();
    }
    }
}




}
}

void FIELD::openDialog(){
        movie->start();
        dialog->show();
}
void FIELD::closeDialog(){
    movie->stop();
    dialog->close();
}
