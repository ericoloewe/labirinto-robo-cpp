#include "RoboB9.h"
#include "GL.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <time.h>

using namespace std;

RoboB9::RoboB9(const Point& posIni, Labirinto *l, int maxSteps) : Robo(posIni, l, maxSteps)
{
    srand(time(NULL));
    roboTex = CarregaTextura("b9.jpg", false);
}

void RoboB9::generateSteps()
{
    int cont = 1;
    bool saiu = false;
    int x = posIni.getX();
    int y = posIni.getY();
    steps.push_back(Point(x,y));
    while(!saiu && cont < maxSteps)
    {
        int dx, dy;
        do {
            int dir = rand()%4;
            dx = 0;
            dy = 0;
            switch(dir) {
                case 0:	dx = 1;
                    break;
                case 1:	dx = -1;
                    break;
                case 2:	dy = 1;
                    break;
                case 3: dy = -1;
                    break;
            }
        }
        while(!lab->isEmpty(Point(x+dx, y+dy)));
        x += dx;
        y += dy;
        steps.push_back(Point(x, y));
        cont++;
        if(x >= lab->getWidth() || x < 0
                || y >= lab->getHeight() || y < 0)
            saiu = true;
    }
}

void RoboB9::draw()
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
