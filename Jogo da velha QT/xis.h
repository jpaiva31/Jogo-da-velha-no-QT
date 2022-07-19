#ifndef XIS_H
#define XIS_H

#include"pecas.h"


class xis:public pecas
{
public:
    xis(int tipo);
    void criaPeca(QPainter &painter,tabuleiro *tab) override;
};

#endif // XIS_H
