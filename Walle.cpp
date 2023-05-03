#include "Walle.h"
#include "GL.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <time.h>

using namespace std;

RoboWALLE::RoboWALLE(const Point& posIni, Labirinto *l, int maxSteps) : Robo(posIni, l, maxSteps)
{
    srand(time(NULL));
    roboTex = CarregaTextura("walle.jpg", false);
    sentido='N';
    arv=new Arvore<Point>;
    tree = new list<Point>;
    way = new list<Point>;
}

void RoboWALLE::generateSteps()
{
    int x = posIni.getX();
    int y = posIni.getY();
    steps.push_back(Point(x,y)); //Coloca o ponto inicial no vector steps
    geraArvore(x,y);
    caminhar();
}

void RoboWALLE::caminhar()
{
    caminhar(arv->get_raiz());

    list<Point>::iterator it=way->begin();
    it++;
    while(it!=way->end())
    {
        steps.push_back(*it);
        it++;
    }
    int i=arv->tamanho();
}

void RoboWALLE::caminhar(Nodo<Point>* no)
{
    Nodo<Point>* ret=new Nodo<Point>;
    int x,y,fim=0;
    if(no!=NULL)
    {
        //no=new Nodo<Point>;
        x=no->info.getX();
        y=no->info.getY();
        if(x >= lab->getWidth() || x < 0 || y >= lab->getHeight() || y < 0)
        {
            fim++;
            list<Point> *li= new list<Point>;
            while(no!=NULL)
            {
                li->push_front(no->info);
                no=no->pai;
            }
            if(li->size()<way->size()||fim==1)
            {
                way=li;
            }
        } else {
            caminhar(no->cima);
            caminhar(no->baixo);
            caminhar(no->esq);
            caminhar(no->dir);
        }
    }
}

void RoboWALLE::geraArvore(const int x,const int y)
{
    Nodo<Point> *no = new Nodo<Point>;
    if(!ehParede(x,y-1)) geraArvore(x,y-1,no->cima,no);
    if(!ehParede(x,y+1)) geraArvore(x,y+1,no->baixo,no);
    if(!ehParede(x-1,y)) geraArvore(x-1,y,no->esq,no);
    if(!ehParede(x+1,y)) geraArvore(x+1,y,no->dir,no);
    arv->set_raiz(no);
}

void RoboWALLE::geraArvore(const int x,const int y,Nodo<Point>*& no,Nodo<Point>*& parent)
{
    no=new Nodo<Point>;
    //if(!arv->jaExiste(no->info)||parent==arv->get_raiz())

    no->info.setX(x);
    no->info.setY(y);
    no->pai=parent;
    tree->push_back(no->info);

    bool saiu=false;
    if(x >= lab->getWidth() || x < 0 || y >= lab->getHeight() || y < 0)
        saiu = true;

    /*if(!ehParede(x,y-1)&&!saiu&&!arv->jaExiste(Point(x,y-1))) geraArvore(x,y-1,no->cima,no);
    if(!ehParede(x,y+1)&&!saiu&&!arv->jaExiste(Point(x,y+1))) geraArvore(x,y+1,no->baixo,no);
    if(!ehParede(x-1,y)&&!saiu&&!arv->jaExiste(Point(x-1,y))) geraArvore(x-1,y,no->esq,no);
    if(!ehParede(x+1,y)&&!saiu&&!arv->jaExiste(Point(x+1,y))) geraArvore(x+1,y,no->dir,no);*/

    if(!ehParede(x,y-1)&&!saiu&&(!ehPontoAnt(x,y-1)||parent==arv->get_raiz())) geraArvore(x,y-1,no->cima,no);
    if(!ehParede(x,y+1)&&!saiu&&(!ehPontoAnt(x,y+1)||parent==arv->get_raiz())) geraArvore(x,y+1,no->baixo,no);
    if(!ehParede(x-1,y)&&!saiu&&(!ehPontoAnt(x-1,y)||parent==arv->get_raiz())) geraArvore(x-1,y,no->esq,no);
    if(!ehParede(x+1,y)&&!saiu&&(!ehPontoAnt(x+1,y)||parent==arv->get_raiz())) geraArvore(x+1,y,no->dir,no);
}

bool RoboWALLE::ehPontoAnt(int x,int y)
{
    bool ret=false;

    for(list<Point>::iterator it=tree->begin();it!=tree->end();it++) //faz uma varredura na lista que é gerada enquanto geramos a arvore
    {
        if(it->getX()==x&&it->getY()==y) ret=true; //verifica se a posição x e y são igual
    }
    /*if(no!=NULL)
        if(no->info.getX()==x&&no->info.getX()==y)
            ret=true;
    if(no->pai!=NULL)
        if(no->pai->info.getX()==x&&no->pai->info.getX()==y)
            ret=true;*/
    return ret;
}

char RoboWALLE::getBack()
{
    char sent=' ';
    switch(sentido) //verifica o sentido e retorna a direita do robo
    {
        case 'N':
            sent='S';
            break;
        case 'L':
            sent='O';
            break;
        case 'S':
            sent='N';
            break;
        case 'O':
            sent='L';
            break;
    }
    return sent;
}

char RoboWALLE::getEsq()
{
    char sent=' ';
    switch(sentido) //verifica o sentido e retorna a direita do robo
    {
        case 'N':
            sent='O';
            break;
        case 'L':
            sent='N';
            break;
        case 'S':
            sent='L';
            break;
        case 'O':
            sent='S';
            break;
    }
    return sent;
}

char RoboWALLE::getDir()
{
    char sent=' ';
    switch(sentido) //verifica o sentido e retorna a direita do robo
    {
        case 'N':
            sent='L';
            break;
        case 'L':
            sent='S';
            break;
        case 'S':
            sent='O';
            break;
        case 'O':
            sent='N';
            break;
    }
    return sent;
}

bool RoboWALLE::ehParedeEsq(const int x,const int y)
{
    bool ret=true;
    switch(sentido) //verifica o sentido e retorna se for parede na esquerda ou nao
    {
        case 'N':
            if(lab->isEmpty(Point(x-1, y))) ret=false;
            break;
        case 'L':
            if(lab->isEmpty(Point(x, y-1))) ret=false;
            break;
        case 'S':
            if(lab->isEmpty(Point(x+1, y))) ret=false;
            break;
        case 'O':
            if(lab->isEmpty(Point(x, y+1))) ret=false;
            break;
    }
    return ret;
}

bool RoboWALLE::ehParedeDir(const int x,const int y)
{
    bool ret=true;
    switch(sentido) //verifica o sentido e retorna se for parede na direita ou nao
    {
        case 'N':
            if(lab->isEmpty(Point(x+1, y))) ret=false;
            break;
        case 'L':
            if(lab->isEmpty(Point(x, y+1))) ret=false;
            break;
        case 'S':
            if(lab->isEmpty(Point(x-1, y))) ret=false;
            break;
        case 'O':
            if(lab->isEmpty(Point(x, y-1))) ret=false;
            break;
    }
    return ret;
}

bool RoboWALLE::tentarCaminhar(const int x,const int y) //verifica o sentido e retorna se é possivel caminhar para o mesmo(que a frente nao ha parede)
{
    return (lab->isEmpty(Point(x, y)));
}

void RoboWALLE::draw()
{
    float rx,ry;
    float deltax = GL::getDeltaX();
    float deltay = GL::getDeltaY();
    rx = pos.getX() * deltax;
    ry = pos.getY() * deltay;
    GL::enableTexture(roboTex->texid);
    GL::setColor(255,255,255);
    GL::drawRect(rx, ry, rx+deltax, ry+deltay);
    GL::disableTexture();
}

void RoboWALLE::rotateRob(char sent)
{
    char s[]={'N','S','L','O'};
    for(int i=0;i<4;i++) //verifica o sentido recebido por parametro, se o mesmo é possivel ser setado no sentido da classe
        if(s[i]==sent) sentido=sent;
}
