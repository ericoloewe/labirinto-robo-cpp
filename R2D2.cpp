#include "R2D2.h"
#include "GL.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <time.h>

using namespace std;

RoboR2D2::RoboR2D2(const Point& posIni, Labirinto *l, int maxSteps) : Robo(posIni, l, maxSteps)
{
    srand(time(NULL));
    roboTex = CarregaTextura("R2D2.jpg", false);
    sentido='N';
}

void RoboR2D2::generateSteps()
{
    bool saiu = false;
    int x = posIni.getX();
    int y = posIni.getY();
    steps.push_back(Point(x,y)); //Coloca o ponto inicial no vector steps
    int dx, dy;
    while(!saiu) //enquanto o robo R2D2 nao sair ele chama os passsos a seguir para verificar aonde é possivel ele caminhar
    {
        dx=dy=0;
        caminhar(x,y,dx,dy); //verifica aonde é possivel que o robo caminhe, sempre verificando se ele esta com a mão a parede esquerda
        x += dx;
        y += dy;
        steps.push_back(Point(x, y)); //após todo o processo, coloca os passos no vector steps criado
        if(x >= lab->getWidth() || x < 0 || y >= lab->getHeight() || y < 0) //verifica se o mesmo ja saiu
            saiu = true;
    }
}

void RoboR2D2::caminhar(const int x,const int y,int& dx, int& dy)
{
    bool ok=true,okk=false;
    while(ok) // loop criado para enquanto não for feito algo, o programa nao saia dessa função
    {
        if(!ehParede(x,y)&&(ehParedeEsq(x,y)||okk)) // verifica se não é parede a frente, e se ele esta com a mão a esquerda
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
        else //caso for uma parede a frente, ou ele nao estiver com a mao a frente ele faz os seguintes passos
        {
            if(ehParedeEsq(x,y)) //verifica se é parede na esquerda
            {
                while(ehParede(x,y)) //caso sim verifica se é parede a frente
                {
                    if(!ehParedeEsq(x,y)) //se nao for parede a esquerda ele rotaciona o robo a esquerda
                    {
                        rotateRob(getEsq());
                    } else { //caso for parede a esquerda ele rotaciona o robo a direita
                        rotateRob(getDir());
                    }
                }
            } else{ //caso nao for parede a frente ele rotaciona o robo a esquerda, para continuar com a devida mao a parede
                rotateRob(getEsq());
                okk=true;
            }
        }
    }
}

char RoboR2D2::getEsq()
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

char RoboR2D2::getDir()
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

bool RoboR2D2::ehParedeEsq(const int x,const int y)
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

bool RoboR2D2::ehParedeDir(const int x,const int y)
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

bool RoboR2D2::tentarCaminhar(const int x,const int y) //verifica o sentido e retorna se é possivel caminhar para o mesmo(que a frente nao ha parede)
{
    bool ret=false;
    if(lab->isEmpty(Point(x+1, y))&&sentido=='L') ret=true;
    else if(lab->isEmpty(Point(x, y-1))&&sentido=='N') ret=true;
    else if(lab->isEmpty(Point(x, y+1))&&sentido=='S') ret=true;
    else if(lab->isEmpty(Point(x-1, y))&&sentido=='O') ret=true;
    return ret;
}

void RoboR2D2::draw()
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

void RoboR2D2::rotateRob(char sent)
{
    char s[]={'N','S','L','O'};
    for(int i=0;i<4;i++) //verifica o sentido recebido por parametro, se o mesmo é possivel ser setado no sentido da classe
        if(s[i]==sent) sentido=sent;
}
