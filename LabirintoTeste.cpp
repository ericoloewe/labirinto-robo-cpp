#include "LabirintoTeste.h"
#include <iostream>
#include <fstream>

LabirintoTeste :: LabirintoTeste() {
}

// Deveria carregar o labirinto de um arquivo,
// aqui so gera um espaco fechado, com uma saida na parte de baixo
void LabirintoTeste :: loadMaze(string arquivo) {
    ifstream arq;
    string temp,line;
    int prx,pry;
    cout << "Abrindo arquivo texto..." << endl;
	// Abre arquivo
    arq.open(arquivo.c_str() , ios::in );
    arq >> temp >> dimy >> dimx; // recebe a dimensão do labirinto
    arq >> temp >> prx >> pry; //recebe a posição inicial do robo
    arq >> temp >> robot;  //recebe o devido robo para o labirinto
    getline(arq,line); //tira a linha em branco do labirinto
    for(int i=0; i<dimy; i++) //loop feito para gerar o labirinto
    {
        getline(arq,line); //recebe a linha inteira do labirinto
        for(int j=0; j<dimx; j++) //loop feito para quebrar a linha em partes para setar o labirinto
            lab[i][j]=line[j];
    }
    posIni = Point(prx,pry); //seta a posição inicial do robo
    arq.close(); //fecha o arquivo
}

// Retorna true se a posição x,y do labirinto
// estiver livre (i.e. contenha um espaço em branco)
bool LabirintoTeste :: isEmpty(const Point& pos) const {
    if(pos.getX()<0 || pos.getX()>=dimx || pos.getY()<0 || pos.getY()>=dimy) return true;
    return (lab[pos.getY()][pos.getX()]==' ');
}

// Retorna dimensoes do labirinto
int LabirintoTeste :: getWidth() { return dimx; }
int LabirintoTeste :: getHeight() { return dimy; }

int LabirintoTeste::getRobot() { return robot; }

Point LabirintoTeste::getIniPos() { return posIni; }
