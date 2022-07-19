#include "xis.h"
#include <QLabel>
#include <QDebug>
xis::xis(int p):pecas(p)
{
    posicao=p;
}

void xis::criaPeca(QPainter &painter,tabuleiro *tab)
{
    int x,y;

    if(posicao==1||posicao==4||posicao==7)  x=180;
    if(posicao==2||posicao==5||posicao==8)  x=310;
    if(posicao==3||posicao==6||posicao==9)  x=460;
    if(posicao==1||posicao==2||posicao==3)  y=130;
    if(posicao==4||posicao==5||posicao==6)  y=250;
    if(posicao==7||posicao==8||posicao==9)  y=370;

    painter.drawImage(QRect(x, y, 100, 100), QImage("C:/Users/Alunos/Desktop/Jogo da velha QT/xis.png"));
}

