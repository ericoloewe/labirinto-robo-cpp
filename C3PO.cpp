#include "C3PO.h"
#include "GL.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <time.h>

using namespace std;

RoboC3PO::RoboC3PO(const Point& posIni, Labirinto *l, int maxSteps) : Robo(posIni, l, maxSteps)
{
    srand(time(NULL));
    roboTex = CarregaTextura("C3PO.jpg", false);
    sentido='L';
}

void RoboC3PO::generateSteps()
{
    int cont = 1;
    bool saiu = false;
    int x = posIni.getX();
    int y = posIni.getY();
    steps.push_back(Point(x,y)); //Coloca o ponto inicial no vector steps
    int dx, dy;
    while(!saiu && cont < maxSteps) //verifica se o robo ja saiu, ou se o numero de passos foi ultrapassado
    {
        dx=dy=0;
        caminhar(x,y,dx,dy); //verifica aonde é possivel que o robo caminhe
        x += dx;
        y += dy;
        steps.push_back(Point(x, y)); //após todo o processo, coloca os passos no vector steps criado
        cont++;
        if(x >= lab->getWidth() || x < 0 || y >= lab->getHeight() || y < 0) //verifica se o mesmo ja saiu
            saiu = true;
    }
}

void RoboC3PO::caminhar(const int x,const int y,int& dx, int& dy)
{
    bool ok=true;
    while(ok) // loop criado para enquanto não for feito algo, o programa nao saia dessa função
    {
        if(!ehParede(x,y))  // verifica se não é parede a frente
        {
            switch(sentido) //caso sim, ele anda para o sentido indicado
            {
            case 'N':
                dy=-1;
                break;
            case 'S':
                dy=1;
                break;
            case 'L':
                dx=1;
                break;
            case 'O':
                dx=-1;
                break;
            }
            ok=false; //ele seta o "ok" como false para ele sair do loop
        }
        else //caso for uma parede a frente ele faz os seguintes passos
        {
            if(!ehParedeDir(x,y)) //verifica se não é uma parede a direita
            {
                rotateRob(getDir()); //caso não for, ele rotaciona o robo para a direita
            } else { // caso for uma parede a direita, ele verifica se não é uma parede a esquerda
                rotateRob(getEsq());   //caso nao for, ele gira o robo para a esquerda
            }
        }
    }
}

char RoboC3PO::getEsq()
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

char RoboC3PO::getDir()
{
    char sent=' ';
    switch(sentido) //verifica o sentido e retorna a esquerda do robo
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

bool RoboC3PO::ehParedeEsq(const int x,const int y)
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

bool RoboC3PO::ehParedeDir(const int x,const int y)
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

bool RoboC3PO::tentarCaminhar(const int x,const int y) //verifica o sentido e retorna se é possivel caminhar para o mesmo(que a frente nao ha parede)
{
    bool ret=false;
    if(lab->isEmpty(Point(x+1, y))&&sentido=='L') ret=true;
    else if(lab->isEmpty(Point(x, y-1))&&sentido=='N') ret=true;
    else if(lab->isEmpty(Point(x, y+1))&&sentido=='S') ret=true;
    else if(lab->isEmpty(Point(x-1, y))&&sentido=='O') ret=true;
    return ret;
}

void RoboC3PO::draw()
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

void RoboC3PO::rotateRob(char sent)
{
    char s[]={'N','S','L','O'};
    for(int i=0;i<4;i++) //verifica o sentido recebido por parametro, se o mesmo é possivel ser setado no sentido da classe
        if(s[i]==sent) sentido=sent;
}
