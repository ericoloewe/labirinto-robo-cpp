#ifndef ROBO_H
#define ROBO_H

#include <vector>
#include "Point.h"
#include "Texture.h"

using namespace std;

// Classe que define a interface publica de um robo qualquer
// Os 3 robos devem obrigatoriamente implementar esses metodos

class Robo
{
    public:

    Robo(const Point& posIni, Labirinto* lab, int maxSteps)
    {
        this->posIni = posIni;
        this->lab = lab;
        this->maxSteps = maxSteps;
    }
	virtual void draw() = 0;
    void move(const Point &pos) { this->pos = pos; }
	virtual void generateSteps() = 0;
	vector<Point> getSteps() { return steps; }

    protected:

    Point posIni, pos;
    Labirinto* lab;
    int maxSteps;
	vector<Point> steps;
};

#endif
