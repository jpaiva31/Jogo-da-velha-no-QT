#include "janela.h"
#include <fstream>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QHBoxLayout>
#include <QLabel>
janela::janela(QWidget *parent) : QMainWindow(parent)
{
  this->setGeometry(100,100,800,600);
  this->setWindowTitle("Jogo da velha");
  QPalette pal=QPalette();
  pal.setColor(QPalette::Window, Qt::white);
  this->setAutoFillBackground(true);
  this->setPalette(pal);

  salvar= new QPushButton("Salvar", this);
  salvar->setGeometry(690,20,90,40);

  carregar = new QPushButton("Abrir", this);
  carregar->setGeometry(690,80,90,40);

  NewGame = new QPushButton("Novo Jogo", this);
  NewGame->setGeometry(690,140,90,40);

  connect(salvar, SIGNAL(clicked(bool)), this, SLOT(salvarArquivo()));
  connect(carregar, SIGNAL(clicked(bool)), this, SLOT(abrirArquivo()));
  connect(NewGame, SIGNAL(clicked(bool)), this, SLOT(cria()));
  jogo->setPodeTurno(false);
  jogo = tabuleiro::getInstacia();
}

void janela::salvarArquivo(){
  QString caminho = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
  QString fileName = QFileDialog::getSaveFileName(this, "Salvar Jogo", caminho, "(*.txt)");
  string nomeJogo;
  nomeJogo = fileName.toStdString();
  FILE *saveGame;
  saveGame = fopen(nomeJogo.c_str(), "w");
  fprintf(saveGame, "%d", jogo->getTurno());

  for(int i=0;i<9;i++){
    fprintf(saveGame, "%d", jogo->getCasa(i));

    }

    fclose(saveGame);
}

void janela::abrirArquivo(){
  QString caminho = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
  QString fileName = QFileDialog::getOpenFileName(this, "Salvar Jogo", caminho, "(*.txt)");
  string nomeJogo;
  nomeJogo = fileName.toStdString();
  FILE *abrirGame;
  abrirGame = fopen(nomeJogo.c_str(), "r");
  int turno;

   jogo->zeraTudo();
   criaX();

   if (abrirGame!=nullptr){

        for(int i=0;i<10; i++){
            int pieceTest=fgetc(abrirGame);

            switch (pieceTest) {

               case '0':
               if(i==0)
               turno=0;
               break;

               case '1':
               if(i==0) turno=1;
                else{
                 criaElemento(i,0);  //coloca O
               }
               break;

               case '2':
               criaElemento(i,1);  //coloca x
               break;
               default:
               break;
            }
          }
    }
    jogo->setTurno(turno);
    fclose(abrirGame);

}

void janela::cria(){

    turno = new QWidget(this);
    turno->setWindowTitle("Quem começa?");
    turno->setGeometry(100,100,500,500);

    turnoB = new QPushButton("Bola");
    turnoX = new QPushButton("Xis");

    layout1 = new QHBoxLayout;

    layout1->addWidget(turnoB);
    layout1->addWidget(turnoX);
    turno->setStyleSheet(
                "background-color: white;"
                "font-family: Arial;"
                );
    connect(turnoB, SIGNAL(clicked()), this, SLOT(criaJ()));
    connect(turnoX, SIGNAL(clicked()), this, SLOT(criaX()));
    turno->setLayout(layout1);
    turno->show();
    jogo->setPodeTurno(true);
    qWarning() << jogo->getVisivel();


}

void janela::criaJ(){
    turno->close();

   jogo->setVisivel(true);

   if(jogo->vetorPode.size()!=0){
    jogo->zeraTudo();
   }
    jogo->setTurno(0);

    this->update();
}

void janela::criaX(){
    if(jogo->getPodeTurno()==true){
    turno->close();
    }
    jogo->setVisivel(true);

    if(jogo->vetorPode.size()!=0){
     jogo->zeraTudo();
    }
    jogo->setTurno(1);

        this->update();

}

void janela::criaElemento(int a,int b){
    if(b==0){
        novaBola = new bola(a);
        jogo->vetorPecas.push_back(novaBola);
        jogo->setTurno(1);
        jogo->setPode(a-1);
        jogo->setCasa(a-1,1);
    }
    else if(b==1){ novoXis = new xis(a);
        jogo->vetorPecas.push_back(novoXis);
        jogo->setTurno(0);
        jogo->setPode(a-1);
        jogo->setCasa(a-1,2);
}
}

void janela::paintEvent(QPaintEvent *event){
    QLabel *label = new QLabel(this);
    label->setGeometry(320,70,100,100);

    QPainter painter(this);

    if(jogo->getVisivel()==true){
        jogo->criaTabuleiro(painter);
    }

    if(jogo->getVisivel()==true){
       for(unsigned int i =0; i<jogo->vetorPecas.size(); i++){
           jogo->vetorPecas[i]->criaPeca(painter, jogo);
       }
    }


    if(jogo->getVisivel()==true){

       if(jogo->getCasa(0)==jogo->getCasa(4)&&jogo->getCasa(0)==jogo->getCasa(8)&&jogo->getCasa(0)!=0){
          painter.drawLine(230,180,510,420);

          if(jogo->getCasa(0)==1){
            painter.drawText(320,70, "O GANHOU");
            jogo->setDeixa(false);
            jogo->setAux(true);
           }

           if(jogo->getCasa(0)==2){
             painter.drawText(320,70, "X GANHOU");
             jogo->setDeixa(false);
             jogo->setAux(true);
           }
           label->show();
        }


        if(jogo->getCasa(0)==jogo->getCasa(1)&&jogo->getCasa(0)==jogo->getCasa(2)&&jogo->getCasa(0)!=0){
           painter.drawLine(230,180,510,180);

           if(jogo->getCasa(0)==1){
            painter.drawText(320,70, "O GANHOU");
            jogo->setDeixa(false);
            jogo->setAux(true);
           }

           if(jogo->getCasa(0)==2){
               painter.drawText(320,70, "X GANHOU");
               jogo->setDeixa(false);
               jogo->setAux(true);
           }
           label->show();
        }


        if(jogo->getCasa(0)==jogo->getCasa(3)&&jogo->getCasa(0)==jogo->getCasa(6)&&jogo->getCasa(0)!=0){
           painter.drawLine(230,180,230,420);
           if(jogo->getCasa(0)==1){
             painter.drawText(320,70, "O GANHOU");
             jogo->setDeixa(false);
             jogo->setAux(true);
           }

           if(jogo->getCasa(0)==2){
             painter.drawText(320,70, "X GANHOU");
             jogo->setDeixa(false);
             jogo->setAux(true);
           }
           label->show();
       }


        if(jogo->getCasa(1)==jogo->getCasa(4)&&jogo->getCasa(1)==jogo->getCasa(7)&&jogo->getCasa(1)!=0){
           painter.drawLine(360,180,360,420);
           if(jogo->getCasa(1)==1){
            painter.drawText(320,70, "O GANHOU");
            jogo->setDeixa(false);
            jogo->setAux(true);
        }

           if(jogo->getCasa(1)==2){
            painter.drawText(320,70, "X GANHOU");
            jogo->setDeixa(false);
            jogo->setAux(true);
           }
           label->show();
        }


        if(jogo->getCasa(2)==jogo->getCasa(4)&&jogo->getCasa(2)==jogo->getCasa(6)&&jogo->getCasa(2)!=0){
           painter.drawLine(510,180,230,420);
           if(jogo->getCasa(2)==1){
             painter.drawText(320,70, "O GANHOU");
             jogo->setDeixa(false);
             jogo->setAux(true);
         }

           if(jogo->getCasa(2)==2){
            painter.drawText(320,70, "X GANHOU");
            jogo->setDeixa(false);
            jogo->setAux(true);
         }
            label->show();
        }


        if(jogo->getCasa(3)==jogo->getCasa(4)&&jogo->getCasa(3)==jogo->getCasa(5)&&jogo->getCasa(3)!=0){
           painter.drawLine(230,300,510,300);
           if(jogo->getCasa(3)==1){
              painter.drawText(320,70, "O GANHOU");
              jogo->setDeixa(false);
              jogo->setAux(true);
           }

           if(jogo->getCasa(3)==2){
            painter.drawText(320,70, "X GANHOU");
            jogo->setDeixa(false);
            jogo->setAux(true);
           }
          label->show();
        }


        if(jogo->getCasa(2)==jogo->getCasa(5)&&jogo->getCasa(2)==jogo->getCasa(8)&&jogo->getCasa(2)!=0){
           painter.drawLine(510,180,510,420);
           if(jogo->getCasa(2)==1){
             painter.drawText(320,70, "O GANHOU");
             jogo->setDeixa(false);
             jogo->setAux(true);
           }

           if(jogo->getCasa(2)==2){
            painter.drawText(320,70, "X GANHOU");
            jogo->setDeixa(false);
            jogo->setAux(true);
           }
           label->show();
        }


        if(jogo->getCasa(6)==jogo->getCasa(7)&&jogo->getCasa(6)==jogo->getCasa(8)&&jogo->getCasa(6)!=0){
           painter.drawLine(230,420,510,420);
           if(jogo->getCasa(6)==1){
             painter.drawText(320,70, "O GANHOU");
             jogo->setDeixa(false);
             jogo->setAux(true);
           }
           if(jogo->getCasa(6)==2){
             painter.drawText(320,70, "X GANHOU");
             jogo->setDeixa(false);
             jogo->setAux(true);
           }

        }


    int aux=0;
    for(int i=0;i<9;i++){
    if(jogo->getCasa(i)==0){
        aux=0;
        break;
    }
        else{aux=1;}
    }


    if(aux==1&&jogo->getDeixa()==true){
         painter.drawText(320,70, "DEU VELHA");
         jogo->setDeixa(false);
         jogo->setAux(true);
    }

}

    painter.drawRect(10,10,this->width()-20,this->height()-20);
    painter.drawLine(680,10,680,590);

}

void janela::mousePressEvent(QMouseEvent *event)
{

    this->update();

    if(event->x()>190 && event->x()<290 && jogo->getDeixa()==true) {
        if(event->y()>130&&event->y()<240){if(jogo->getPode(0)==0) criaElemento(1,jogo->getTurno());}
        if(event->y()>240&&event->y()<360){if(jogo->getPode(3)==0)  criaElemento(4,jogo->getTurno());}
        if(event->y()>360&&event->y()<420) {if(jogo->getPode(6)==0) criaElemento(7,jogo->getTurno());}
    }


    if(event->x()>290 && event->x()<430 && jogo->getDeixa()==true) {
        if(event->y()>130&&event->y()<240){if(jogo->getPode(1)==0)  criaElemento(2,jogo->getTurno());}
        if(event->y()>240&&event->y()<360){if(jogo->getPode(4)==0)  criaElemento(5,jogo->getTurno());}
        if(event->y()>360&&event->y()<420){if(jogo->getPode(7)==0)  criaElemento(8,jogo->getTurno());}
    }


    if(event->x()>430 && event->x()<530 && jogo->getDeixa()==true) {
        if(event->y()>130&&event->y()<240){if(jogo->getPode(2)==0)  criaElemento(3,jogo->getTurno());}
        if(event->y()>240&&event->y()<360){if(jogo->getPode(5)==0)  criaElemento(6,jogo->getTurno());}
        if(event->y()>360&&event->y()<420){if(jogo->getPode(8)==0)  criaElemento(9,jogo->getTurno());}
    }

    update();
}
