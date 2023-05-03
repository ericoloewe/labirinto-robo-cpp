#ifndef ROBOB9_H
#define ROBOB9_H

#include "Labirinto.h"
#include "Robo.h"
#include "Texture.h"

using namespace std;

class RoboB9: public Robo {
	public:
        RoboB9(const Point& posIni, Labirinto *l, int maxSteps);	// Construtor
        void draw();
        void generateSteps();
        vector<Point> getSteps();
    private:
        TEX* roboTex; // id de textura do robo
};

#endif
