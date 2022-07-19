#ifndef BOLA_H
#define BOLA_H
#include"pecas.h"


class bola:public pecas
{
public:
    bola(int tipo);
    void criaPeca(QPainter &painter,tabuleiro *tab) override;

};

#endif // BOLA_H
