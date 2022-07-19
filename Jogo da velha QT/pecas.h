#ifndef PECAS_H
#define PECAS_H

#include<QPaintEvent>
#include<QPainter>

class tabuleiro;

class pecas
{
    int tipoPeca;
public:
    int posicao;
    pecas(int tipo);

    void setPosicao(int x, tabuleiro *tab);
    int getPosicao(){return posicao;}
    int getTipoPeca(){return tipoPeca;}

    virtual void criaPeca(QPainter &painter, tabuleiro *tab) = 0;

};

#endif // PECAS_H
