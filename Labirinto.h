#ifndef LABIRINTO_H
#define LABIRINTO_H

#include "Point.h"
#include <string>

using namespace std;

// Classe que define a interface de um labirinto:os
// metodos virtual devem ser implementados pelas
// classes derivadas

class Labirinto
{
    public:
    virtual bool isEmpty(const Point& ponto) const = 0;
	virtual int  getWidth() = 0;
	virtual int  getHeight() = 0;
    virtual int  getRobot() = 0;
    virtual Point getIniPos() = 0;
	virtual void loadMaze(string arquivo) = 0;
	//virtual char getlab(int i, int j) = 0;
};

#endif
