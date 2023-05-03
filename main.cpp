#include "LabirintoTeste.h"
#include "RoboB9.h"
#include "C3PO.h"
#include "R2D2.h"
#include "Walle.h"
#include "GL.h"

using namespace std;

int main()
{
    GL::init();
    // Carga do labirinto
    Labirinto* lab = new LabirintoTeste();
    lab->loadMaze("labirintogrande.txt");

    Point posIni = lab->getIniPos();
    cout << "Pos ini: " << posIni.getX() << " , " << posIni.getY() << endl;

    Robo* robo;
    switch(lab->getRobot()){ //verifica o robo atual, e seta ele como o robo do programa
        case 0:{
            robo = new RoboB9(posIni, lab, 200); // 200 passos no maximo
            break;
        }
        case 1:{
            robo = new RoboC3PO(posIni,lab,200);
            break;
        }
        case 2:{
            robo = new RoboR2D2(posIni,lab,NULL);
            break;
        }
        case 3:{
            robo = new RoboWALLE(posIni,lab,NULL);
            break;
        }
    }

    GL::setLabirintoRobo(lab, robo);
    cout <<"ROBO:" << lab->getRobot();
	// Inicializa janela grafica e inicia programa
	GL::loop();

}
