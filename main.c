#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "include/centerWindow.c"

#define LARGURA 800
#define ALTURA 800
#define M_TAMANHO 30
#define LADO 20
#define BACKGROUND_COLOR \
	(Color) { 60, 3, 32, 100 } // Light Gray

// Funcao que move o objeto
void move(int dx, int dy, int *x, int *y)
{
	if (dx == 1)
		*x += 20;

	if (dx == -1)
		*x -= 20;

	if (dy == 1)
		*y += 20;

	if (dy == -1)
		*y -= 20;
}

// Funcao que verifica se o objeto deve mover
int deveMover(int x, int y, int dx, int dy)
{

	// Verifica eixo x
	if ((dx == 1 && x + 20 > 800 - LADO) || (dx == -1 && x - 20 < 0))
		return 0;

	if ((dy == 1 && y + 20 > 800 - LADO) || (dy == -1 && y - 20 < 0))
		return 0;

	return 1;
}

void deslocaInimigo(int *x, int *y)
{
	// srand(time(NULL)); // seed atrelada ao tempo do computador, deixa mais devagar

	// Logica para fazer objeto inimigo se movimentar
	// Gera um aleatorio entre 0 e 2
	int deslocaRandom = rand() % 3;

	int deslocaRandom2 = rand() % 3;

	// Mapeia o resultado desse número entre -1 e 1 quando subtrai 1
	int numeroRandom = deslocaRandom - 1;
	int numeroRandom2 = deslocaRandom2 - 1;
	printf("%d", numeroRandom);

	// Deslocamento do inimigo
	int desIniX = numeroRandom;
	int desIniY = numeroRandom2;

	// Parar o inimigo caso ele bata na parede
	if (!deveMover(*x, *y, desIniX, desIniY))
	{

		printf("\nFLAG LAFGAFA A SD");
		int it = 3000; // Iterador para parar quadrado inimigo
		printf("%d", it);

		do
		{
			move(0, 0, x, y);

			it--;

			printf("%d", it);

		} while (it > 0);

		if (desIniX == 1 || desIniX == -1)
		{
			do
			{
				desIniX = (rand() % 3) - 1;

			} while (desIniX == 1 && desIniX == -1);
		}

		if (desIniY == 1 || desIniY == -1)
		{
			do
			{
				desIniY = (rand() % 3) - 1;

			} while (desIniY == 1 && desIniY == -1);
		}

		move(desIniX, desIniY, x, y);
	}
	else
		move(desIniX, desIniY, x, y);
}

int main(void)
{

	// srand(time(NULL)); // seed atrelada ao tempo do computador
	int posRandom = (rand() % 40) * 20; // Posição aleatoria do quadrado multiplo de 20, 0 - 800

	// Eixos de locomoção do quadrado, iniciar em posicao randomica quadrado 1
	int posx = posRandom;
	int posy = posRandom;

	// testeseadwadawd

	// Eixos de locomoção do quadrado, iniciar em posicao 400, 400.
	int posx2 = 400;
	int posy2 = 400;

	// Inicializacoes rayLib
	InitWindow(LARGURA, ALTURA, "O Jogo"); // Inicializa janela, com certo tamanho e titulo
	centerWindow(LARGURA, ALTURA);
	SetTargetFPS(60); // Ajusta a execucao do jogo para 60 frames por segundo

	// Laco principal do jogo
	while (!WindowShouldClose()) // Detect window close button or ESC key
	{

		// Atualiza a representacao visual a partir do estado do jogo

		// Trata entrada do usuario e atualiza estado do jogo
		if (IsKeyPressed(KEY_RIGHT) || IsKeyDown(KEY_RIGHT)) // Verifica tecla pressionada e a tecla segurada
		{
			if (deveMover(posx, posy, 1, 0))
				move(1, 0, &posx, &posy);
		}

		if (IsKeyPressed(KEY_LEFT) || IsKeyDown(KEY_LEFT))
		{
			if (deveMover(posx, posy, -1, 0))
				move(-1, 0, &posx, &posy);
		}

		if (IsKeyPressed(KEY_UP) || IsKeyDown(KEY_UP))
		{
			if (deveMover(posx, posy, 0, -1))
				move(0, -1, &posx, &posy);
		}

		if (IsKeyPressed(KEY_DOWN) || IsKeyDown(KEY_DOWN))
		{
			if (deveMover(posx, posy, 0, 1))
				move(0, 1, &posx, &posy);
		}

		deslocaInimigo(&posx2, &posy2);

		BeginDrawing(); // Inicia o ambiente de desenho na tela

		ClearBackground(BACKGROUND_COLOR); // Limpa a tela e define cor de fundo

		DrawRectangle(posx, posy, LADO, LADO, GREEN); // Posição do quadrado 1

		DrawRectangle(posx2, posy2, LADO, LADO, RED); // Posição do quadrado 2

		EndDrawing(); // Finaliza o ambiente de desenho na tela
	}

	CloseWindow(); // Fecha a janela e o contexto OpenGL

	return 0;
}
