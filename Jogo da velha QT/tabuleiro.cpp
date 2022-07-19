#include "tabuleiro.h"
#include <QDebug>
tabuleiro::tabuleiro( bool V)
{
    selecionado = false;
    visivel = false;
    for(int i=0;i<9;i++){
        vetorPode.push_back(0);
        vetorCasas.push_back(0);
    }

}

void tabuleiro::criaTabuleiro(QPainter &painter)
{
    visivel=true;

    painter.drawLine(290,130,290,470);
    painter.drawLine(430,130,430,470);
    painter.drawLine(190,240,530,240);
    painter.drawLine(190,360,530,360);
}

void tabuleiro::zeraTudo()
{
    aux=false;

    for(int i=0;i<vetorCasas.size();i++){
        vector<pecas*> aux;
        vetorCasas[i]=0;
        vetorPecas=aux;
        vetorPode[i]=0;
        deixaClicar=true;
    }

}


tabuleiro *tabuleiro::getInstacia()
{
    if(instanciaVelha == nullptr)
        instanciaVelha = new tabuleiro(false);

    return instanciaVelha;
}

tabuleiro *tabuleiro::instanciaVelha = nullptr;


