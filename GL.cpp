#include "GL.h"
#include <sstream>

// Existe outra maneira de resolver isto ?
int GL::width,GL::height;
vector<Point> GL::steps;
int GL::current;
float GL::deltax, GL::deltay;
int GL::dimx, GL::dimy;
Labirinto* GL::lab;
Robo* GL::rob;
TEX* GL::paredeTex;

// Desenha um retangulo
void GL::drawRect(float x1, float y1, float x2, float y2) {
    glBegin(GL_QUADS);
      glTexCoord2f(0,1);
	  glVertex2f(x1,y1);
      glTexCoord2f(1,1);
      glVertex2f(x2,y1);
      glTexCoord2f(1,0);
      glVertex2f(x2,y2);
      glTexCoord2f(0,0);
      glVertex2f(x1,y2);
	glEnd();
}

// Desenha um triangulo
void GL::drawTri(float x1, float y1, float x2, float y2, float x3, float y3) {
	glBegin(GL_TRIANGLES);
	  glVertex2f(x1,y1);
	  glVertex2f(x2,y2);
	  glVertex2f(x3,y3);
	glEnd();
}

// Desenha um circulo
void GL::drawCirc(float x1, float y1, float r) {

	float ang;
	ang = 0;

	// Usamos triangle fan para ser mais eficiente
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1,y1);

	GLint circle_points = 20;
	for (int i = 0; i < circle_points; i++) {
		float angle = 2*3.1415926*i/circle_points;
		glVertex2f(x1+cos(angle)*r, y1+sin(angle)*r);
	}
	glVertex2f(x1+cos(0)*r, y1+sin(0)*r);
	glEnd();
}

// Desenha uma linha
void GL::drawLine(float x1, float y1, float x2, float y2) {
	glBegin(GL_LINES);
	  glVertex2f(x1,y1);
	  glVertex2f(x2,y2);
	glEnd();
}

// Limpa a tela e prepara para desenhar
void GL::clear() {
	// Limpa a janela de visualiza�o com a cor branca
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Carrega a matriz identidade
	glLoadIdentity();
}

// Funcao responsavel por inicializar parametros e variaveis
void GL::init()
{
	int argc = 0;
	char *argv[] = { "gl", 0 };

	glutInit(&argc,argv);

	// Define do modo de operacao da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(400,400);

	// Cria a janela passando como argumento o titulo da mesma
    glutCreateWindow("Trabalho 2");

	// Registra a funcao callback de redesenho da janela de visualizacao
	glutDisplayFunc(draw);

	// Registra a funcao callback para tratamento das teclas ASCII
    glutKeyboardFunc (keyboard);

    // Registra a funcao callback para tratamento das teclas especiais
    glutSpecialFunc (keyboardSpecial);

	// Define a janela de visualizacao 2D
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,1.0,1.0,0.0);
    glMatrixMode(GL_MODELVIEW);

    // Carrega a textura de parede para o labirinto
    paredeTex = CarregaTextura("brick.jpg", true);
}

void GL::setLabirintoRobo(Labirinto* l, Robo* robo)
{
    lab = l;
    rob = robo;

    dimx = lab->getWidth();
    dimy = lab->getHeight();
	deltax = 1.0/dimx;
    deltay = 1.0/dimy;

    rob->generateSteps();
    steps = rob->getSteps();
    cout << "Steps: " << steps.size() << endl;

    for(int i=0; i<steps.size(); i++)
        cout << steps[i].getX() << "," << steps[i].getY() << endl;
    current = 0;
    rob->move(steps[current]);
}

// Entra no loop de eventos
void GL::loop() {
	glutMainLoop();
}

// Funcao chamada quando a tela e' redesenhada
void GL::draw(void)
{
	clear();

	// Para outras cores, veja exemplos em /etc/X11/rgb.txt

	setColor(200,200,200);	// cinza claro

	float x,y;
	// Desenha a grade
	for(x=0; x<=1; x+=deltax)
		drawLine(x,0,x,1);
	for(y=0; y<=1; y+=deltay)
		drawLine(0,y,1,y);

	// Desenha o labirinto
    glColor3f(1,1,1);
    y = 0.0;
    enableTexture(paredeTex->texid);
	for(int l=0; l<dimy; l++, y+=deltay) {
		x = 0.0;
		for(int c=0; c<dimx; c++, x+=deltax) {
            if(!lab->isEmpty(Point(c,l)))
				drawRect(x,y,x+deltax,y+deltay);
		}
    }
    disableTexture();

    // Escreve o passo atual na tela
    ostringstream aux;
    aux << "Passo: " << current+1 << " de " << steps.size();
    glColor3f(0,0,0);
    drawText(0.0615,0.0315, aux.str());
    glColor3f(1,1,0);
    drawText(0.06,0.03, aux.str());

    // Finalmente, desenha o robô na posição atual
    rob->draw();

	// Exibe o desenho
	show();
}

// Funcao chamada quando uma tecla e' pressionada
void GL::keyboard(unsigned char key, int x, int y)
{
    if (key == 27)		// ESC ?
    {
        LiberaTexturas();
        exit(0);
    }

	// Redesenha a tela
	glutPostRedisplay();
}

// Escreve uma string na tela, usando uma projecao ortografica
// normalizada (0..1, 0..1)
void GL::drawText(float x, float y, string txt)
{
    // Posiciona no canto inferior esquerdo da janela
    glRasterPos2f(x,y);
    // "Escreve" a mensagem
    int cont=0;
    while(cont < txt.size())
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, txt[cont++]);
}

void GL::enableTexture(GLuint texid)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texid);
}

void GL::disableTexture()
{
    glDisable(GL_TEXTURE_2D);
}

void GL::keyboardSpecial(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT &&  current > 0)
            current--;
    else if(key == GLUT_KEY_RIGHT  && current < steps.size()-1)
            current++;

    rob->move(steps[current]);

    // Redesenha a tela
    glutPostRedisplay();
}
