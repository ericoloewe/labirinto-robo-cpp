#ifndef WALLE_H
#define WALLE_H

#include "Labirinto.h"
#include "Robo.h"
#include "Texture.h"
#include "Arvore.h"

using namespace std;

class RoboWALLE: public Robo {
	public:
        RoboWALLE(const Point& posIni, Labirinto *l, int maxSteps);	// Construtor
        void draw();
        void generateSteps();
        void generateSteps(Arvore<Point>* arv);
        vector<Point> getSteps();
        Nodo<Point>* menorCaminho(Arvore<Point>* arv);
        Nodo<Point>* estaNoFim(Nodo<Point>* no);
        int tamanho(Nodo<Point>* no);
        char getSent() { return sentido; }
        void rotateRob(char sent);
        Arvore<Point>* caminhar(const int x,const int y);
        void caminhar(const int x,const int y,Nodo<Point>* no,Nodo<Point>* parent);
        bool tentarCaminhar(const int x,const int y);
        bool ehParede(const int x,const int y){ return !tentarCaminhar(x,y); }
        bool ehParedeEsq(const int x,const int y);
        bool ehParedeDir(const int x,const int y);
        char getEsq();
        char getDir();
    private:
        TEX* roboTex; // id de textura do robo
        char sentido;
};

#endif
