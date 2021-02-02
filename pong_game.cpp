#include <GL/glut.h>
#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include "GL/freeglut.h"

//Dimensao da Tela
int largura = 600;
int altura = 400;

//Sentido da Bola
GLint mball_x=0;
GLint mball_y=0;
//Direcao da Bola
GLint dire_x=1;
GLint dire_y=1;
//Movimenta as Barras
//Esquerda L
GLint mbar_yl=150;
//Direita R
GLint mbar_yr=150;
//Movimento Aleatorio
GLint rand_y = 0;
//Variavel de Pontuacao -> Max inf
int score_right = 0;
int score_left = 0;
//Variavel de Vida -> Inicial 5
int life_right = 5;
int life_left = 5;

//Inicia Cor e Perspectiva
void init(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glOrtho (0, largura, 0, altura, 0 ,1);
}

//Desenha Hud e MSG Final
void drawText(float x, float y, std::string text) {
    glRasterPos2f(x, y);
    glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}

//Cria Objetos em Tela
void display(void){
	//Limpa Comando em Tela
	glClear(GL_COLOR_BUFFER_BIT);
	//Cor da linha
	glColor3f(1.0, 1.0, 1.0);
	//Largura da Linha
	glLineWidth(10.0);
	glBegin(GL_LINE_LOOP);
	//Borda
	glVertex2i(2,2);		glVertex2i(599,2);
	glVertex2i(599,399);	glVertex2i(2,399);
	glEnd();
	
	//Desenha Linha Gerais 
	glBegin(GL_LINES);

	//Barra Left
	glVertex2i(50,mbar_yl);
	glVertex2i(50,mbar_yl+150);

	//Barra Right
	glVertex2i(550,mbar_yr);
	glVertex2i(550,mbar_yr+150);

	glEnd();

	glPointSize(15.0);
	glBegin(GL_POINTS);

	//Ball Position
	glVertex2i(mball_x+200,mball_y+200);
	glEnd();
	
	//Cria Hud
    std::string SL = std::to_string(score_left);
    std::string SR = std::to_string(score_right);
    std::string LL = std::to_string(life_left);
    std::string LR = std::to_string(life_right);
    drawText(largura / 2 - 189, altura - 20, "SCORE["+ SL +"]  ["+ LL +"]LIFE  L   |   R   LIFE["+ LR +"]  ["+ SR +"]SCORE");

	//MSG Final
	if(life_left == 0)  drawText((largura/2-30), (altura/2), "Lado Direito (RIGHT) VENCEU !");
	if(life_right == 0) drawText((largura/2-30), (altura/2), "Lado Esquerdo (LEFT) VENCEU !");
	
	//Atualiza Buffers
	glutSwapBuffers();
}

//Entrada de Setas(Right)
void keyboardArrow(int key, int x, int y){

	switch (key) {
		//Ativa de CIMA
		case GLUT_KEY_UP:
			//Soma Movimento na Barra Right Mantendo Limite
			if(mbar_yr < 250) mbar_yr += 10;
			break;
		case GLUT_KEY_DOWN:
			//Subtrai Movimento na Barra Right Mantendo Limite
			if(mbar_yr > 0) mbar_yr -= 10;
			break;
		//Termina Programa (Qualquer Tecla)
		default:
			exit(0);
			break;
	}
	//Recoloca Barra
	glutPostRedisplay();
}

//Entrada de Letras(Left)
void keyboardLetter(unsigned char key, int x, int y){

	switch (key) {
		//Ativa se W
		case 'w':
			//Soma Movimento na Barra Left Mantendo Limite
			if(mbar_yl < 250) mbar_yl += 10;
			break;
		//Ativa se S
		case 's':
			//Subtrai Movimento na Barra Left Mantendo Limite
			if(mbar_yl > 0) mbar_yl -= 10;
			break;
		//Termina Programa (Qualquer Tecla)
		default:
			exit(0);
			break;
	}
	//Recoloca Barra
	glutPostRedisplay();
}

void bola(int passo){
	//Move no X
	if(dire_x==1) {
		//Soma Movimento em X
		mball_x += 3;
		//Lado Right
		if(mball_x>=340){
			//Cria Velocidade Aleatoria
			int rand_y = rand() % 9;
			std::cout<<"\nY speed:"<<rand_y;
			passo = rand_y;
			//Troca Direcao
			dire_x = 0;
		}
	}
	else{
		//Subtrai Movimento em X
		mball_x -= 3;
		//Lado Left
		if(mball_x <= -140){
			//Cria Velocidade Aleatoria
			int rand_y = rand() % 9;
			std::cout<<"\nY speed:"<<rand_y<<"\n";
			passo = rand_y;
			//Troca Direcao
			dire_x = 1;
		}
	}

	//Move no Y (Altera Sentido)
	if(dire_y==1) {
		//Soma Movimento
		mball_y += passo;
		//Troca Direcao
		if(mball_y >= 185) dire_y=0;
	}
	else{
		//Subtrai Movimento
		mball_y -= passo;
		//Troca Direcao
		if(mball_y <= -185) dire_y=1;
	}

	glutPostRedisplay();
	//Funcao de Timer
	glutTimerFunc(10,bola, passo);
}

//Cria e Verifica Pontuacao
void score(int t01){
	//Retorna Score no Terminal
	//std::cout<<"\nScore R: "<<score_right<<" L: "<<score_left<<"     Life R: "<<life_right<<" L: "<<life_left;

	//Right Acerta
	if((mball_x >= 340) && ((mball_y+200) > (mbar_yr)) && ((mball_y+200) < (mbar_yr+150)) ){
		score_right += 1;
	}
	//Left Acerta
	if((mball_x <= -139)&& ((mball_y+200) > (mbar_yl)) && ((mball_y+200) < (mbar_yl+150)) ){
		score_left += 1;
	}
	//Right Erra
	if((mball_x >= 340) && !(((mball_y+200) > (mbar_yr)) && ((mball_y+200) < (mbar_yr+150))) ){
		if(life_right > 0) life_right -= 1;
	}
	//Left Erra
	if((mball_x <= -139)&& !(((mball_y+200) > (mbar_yl)) && ((mball_y+200) < (mbar_yl+150))) ){
		if(life_left > 0) life_left -= 1;
	}

	//Fim de Jogo (Vida Zero)
	if(life_left == 0 || life_right == 0){
		//Zera Valores do Jogo (Pausa)
		mball_x=0;
		mball_y=0;

		dire_x=1;
		dire_y=1;

		mbar_yl=150;
		mbar_yr=150;
	}
	glutPostRedisplay();
	glutTimerFunc(10,score,5);
}

int main(int argc, char** argv){
	//Caracteristicas da Janela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (largura, altura);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Pong Game");
	init();
	//Cria o Display dos Objetos
	glutDisplayFunc(display);
	//Bola
	glutTimerFunc(10,bola,1);
	//Move Setas Cima Baixo
	glutSpecialFunc(keyboardArrow);
	//Move Letra WS
	glutKeyboardFunc(keyboardLetter);
	//Score
	glutTimerFunc(9,score,2);
	//Loop Main
	glutMainLoop();
	return 0;
}


