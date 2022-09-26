#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <locale.h>
int processNote(char note);
int main()
{
	setlocale(LC_ALL, "Portuguese");
	double const baseNotes[12] = {32.70, 34.65, 36.71, 38.89, 41.20, 43.65, 46.25, 49.00, 51.91, 55.00, 58.27, 61.74};
	int const baseRatio = 500;
	int n, i, pos, oct, count = -1, s, aux = 0;
	char note, type;
	double notasS[2][24] = {{9.0, 11.0, 0.0, 0.0, 2.0, 4.0, 4.0, 7.0, 2.0, 0.0, 11.0, 9.0, 9.0, 11.0, 0.0, 0.0, 2.0, 4.0, 4.0, 7.0, 9.0, 7.0, 11.0, 9.0},
				{3.0, 3.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 3.0, 3.0, 3.0, 3.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0}};
	double ratio;
	struct song
	{
		char title[30];
		double f[50];
		double d[50];
		int size;
	};
	struct song songs[10];
	
	char op;
	int e = 0;
	do
	{
		system("cls");
		printf("\nCriar música - 1\nConsultar músicas - 2\nTocar música - 3\nSair - qlqr outra coisa");
		printf("\n\nOpção: ");
		op = getche();
		printf("\n");
		switch(op)
		{
			case '1':
				count++;
				printf("\nCreate song");
				printf("\nNumber of notes: ");
				scanf("%i", &n);
				for(i = 0; i < n; i++)
				{
					system("cls");
					do
					{
						printf("\nWhich note is it? ");
						note = getche();
					}
					while(note < 97 || note > 103);
					pos = processNote(note);
					
					printf("\nOctave: ");
					scanf("%i", &oct);
					printf("'#' for sharp, 'b' for flat and anything else for natural\n");
					type = getche();
					switch(type)
					{
						case '#':
							if(pos == 11)
							{
								oct ++;
								pos = 0;
							}
							else
								pos ++;
							break;
						case 'b':
							if(pos == 0)
							{
								oct --;
								pos = 11;
							}
							else 
								pos --;
							break;
					}
					songs[count].f[i] = baseNotes[pos]*pow(2, oct);
					printf("\nInsert duration ratio: ");
					scanf("%lf", &ratio);
					songs[count].d[i] = ratio * baseRatio;
				}
				fflush(stdin);
				printf("Songs's title: ");
				gets(songs[count].title);
				songs[count].size = n;
				break;
			case '2':
				for(i = 0; i <= count; i++)
				{
					printf("\nTítulo: %s - Posição: %i\n", songs[i].title, i);
				}
				system("pause");
				break;
			case '3':
				printf("Posição da música: ");
				scanf("%i", &s);
				system("cls");
				Sleep(500);
				printf("1\n");
				Sleep(500);
				printf("2\n");
				Sleep(500);
				printf("3\n");
				Sleep(500);
				printf("\nPlaying %s", songs[s].title);
				for(i = 0; i < songs[s].size; i++)
				{
					Beep(songs[s].f[i], songs[s].d[i]);
				}
				break;
			case '4':
				if(aux < 1)
					for(i = 0; i < 24; i++)
					{
						notasS[0][i] = baseNotes[(int)notasS[0][i]]*pow(2, notasS[1][i]);
					}
				aux++;
				Beep(notasS[0][0], 500);
				Beep(notasS[0][1], 500);
				Beep(notasS[0][2], 1000);
				Beep(notasS[0][3], 500);
				Beep(notasS[0][4], 500);
				Beep(notasS[0][5], 1000);
				Beep(notasS[0][6], 500);
				Beep(notasS[0][7], 500);
				Beep(notasS[0][8], 1000);
				Beep(notasS[0][9], 500);
				Beep(notasS[0][10], 500);
				Beep(notasS[0][11], 1000);
				Beep(notasS[0][12], 500);
				Beep(notasS[0][13], 500);
				Beep(notasS[0][14], 1000);
				Beep(notasS[0][15], 500);
				Beep(notasS[0][16], 500);
				Beep(notasS[0][17], 1000);
				Beep(notasS[0][18], 500);
				Beep(notasS[0][19], 500);
				Beep(notasS[0][20], 1000);
				Beep(notasS[0][21], 500);
				Beep(notasS[0][22], 500);
				Beep(notasS[0][23], 1000);
				break;
			default:
				e ++;
				break;
		}
	}
	while(e<1);
	
	return 0;
	
}

int processNote(char note)
{
	int r;
	switch(note)
	{
		case 'c':
			r = 0;
			break;
		case 'd':
			r = 2;
			break;
		case 'e':
			r = 4;
			break;
		case 'f':
			r = 5;
			break;
		case 'g':
			r = 7;
			break;
		case 'a':
			r = 9;
			break;
		case 'b':
			r = 11;
			break;
	}
	return r;
}
