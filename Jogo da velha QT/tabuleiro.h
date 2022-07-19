#ifndef TABULEIRO_H
#define TABULEIRO_H

#include <QMainWindow>
#include <QWidget>
#include <QPainter>
#include "pecas.h"
using namespace std;

class tabuleiro
{
    protected:
    int turno;
    bool visivel=false;
    bool selecionado,aux;
    bool deixaClicar=true;
    bool pode=false;
    static tabuleiro *instanciaVelha;
public:
    vector<pecas*> vetorPecas;
    vector<int> vetorCasas;
    vector<int> vetorPode;
    tabuleiro(bool v=false);
    void criaTabuleiro(QPainter &painter);
    void setVisivel(bool V){visivel = V;}
    void setSelecionado(bool S){selecionado = S;}
    int getPosicao(){return 50;}
    bool getVisivel(){return visivel;}
    bool getSelecionado(){return selecionado;}
    void setTurno(int a){turno=a;}
    int getTurno(){return turno;}
    bool temPeca(int x, int y);
    void setPode(int x){vetorPode[x]=1;};
    int getPode(int x){return vetorPode[x];}
    void setCasa(int x, int y){vetorCasas[x]=y;}
    int getCasa(int x){return vetorCasas[x];}
    void zeraTudo();
    void setDeixa(bool a){deixaClicar=a;}
    bool getDeixa(){return deixaClicar;}
    static tabuleiro *getInstacia();
    bool getAux(){return aux;}
    void setAux(bool a){aux=a;}
    void setPodeTurno(bool a){pode=a;}
    bool getPodeTurno(){return pode;}
};

#endif // TABULEIRO_H

