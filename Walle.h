#ifndef WALLE_H
#define WALLE_H

#include "Labirinto.h"
#include "Robo.h"
#include "Texture.h"
#include "Arvore.h"
#include <list>

using namespace std;

class RoboWALLE: public Robo {
	public:
        RoboWALLE(const Point& posIni, Labirinto *l, int maxSteps);	// Construtor
        void draw();
        void generateSteps(); //Gera os passos que o robo deve seguir
        vector<Point> getSteps(); //retorna os passos que o robo deve seguir
        char getSent() { return sentido; } //retorna o sentido em que o robo se encontra
        void rotateRob(char sent); //Gira o Robo para o sentido indica(se possivel)
        void caminhar();
        void caminhar(Nodo<Point>* no);
        void geraArvore(const int x,const int y);
        void geraArvore(const int x,const int y,Nodo<Point>*& no,Nodo<Point>*& parent);
        bool tentarCaminhar(const int x,const int y); //verifica se � possivel caminhar para o sentido indicado, retornando true se possivel
        bool ehParede(const int x,const int y){ return !tentarCaminhar(x,y); } //verifica se � o sentido indicado � parede retornando true se sim
        bool ehParedeEsq(const int x,const int y); //verifica se � parede na esquerda retornando true se sim
        bool ehParedeDir(const int x,const int y); //verifica se � parede na direita retornando true se sim
        bool ehPontoAnt(int x, int y);
        char getEsq(); //Retorna o sentido da esquerda do que o robo se encontra
        char getDir(); //Retorna o sentido da direita do que o robo se encontra
        char getBack(); //Retorna o sentido contrario do que o robo se encontra
    private:
        TEX* roboTex; // id de textura do robo
        char sentido; //sentido atual onde o robo se encontra
        Arvore<Point>* arv;
        list<Point> *way,*tree;
};

#endif
