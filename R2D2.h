#ifndef R2D2_H
#define R2D2_H

#include "Labirinto.h"
#include "Robo.h"
#include "Texture.h"

using namespace std;

class RoboR2D2: public Robo {
	public:
        RoboR2D2(const Point& posIni, Labirinto *l, int maxSteps);	// Construtor
        void draw();
        void generateSteps(); //Gera os passos que o robo deve seguir
        vector<Point> getSteps(); //retorna os passos que o robo deve seguir
        char getSent() { return sentido; } //retorna o sentido em que o robo se encontra
        void rotateRob(char sent); //Gira o Robo para o sentido indica(se possivel)
        void caminhar(const int x,const int y,int& dx, int& dy); //indica para onde o robo deve caminhar
        bool tentarCaminhar(const int x,const int y); //verifica se é possivel caminhar para o sentido indicado, retornando true se possivel
        bool ehParede(const int x,const int y){ return !tentarCaminhar(x,y); } //verifica se é o sentido indicado é parede retornando true se sim
        bool ehParedeEsq(const int x,const int y); //verifica se é parede na esquerda retornando true se sim
        bool ehParedeDir(const int x,const int y); //verifica se é parede na direita retornando true se sim
        char getEsq(); //Retorna o sentido da esquerda do que o robo se encontra
        char getDir(); //Retorna o sentido da direita do que o robo se encontra
    private:
        TEX* roboTex; // id de textura do robo
        char sentido; //sentido atual onde o robo se encontra
};

#endif
