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
}

void RoboWALLE::generateSteps()
{
    int x = posIni.getX();
    int y = posIni.getY();

    steps.push_back(Point(x, y));
    Arvore<Point>* arv;
    arv = new Arvore<Point>;
    arv = caminhar(x,y);

    generateSteps(arv);
}

void RoboWALLE::generateSteps(Arvore<Point>* arv)
{
    vector<Point> step;
    Nodo<Point> *no = new Nodo<Point>;
    no=menorCaminho(arv);

    while(no!=NULL)
    {
        step.push_back(no->info);
        no=no->pai;
    }
    for(int i=step.size(),j=1;i>=0;i--,j++)
    {
        steps[j]=step[i];
    }
}

int RoboWALLE::tamanho(Nodo<Point>* no)
{
    if(!no)
    {
        return 0;
    } else {
        return 1+tamanho(no->pai);
    }
}

Nodo<Point>* RoboWALLE::menorCaminho(Arvore<Point>* arv)
{
    int tamM1,tamM2,tamM3,tamM4;
    Nodo<Point> *no = new Nodo<Point>;
    Nodo<Point> *menor,*menor2,*menor3,*menor4,*ret;
    no=arv->get_raiz();
    menor=estaNoFim(no->baixo);
    menor2=estaNoFim(no->cima);
    menor3=estaNoFim(no->esq);
    menor4=estaNoFim(no->dir);

    tamM1=this->tamanho(menor);
    tamM2=this->tamanho(menor2);
    tamM3=this->tamanho(menor3);
    tamM4=this->tamanho(menor4);

    if(tamM1<tamM2&&tamM1<tamM3&&tamM1<tamM4) ret=menor;
    if(tamM2<tamM1&&tamM2<tamM3&&tamM2<tamM4) ret=menor2;
    if(tamM3<tamM2&&tamM3<tamM1&&tamM3<tamM4) ret=menor3;
    if(tamM4<tamM2&&tamM4<tamM3&&tamM4<tamM1) ret=menor4;

    return ret;
}

Nodo<Point>* RoboWALLE::estaNoFim(Nodo<Point>* no)
{
    if(no!=NULL)
    {
        int x=no->info.getX(),y=no->info.getY();
        if(x >= lab->getWidth() || x < 0 || y >= lab->getHeight() || y < 0)
            return no;
    }
}

Arvore<Point>* RoboWALLE::caminhar(const int x,const int y)
{
    Nodo<Point> *no = new Nodo<Point>;
    Arvore<Point>* arv = new Arvore<Point>;
    if(!ehParede(x,y-1)) caminhar(x,y-1,no->cima,no);
    if(!ehParede(x,y+1)) caminhar(x,y+1,no->baixo,no);
    if(!ehParede(x-1,y)) caminhar(x-1,y,no->esq,no);
    if(!ehParede(x+1,y)) caminhar(x+1,y,no->dir,no);
    arv->set_raiz(no);
    return arv;
}

void RoboWALLE::caminhar(const int x,const int y,Nodo<Point>* no,Nodo<Point>* parent)
{
    no->info.setX(x);
    no->info.setY(y);
    no->pai=parent;

    bool saiu=false;
    if(x >= lab->getWidth() || x < 0 || y >= lab->getHeight() || y < 0)
        saiu = true;

    if(!saiu)
    {
        while(ehParede(x,y))
        {
            if(!ehParedeEsq(x,y))
            {
                rotateRob(getEsq());
            } else {
                rotateRob(getDir());
            }
        }
        switch(sentido)
        {
            case 'N':
                if(!ehParede(x,y-1)) caminhar(x,y-1,no->cima,no);
                break;
            case 'S':
                if(!ehParede(x,y+1)&&!saiu) caminhar(x,y+1,no->baixo,no);
                break;
            case 'L':
                if(!ehParede(x-1,y)&&!saiu) caminhar(x-1,y,no->esq,no);
                break;
            case 'O':
                if(!ehParede(x+1,y)&&!saiu) caminhar(x+1,y,no->dir,no);
                break;
        }
    }
}

char RoboWALLE::getEsq()
{
    char sent=' ';
    switch(sentido)
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
    switch(sentido)
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
    switch(sentido)
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
    switch(sentido)
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

bool RoboWALLE::tentarCaminhar(const int x,const int y)
{
    bool ret=false;
    if(lab->isEmpty(Point(x+1, y))&&sentido=='L') ret=true;
    else if(lab->isEmpty(Point(x, y-1))&&sentido=='N') ret=true;
    else if(lab->isEmpty(Point(x, y+1))&&sentido=='S') ret=true;
    else if(lab->isEmpty(Point(x-1, y))&&sentido=='O') ret=true;
    return ret;
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
    char s[]={'N','S','L','O','D'};
    for(int i=0;i<5;i++)
        if(s[i]==sent) sentido=sent;
}
