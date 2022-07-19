#ifndef JANELA_H
#define JANELA_H
#include <QMainWindow>
#include <QpushButton>
#include <QTextEdit>
#include <QPainter>
#include <QMouseEvent>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include "tabuleiro.h"
#include "xis.h"
#include "bola.h"
#include <QStandardPaths>
#include <QFileDialog>
#include <QMessageBox>
class janela : public QMainWindow
{
    tabuleiro *jogo;
    Q_OBJECT
    QPushButton *salvar,*carregar, *NewGame,*turnoX,*turnoB;
    QHBoxLayout * layout1;
    QTextEdit *editor;
    QWidget *turno,*ganha;
    xis *novoXis;
    bola *novaBola;
    public:
    explicit janela(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);


public slots:
    void paintEvent(QPaintEvent *event);
    void salvarArquivo();
    void abrirArquivo();
    void cria();
    void criaJ();
    void criaX();
    void criaElemento(int a, int b);

signals:

};

#endif // JANELA_H
