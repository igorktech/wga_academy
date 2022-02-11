#ifndef FIELD_H
#define FIELD_H

#include <QMouseEvent>
#include <QTimer>
#include <QWidget>
#include <QPoint>
#include <QPainter>
#include <figure.h>
#include <QDialog>
#include <QtDebug>
#include <QLabel>
#include <QMovie>
#include <QVBoxLayout>
#include <QPushButton>
#include <QVector>
#include <QTime>
#define N 5
class FIELD : public QWidget  //класс поля
{
    Q_OBJECT
    FIGURE *fig; //фигурка
    QDialog* dialog;
    QMovie *movie;
    QLabel *processLabel;
    QPushButton * button;
    char num_yellow = 0;
    char num_green = 0;
    char num_red = 0;
    char frame[5] = {2,0,3,0,4 // расположение, которому должны соответствовать фигурки
                    };
    uint num_step=0;
    QVector<QVector<char>> field; //поле, которое в игре работает с перестановками
    QVector<QVector<char>> level ={{2,1,2,1,2},  //исходное поле
                       {2,0,2,0,2},
                       {2,1,2,1,2},
                       {2,0,2,0,2},
                       {2,1,2,1,2}
                      };
    QPoint cursor_pos; // позиция курсора
    QPoint choose[2]; //две ячейки, которые нужно поменять местами
    bool flag = 0;
    bool end_game = 0; // идет ли игра
    public:
        ~FIELD();
        explicit FIELD(QWidget *parent = nullptr);
        void paintEvent(QPaintEvent*event);// отрысовка картинки
        public slots:
        void closeDialog(); // закрытие окна
        void slotFigureInit();  //инициализация поля
        void openDialog(); // открытие картинки в новом окне
        virtual void mousePressEvent(QMouseEvent *event) override;
    signals:
        void setValue(int); //изменение значения на индикаторе
        void signalFigureInit();
        void drawOnFrame();
};

#endif // FIELD_H
