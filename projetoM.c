/*
	Sobre o programa:
	
	Um simples protótipo de um jogo musical,
	no qual se ouve 2 sons e deve-se determinar o intervalo em semitons entre eles.
*/
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

int gerarN(char op);
int gerarO();
int modulo(int v);

int main()
{
	double const base[13] = {32.70, 34.65, 36.71, 38.89, 41.20, 43.65, 46.25, 49.00, 51.91, 55.00, 58.27, 61.74, 65.41};
	double f1, f2;
	char op, continuar, repetir;
	int n1, n2, oit, intervalo, resposta, acertos = 0, rodadas = 0;
	
	do
	{		
		system("cls");
		printf("Escolha o modo de jogo:");
		printf("\n 't' -> todas as notas");
		printf("\n 'n' -> apenas escala natural de dó maior\n");
		op = getch();
		system("cls");
	}
	while(op != 't' && op != 'n');
	
	srand(time(NULL));
	
	do
	{
		rodadas ++;
		n1 = gerarN(op);
		n2 = gerarN(op);
		intervalo = modulo(n1 - n2);
		
		oit = gerarO();
		f1 = base[n1]*pow(2, oit);	
		f2 = base[n2]*pow(2, oit);
		
		do
		{
			system("cls");
			
			Beep(f1, 1000);
			sleep(1);
			Beep(f2, 1000);
			
			printf("Pressione 'r' para repetir e qualquer outro valor para responder\n");
			repetir = getch();
		}
		while(repetir == 'r');
		
		system("cls");
		printf("\nQual o tamanho do intervalo (em semitons) entre as duas notas?");
		printf("\nResposta: ");
		
		scanf("%i", &resposta);
		
		system("cls");
		
		if(resposta == intervalo)
		{
			acertos ++;
			printf("Acertou!");
		}
		else
			printf("Errou! O tamanho era: %i", intervalo);
			
		printf("\n1 para continuar e outro valor para sair: ");
		continuar = getche();
	}
	while(continuar == '1');
	
	system("cls");
	
	printf("\nJogo finalizado!\n %i rodadas, %i acertos\nTaxa de acerto: %.2f%%", rodadas, acertos, 100.0 * acertos/rodadas);
	
	return 0;
}

int gerarN(char op)
{
	int r, i, achou = 0;
	int natural[8] = {0, 2, 4, 5, 7, 9, 11, 12};
	
	if(op == 't')
		r = rand() %12;
	else
	{
		do
		{
			r = rand() %12;
			for(i = 0; i < 8; i++)
			{
				if(r == natural[i])
				{
					achou ++;
					break;
				}
			}
		}
		while(achou == 0);
	}
	return r;
}

int gerarO()
{
	int o =  2 + rand() % 5;
	return o;
}

int modulo(int v)
{
	if(v < 0)
	{
		v = v * -1;
	}
	return v;
}


