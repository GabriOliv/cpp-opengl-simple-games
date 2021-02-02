#include <GL/glut.h>
#include <iostream>
#include "GL/freeglut.h"


//Dimensao da Tela
	int dimension = 600;
	//Largura de Tela
	int largura = dimension*3/2;
	//Altura de Tela
	int altura = dimension;

//Variaveis do Jogo
	//Seleciona o Carro
	int selection = 0;
	//Movimentos Totais em Jogo
	int movmnts = 0;

//Declaracao dos Componentes do Jogo
	//Carros em Jogo
	//Colors Scheme
	/*	Gray	-1	(0.3,0.3,0.3)
		Red		0	(1.0,0.0,0.0)
		Blue	1	(0.0,0.0,1.0)
		Green	2	(0.0,0.8,0.0)
		Orange	3	(1.0,0.5,0.0)
		Purple	4	(0.7,0.0,1.0)
		Yellow	5	(1.0,1.0,0.0)
	*///[cor-R][X-8][Y-9][Z-0][MOV-0H]
	int C[6][5] = 
	{
		{0, 0,13,14,0},
		{1,20,26,32,1},
		{2,34,35, 0,0},
		{3, 5,11,17,1},
		{4,27,33, 0,1},
		{5,22,23, 0,0}
	};

	//Constantes de Coordenadas
	const int c_x = 6;
	const int c_y = 6;
	const int c_z = 2;
	//Tabuleiro
	//[coord x] [coord y] [coord y: 0->Num | 1->Slot | 2 -> Aux]
	int A[c_x][c_y][c_z] = 
	{
		{
			{ 1,-1},{ 2,-1},{ 3,-1},{ 4,-1},{ 5,-1},{ 6,-1},
		},{
			{ 7,-1},{ 8,-1},{ 9,-1},{10,-1},{11,-1},{12,-1},
		},{
			{13,-1},{14,-1},{15,-1},{16,-1},{17,-1},{18,-1},
		},{
			{19,-1},{20,-1},{21,-1},{22,-1},{23,-1},{24,-1},
		},{
			{25,-1},{26,-1},{27,-1},{28,-1},{29,-1},{30,-1},
		},{
			{31,-1},{32,-1},{33,-1},{34,-1},{35,-1},{36,-1},
		}
	};

//Display
	//Inicia Cor e Perspectiva(Display)
	void init(void);
	//Desenha Hud(Display)
	void drawText(float x, float y, std::string text, int tam);
	//Plot de Poligono(Display)
	void Polygon_default(int centro_x, int centro_y, int sizep, int type, int colorC);
	//Display do Jogo(Display)
	void display(void);

//Manipulacao do Jogo
	//Atualiza Tabuleiro(A)
	void RefreshTab();
	//Movimenta Carro na Matriz Carro(C) e Salva na MAtriz Tabuleiro(A) 
	void MovCar(int movsentido);

//Comandos do Teclado
	//Setas de Controle do Jogo
	void keyboardArrow(int key, int x, int y);
	//Tecla ESC para Sair
	void keyboardLetter(unsigned char key, int x, int y);

//Main Entry Point do Jogo
int main(int argc, char** argv){
	//Caracteristicas da Janela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (largura, altura);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Puzzle Rush Hour");
	init();

	//Cria o Display dos Objetos
	glutDisplayFunc(display);
	//Entrada de Teclado
	glutSpecialFunc(keyboardArrow);
	glutKeyboardFunc(keyboardLetter);
		
	//Loop Main
	glutMainLoop();
	return 0;
}

//Inicia Cor e Perspectiva
void init(void){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho (0, largura, 0, altura, 0 ,1);
}

//Desenha Hud
void drawText(float x, float y, std::string text, int tam) {
	//Escreve em TIMES ROMAN tam 24
	if(tam == 1){
		glRasterPos2f(x, y);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)text.c_str());
	}
	//Escreve em TIMES ROMAN tam 10
	if(tam == 0){
		glRasterPos2f(x, y);
		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_10, (const unsigned char*)text.c_str());
	}
	//Escreve em TIMES ROMAN tam 24 Diagonal
	if(tam == 10){
		int size = text.size();
		for(int i=0; i<size; i++){
			glRasterPos2f(x, y);
			char aux=text[i];
			glutBitmapCharacter ( GLUT_BITMAP_TIMES_ROMAN_24 , aux);
			y=y-10;
			x=x+8;
		}
	}
}

//Plot de Poligono
void Polygon_default(int centro_x, int centro_y, int sizep, int type, int colorC){
	float colorR = 1;
	float colorG = 1;
	float colorB = 1;

	//Grey
	if(colorC == -1){	colorR = 0.4; colorG = 0.4; colorB = 0.4;}
	//Red
	else if(colorC ==  0){	colorR = 1.0; colorG = 0.0; colorB = 0.0;}
	//Blue
	else if(colorC ==  1){	colorR = 0.0; colorG = 0.0; colorB = 1.0;}
	//Green
	else if(colorC ==  2){	colorR = 0.0; colorG = 0.8; colorB = 0.0;}
	//Orange
	else if(colorC ==  3){	colorR = 1.0; colorG = 0.5; colorB = 0.0;}
	//Purple
	else if(colorC ==  4){	colorR = 0.7; colorG = 0.0; colorB = 1.0;}
	//Yellow
	else if(colorC ==  5){	colorR = 1.0; colorG = 1.0; colorB = 0.0;}
	
	//Polygono do Tabuleiro
	if(type == 0){
		//Quadrado Grande
		glBegin(GL_POLYGON);
			glColor3f( colorR*0.4, colorG*0.4, colorB*0.4 );
			glVertex2i( centro_x-sizep/2,centro_y-sizep/2);
			glVertex2i( centro_x-sizep/2,centro_y+sizep/2);
			glVertex2i( centro_x+sizep/2,centro_y+sizep/2);
			glVertex2i( centro_x+sizep/2,centro_y-sizep/2);
		glEnd();
		//Luz
		glBegin(GL_POLYGON);
			glColor3f( colorR*0.7, colorG*0.7, colorB*0.7 );
			glVertex2i( centro_x-sizep/2,centro_y-sizep/2);
			glVertex2i( centro_x-sizep/2,centro_y+sizep/2);
			glVertex2i( centro_x+sizep/2,centro_y+sizep/2);
		glEnd();
		//Arestas Internas
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
			glColor3f( colorR*0.3, colorG*0.3, colorB*0.3 );
			glVertex2i( centro_x-sizep/2,centro_y-sizep/2);
			glVertex2i( centro_x-sizep/2,centro_y+sizep/2);
			glVertex2i( centro_x+sizep/2,centro_y-sizep/2);
			glVertex2i( centro_x+sizep/2,centro_y+sizep/2);
		glEnd();
		//Quadrado Menor
		glBegin(GL_POLYGON);
			glColor3f(colorR, colorG, colorB);
			glVertex2i( centro_x-sizep/4,centro_y-sizep/4);
			glVertex2i( centro_x-sizep/4,centro_y+sizep/4);
			glVertex2i( centro_x+sizep/4,centro_y+sizep/4);
			glVertex2i( centro_x+sizep/4,centro_y-sizep/4);
		glEnd();
		//Aresta do Quadrado Maior
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
			glColor3f( colorR*0.2, colorG*0.2, colorB*0.2 );
			glVertex2i( centro_x-sizep/2,centro_y-sizep/2);
			glVertex2i( centro_x-sizep/2,centro_y+sizep/2);
			glVertex2i( centro_x+sizep/2,centro_y+sizep/2);
			glVertex2i( centro_x+sizep/2,centro_y-sizep/2);
		glEnd();
		//Aresta do Quadrado Menor
		glBegin(GL_LINE_LOOP);
			glColor3f( colorR*0.2, colorG*0.2, colorB*0.2 );
			glVertex2i( centro_x-sizep/4,centro_y-sizep/4);
			glVertex2i( centro_x-sizep/4,centro_y+sizep/4);
			glVertex2i( centro_x+sizep/4,centro_y+sizep/4);
			glVertex2i( centro_x+sizep/4,centro_y-sizep/4);
		glEnd();
	}
	//Polygono da Saida
	if(type == 1){
		//Luz
		glBegin(GL_POLYGON);
			glColor3f( colorR*0.7, colorG*0.7, colorB*0.7 );
			glVertex2i( centro_x-sizep/2,centro_y-sizep/2);
			glVertex2i( centro_x-sizep/2,centro_y+sizep/2);
			glVertex2i( centro_x+sizep/5,centro_y+sizep/2);
			glVertex2i( centro_x+sizep/5,centro_y-sizep/2);
		glEnd();
		//Quadrado Grande
		glBegin(GL_POLYGON);
			glColor3f( colorR*0.4, colorG*0.4, colorB*0.4 );
			glVertex2i( centro_x-sizep/2,centro_y-sizep/2);
			glVertex2i( centro_x+sizep/5,centro_y+sizep/2);
			glVertex2i( centro_x+sizep/5,centro_y-sizep/2);
		glEnd();
		//Quadrado Menor
		glBegin(GL_POLYGON);
			glColor3f(colorR, colorG, colorB);
			glVertex2i( centro_x-8*sizep/20,centro_y-8*sizep/20);
			glVertex2i( centro_x-8*sizep/20,centro_y+8*sizep/20);
			glVertex2i( centro_x+2*sizep/20,centro_y+8*sizep/20);
			glVertex2i( centro_x+2*sizep/20,centro_y-8*sizep/20);
		glEnd();
		//Arestas do Quadrado Maior
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
			glColor3f( colorR*0.2, colorG*0.2, colorB*0.2 );
			glVertex2i( centro_x-sizep/2,centro_y-sizep/2);
			glVertex2i( centro_x-sizep/2,centro_y+sizep/2);
			glVertex2i( centro_x+sizep/5,centro_y+sizep/2);
			glVertex2i( centro_x+sizep/5,centro_y-sizep/2);
		glEnd();
		//Aresta do Quadrado Menor
		glBegin(GL_LINE_LOOP);
			glVertex2i( centro_x-8*sizep/20,centro_y-8*sizep/20);
			glVertex2i( centro_x-8*sizep/20,centro_y+8*sizep/20);
			glVertex2i( centro_x+2*sizep/20,centro_y+8*sizep/20);
			glVertex2i( centro_x+2*sizep/20,centro_y-8*sizep/20);
		glEnd();
	}
	
}

//Atualiza Tabuleiro
void RefreshTab(){
	//Limpa Layout Antigo
	for(int i=0; i<c_x; i++){
		for(int j=0; j<c_y; j++){
			//Espaco sem Carro
			A[i][j][1] = -1;
		}
	}

	//Seta New Positions
	//Conta Carro
	for(int i=0; i<6; i++){
		//Count x
		for(int j=0; j<c_x; j++){
			//Count y
			for(int k=0; k<c_y; k++){
				//[cor-R][X-8][Y-9][Z-0][MOV-0H]
				     if(A[j][k][0] == C[i][1])	A[j][k][1] =  i;
				else if(A[j][k][0] == C[i][2])	A[j][k][1] =  i;
				else if(A[j][k][0] == C[i][3])	A[j][k][1] =  i;
			}
		}
	}

}

//Display do Jogo
void display(void){
	//Limpa Comando em Tela
	glClear(GL_COLOR_BUFFER_BIT);
	//Cor da linha
	glColor3f(0.0, 0.0, 1.0);

	//Bordas
	int ax=largura/20-largura/30; int ay=altura/20-altura/30;
	int bx=largura/20-largura/30; int by=altura-altura/30;
	int cx=largura-largura/40; int cy=altura-altura/30;
	int dx=largura-largura/40; int dy=altura/20-altura/30;

	int sizep = 80;
	int centro_x = 2*largura/3 	+sizep/4;
	int centro_y = altura/2 	-sizep/2;

	int ex=centro_x-3*sizep;	int ey=centro_y+3*sizep;

	//Borda Janela
	glColor3f(0.5,0.5,0.5);
	glLineWidth(5.0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(ax, ay);
		glVertex2i(bx, by);
		glVertex2i(cx, cy);
		glVertex2i(dx, dy);
	glEnd();

	//Borda Menu
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(ax+largura/30, by-altura/20);
		glVertex2i(ax+largura/30, ay+altura/20);
		glVertex2i(ax+largura/03, ay+altura/20);
		glVertex2i(ax+largura/03, by-altura/20);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2i(ax+largura/30, by-altura/8);
		glVertex2i(ax+largura/03, by-altura/8);
	glEnd();

	//Text MENU
	glColor3f(0.3,0.3,0.8);
	drawText(ax+largura/25, by-altura/10,"Menu", 1);

	glColor3f(0,0,0);
	//Text Movimentos Totais em Jogo
    std::string MOVI = std::to_string(movmnts);
	drawText(ax+largura/6, by-altura/10,"Moves: "+MOVI, 1);
	//Text ESC
	drawText(20,16,"Aperte Esc para SAIR", 0);

	//Menu Carros Coordenadas
	int fx=ax+largura/30; int fy=by-altura/20;
	int gx=ax+largura/30; int gy=by-altura/6;
	int hx=ax+largura/03; int hy=by-altura/6;
	int ix=ax+largura/03; int iy=by-altura/20;

	//Menu Listagem de Carros
	for(float i=0; i<6 ; i++){
		int aux = 70;
		int bord = 18;

		//Base
		glBegin(GL_POLYGON);
		glColor3f(0.2,0.2,0.2);
			glVertex2i(fx,fy-(i+1)*aux);
			glVertex2i(gx,gy-(i+1)*aux);
			glVertex2i(hx,hy-(i+1)*aux);
			glVertex2i(ix,iy-(i+1)*aux);
		glEnd();
		//Luz
		glBegin(GL_POLYGON);
		glColor3f(0.4,0.4,0.4);
			glVertex2i(fx,fy-(i+1)*aux);
			glVertex2i(gx,gy-(i+1)*aux);
			glVertex2i(gx+12*bord/18,gy-(i+1)*aux+bord);
			glVertex2i(ix-12*bord/18,iy-(i+1)*aux-bord);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex2i(ix,iy-(i+1)*aux);
			glVertex2i(fx,fy-(i+1)*aux);
			glVertex2i(fx+12*bord/18,fy-(i+1)*aux-bord);
			glVertex2i(ix-12*bord/18,iy-(i+1)*aux-bord);
		glEnd();
		//Linha Interna
		glLineWidth(2.0);
		glColor3f(0,0,0);
		glBegin(GL_LINE_LOOP);
			glVertex2i(fx,fy-(i+1)*aux);
			glVertex2i(fx+12*bord/18,fy-(i+1)*aux-bord);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex2i(gx,gy-(i+1)*aux);
			glVertex2i(gx+12*bord/18,gy-(i+1)*aux+bord);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex2i(hx,hy-(i+1)*aux);
			glVertex2i(hx-12*bord/18,hy-(i+1)*aux+bord);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex2i(ix,iy-(i+1)*aux);
			glVertex2i(ix-12*bord/18,iy-(i+1)*aux-bord);
		glEnd();
		//Base Menor
		glBegin(GL_POLYGON);
		glColor3f(0.3,0.3,0.3);
			glVertex2i(fx+12*bord/18,fy-(i+1)*aux-bord);
			glVertex2i(gx+12*bord/18,gy-(i+1)*aux+bord);
			glVertex2i(hx-12*bord/18,hy-(i+1)*aux+bord);
			glVertex2i(ix-12*bord/18,iy-(i+1)*aux-bord);
		glEnd();
		//Linha Perimetro Externa
		glLineWidth(5.0);
		glBegin(GL_LINE_LOOP);
		glColor3f(0,0,0);
			glVertex2i(fx,fy-(i+1)*aux);
			glVertex2i(gx,gy-(i+1)*aux);
			glVertex2i(hx,hy-(i+1)*aux);
			glVertex2i(ix,iy-(i+1)*aux);
		glEnd();
		//Linha Perimetro Interna
		glLineWidth(2.0);
		glBegin(GL_LINE_LOOP);
		glColor3f(0,0,0);
			glVertex2i(fx+12*bord/18,fy-(i+1)*aux-bord);
			glVertex2i(gx+12*bord/18,gy-(i+1)*aux+bord);
			glVertex2i(hx-12*bord/18,hy-(i+1)*aux+bord);
			glVertex2i(ix-12*bord/18,iy-(i+1)*aux-bord);
		glEnd();
		//Seta Cor do Letreiro Carro 
		std::string COLORtxt = "";
		if(i == 0){	glColor3f(1.0,0.0,0.0);	COLORtxt = "Red";}
		if(i == 1){	glColor3f(0.0,0.5,0.9);	COLORtxt = "Blue";}
		if(i == 2){	glColor3f(0.0,0.8,0.0);	COLORtxt = "Green";}
		if(i == 3){	glColor3f(1.0,0.5,0.0);	COLORtxt = "Orange";}
		if(i == 4){	glColor3f(0.7,0.0,1.0);	COLORtxt = "Purple";}
		if(i == 5){	glColor3f(1.0,1.0,0.0);	COLORtxt = "Yellow";}
		//Text Bloco do Menu
		drawText(fx+1*aux/4, fy-(i)*aux-115, "Bloco "+COLORtxt, 1);
		drawText(fx+47*aux/40, fy-(i)*aux-115, "             < move >", 1);
	}

	//Text Colors Carros
	glBegin(GL_LINE_LOOP);
	glColor3f(0.7,0.5,0.9);
		glVertex2i(fx,fy-(selection+1)*70);
		glVertex2i(gx,gy-(selection+1)*70);
		glVertex2i(hx,hy-(selection+1)*70);
		glVertex2i(ix,iy-(selection+1)*70);
	glEnd();

	//Polygono SAIDA
	Polygon_default(ex+6*sizep, ey-2*sizep, sizep, 1, -1);
	//Polygono Tabuleiro 
	for(int i=0; i<6 ; i++){
		for(int j=0; j<6 ; j++){
			Polygon_default(ex+i*sizep, ey-j*sizep, sizep, 0, -1);
		}
	}

	//Text Saida
	glColor3f(0.8,0.8,0.8);
	drawText(ex+6*sizep-8*sizep/20, ey-2*sizep+3*sizep/20, "Saida", 10);
	
	//Refresh Tabuleiro
	RefreshTab();
	//Plota Carros
	for(int i=0; i<c_x; i++){
		for(int j=0; j<c_y; j++){
			int aux = A[j][i][1];
			Polygon_default(ex+i*sizep, ey-j*sizep, sizep, 0, aux);
		}
	}

	//Detecta se Venceu
	if(C[0][3] == 18){
		//Salva os Movimentos em String
		const std::string MOVIFINAL = std::to_string(movmnts);
		//Trava Selecao de Carros
		selection = -9;
		//Placa de Vencedor
		//Quadrado Grande
		int size2 = sizep/2;
		glBegin(GL_POLYGON);
		glColor3f(0.1,0.1,0.1);
			glVertex2i(ex-size2,	ey+size2);
			glVertex2i(ex-size2,	ey-11*size2);
			glVertex2i(ex+11*size2,	ey-11*size2);
			glVertex2i(ex+11*size2,	ey+size2);
		glEnd();

		//Linha Perimetro Externa
		glLineWidth(10.0);
		glBegin(GL_LINE_LOOP);
		glColor3f(1,1,0);
			glVertex2i(ex+2*size2,	ey-3*size2);
			glVertex2i(ex+2*size2,	ey-7*size2);
			glVertex2i(ex+8*size2,	ey-7*size2);
			glVertex2i(ex+8*size2,	ey-3*size2);
		glEnd();
		//Text de Venceu
		drawText(ex+3*size2,	ey-4*size2,"VC VENCEU", 1);
		drawText(ex+3*size2,	ey-5*size2,"YOU WIN", 1);
		drawText(ex+4*size2,	ey-6*size2,"Moves: "+MOVIFINAL, 1);
	}

	//Atualiza Buffers
	glutSwapBuffers();

}

void MovCar(int movsentido){
//[cor-R][X-8][Y-9][Z-0][MOV-0H]
//Tabuleiro		[coord y] [coord x] [coord y: 0->Num | 1->Slot | 2 -> Aux]

	//Aux de Posicoes
	int movcar = selection;
	int x = C[selection][1];
	int y = C[selection][2];
	int z = C[selection][3];
	int mov = C[selection][4];
	int ERRO = 0;
	
	//Cria Vetor de Coordenadas
	int Il[3];	int Jc[3];
	for(int i=0; i<3; i++){
		Il[i]=0;
		Jc[i]=0;
	}
	
	//Tabuleiro		[coord y] [coord x] [coord y: 0->Num | 1->Slot | 2 -> Aux]
	//Seta Coordenadas Atuais do Carro
	for(int i=0,k=0; i<6; i++){
		for(int j=0; j<6; j++){
			if(A[i][j][0] == x){
				Il[k] = i;
				Jc[k] = j;
				k++;
			}
			if(A[i][j][0] == y){
				Il[k] = i;
				Jc[k] = j;
				k++;
			}
			if(A[i][j][0] == z){
				Il[k] = i;
				Jc[k] = j;
				k++;
			}
		}
	}
	
	//Tabuleiro		[coord y] [coord x] [coord y: 0->Num | 1->Slot | 2 -> Aux]

	//Horizontal
	if(mov == 0){
		//Direita
		if(movsentido == 1){
			std::cout<<"\nbarrier j: ";
			for(int j=6; j<37; j=j+6){
				if(x == j)	ERRO = 1;
				if(y == j)	ERRO = 2;
				if(z == j)	ERRO = 3;
				std::cout<<" - "<<j;
			}
			std::cout<<"\n";

			if(x!=0)	x++;
			if(y!=0)	y++;
			if(z!=0)	z++;
		
			if(ERRO == 0){
				for(int j=0; j<3; j++){
					if(!(Il[j] == 0 && Jc[j] == 0)){
						int aux1 = Il[j];
						int aux2 = Jc[j]+1;
						if(!((A[aux1][aux2][1]) == movcar || (A[aux1][aux2][1]) == -1))	ERRO = 4;
					}
				}
			}

		}

		//Esquerda
		if(movsentido == -1){
			std::cout<<"\nbarrier j: ";
			for(int j=1; j<38; j=j+6){
				if(x == j)	ERRO = 5;
				if(y == j)	ERRO = 6;
				if(z == j)	ERRO = 7;
				std::cout<<" - "<<j;
			}
			std::cout<<"\n";

			if(x!=0)	x--;
			if(y!=0)	y--;
			if(z!=0)	z--;
			
			if(ERRO == 0){
				for(int j=0; j<3; j++){
					if(!(Il[j] == 0 && Jc[j] == 0)){
						int aux1 = Il[j];
						int aux2 = Jc[j]-1;
						if(!((A[aux1][aux2][1]) == movcar || (A[aux1][aux2][1]) == -1))	ERRO = 8;
					}
				}
			}

		}
	}

	//Vertical
	if(mov == 1){
		//Cima
		if(movsentido == 1){
			std::cout<<"\nbarrier j: ";
			for(int j=1; j<7; j++){
				if(x == j)	ERRO = 9;
				if(y == j)	ERRO = 10;
				if(z == j)	ERRO = 11;
				std::cout<<" - "<<j;
			}
			std::cout<<"\n";

			if(x!=0)	x=x-6;
			if(y!=0)	y=y-6;
			if(z!=0)	z=z-6;

			if(ERRO == 0){
				for(int j=0; j<3; j++){
					if(!(Il[j] == 0 && Jc[j] == 0)){
						int aux1 = Il[j]-1;
						int aux2 = Jc[j];
						if(!((A[aux1][aux2][1]) == movcar || (A[aux1][aux2][1]) == -1))	ERRO = 12;
					}
				}
			}

		}
		//Baixo
		if(movsentido == -1){
			std::cout<<"\nbarrier j: ";
			for(int j=31; j<37; j++){
				if(x == j)	ERRO = 13;
				if(y == j)	ERRO = 14;
				if(z == j)	ERRO = 15;
				std::cout<<" - "<<j;
			}
			std::cout<<"\n";

			if(x!=0)	x=x+6;
			if(y!=0)	y=y+6;
			if(z!=0)	z=z+6;
			
			if(ERRO == 0){
				for(int j=0; j<3; j++){
					if(!(Il[j] == 0 && Jc[j] == 0)){
						int aux1 = Il[j]+1;
						int aux2 = Jc[j];
						if(!((A[aux1][aux2][1]) == movcar || (A[aux1][aux2][1]) == -1))	ERRO = 16;
					}
				}
			}

		}
	}

	//Retorna Nova Coordenada #Terminal
	if(ERRO == 0){
		C[selection][1] = x;
		C[selection][2] = y;
		C[selection][3] = z;
		movmnts++;
		std::cout<<"\n[ V ]Movimento Realizado[ V ]\n\n";
	}
	//Retorna ERRO #Terminal
	else{
		std::cout<<"\n[ ! ]Select"<<selection<<" -> Movimento Invalido ->"<<ERRO<<"[ ! ]\n\n";
	}

}

//Entrada de Setas
void keyboardArrow(int key, int x, int y){

	switch (key) {

		//Seleciona Carro
		case GLUT_KEY_UP:
			if(selection > -2) selection = (selection+5)%6;
			break;
		//Seleciona Carro
		case GLUT_KEY_DOWN:
			if(selection > -2) selection = (selection+1)%6;
			break;


		//Move Carro
		case GLUT_KEY_RIGHT:
			if(selection > -2) MovCar(+1);
			break;
		//Move Carro
		case GLUT_KEY_LEFT:
			if(selection > -2) MovCar(-1);
			break;

		default:
			break;
	}
	//Recoloca Display
	glutPostRedisplay();
}

void keyboardLetter(unsigned char key, int x, int y){

	switch (key) {
		//Esc Sair do Jogo
		case 27:
			exit(0);
			break;
		default:
			break;
	}
	//Recoloca Display
	glutPostRedisplay();
}
