#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <locale.h>

#define MAX 50

int processNote(char note);
void gravar_arquivo(i_song musica[]);
int ler_arquivo(i_song musica[MAX]);

//declação da struct song
struct song
{
	char title[30];
	double f[50]; //frequencias
	double d[50]; //duração de uma nota
	int size;
}i_song;

int main()
{
	setlocale(LC_ALL, "Portuguese");

	double const baseNotes[12] = {32.70, 34.65, 36.71, 38.89, 41.20, 43.65, 46.25, 49.00, 51.91, 55.00, 58.27, 61.74};//frequencias basicas a partir da primeira oitava de um teclado

	int const baseRatio = 500;//duração base em milisegundos

	int n, i, pos, oct, count = -1, s, aux = 0;

	char note, type;

	//declaração do vetor de musicas salvas;
	i_song musicas[MAX];
	//chamada da função de leitura/ guardando o numero de musicas salvas
	int len_vet = ler_arquivo(musicas);

	i_song songs[2];

	/*
	Música teste:
	double notasS[2][24] = {{9.0, 11.0, 0.0, 0.0, 2.0, 4.0, 4.0, 7.0, 2.0, 0.0, 11.0, 9.0, 9.0, 11.0, 0.0, 0.0, 2.0, 4.0, 4.0, 7.0, 9.0, 7.0, 11.0, 9.0},
				{3.0, 3.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 3.0, 3.0, 3.0, 3.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0, 4.0}};
	*/
	
	double ratio; //duração de uma nota

	char op;
	int e = 0;
	do
	{
		system("cls");
		printf("\nCriar m�sica - 1\nConsultar m�sicas - 2\nTocar m�sica - 3\nSair - qlqr outra coisa");
		printf("\n\nOp��o: ");
		op = getche();
		printf("\n");
		switch(op)
		{
			case '1': //criar música
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
						note = getche();//recebe um caracter que corresponde a uma nota
					}
					while(note < 97 || note > 103); //verifica se a coisa digitada esta entre o intervalo de notas validas
					pos = processNote(note);
					
					printf("\nOctave: ");
					scanf("%i", &oct);//guarda a oitava na qual a nota esta
					printf("'#' for sharp, 'b' for flat and anything else for natural\n");
					type = getche();

					switch(type)
					{
						case '#':
							if(pos == 11)//11 é a ultima "casa", então ele não pode subir uma posição
							{
								oct ++; 
								pos = 0; // aqui ele vai pra posição 0 e sobe uma oitava
							}
							else
								pos ++;//caso for natural ele vai para a proxima posição no vetor de notas
							break;
						case 'b':
							if(pos == 0) //nesse caso ele não pode descer mais
							{
								oct --;
								pos = 11; //então ele vai para ultima posição do vetor e desce uma oitava
							}
							else 
								pos --;//nesse caso ele vai pra posição anterior a do vetor de notas
							break;
					}
					songs[count].f[i] = baseNotes[pos]*pow(2, oct); //calculo da oitava, setar a frequencia na oitava exata

					printf("\nInsert duration ratio: ");
					scanf("%lf", &ratio);
					songs[count].d[i] = ratio * baseRatio;//escolha da duração da nota
				}

				fflush(stdin);
				printf("Songs's title: ");
				gets(songs[count].title);
				songs[count].size = n;//guarda quantas notas tem a musica
				break;

			case '2': //consultar músicas
				for(i = 0; i < len_vet; i++)
				{
					printf("\nT�tulo: %s - Posi��o: %i\n", musicas[i].title, i);
				}
				system("pause");
				break;

			case '3': //tocar músicas
				printf("Posi��o da m�sica: ");
				scanf("%i", &s);//peaga a posição da música

				system("cls");
				
				//contador para iniciar a música
				Sleep(500);
				printf("1\n");
				Sleep(500);
				printf("2\n");
				Sleep(500);
				printf("3\n");
				Sleep(500);

				printf("\nPlaying %s", musicas[s].title);
				for(i = 0; i < musicas[s].size; i++)
				{
					Beep(musicas[s].f[i], musicas[s].d[i]);
				}
				break;
			/*
			case '4': //música teste
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
			*/
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

void gravar_arquivo(i_song musica[])
{
	int i;
	int len_vet = sizeof(musica) - 1; //pego o tamanho do vetor

	FILE * arq;

	// abre o arquivo para escrita no modo append
	arq = fopen("musicas.bin", "ab");

	if(arq != NULL)
	{
		for(i = 0; i < len_vet; i++)
			// escreve cada elemento do vetor no arquivo
			fwrite(&musica[i], sizeof(i_song), 1, arq);
		fclose(arq);
	}
	else //se caso ele não consiga abrir o arquivo para gravação
	{
		printf("\nErro ao abrir o arquivo!\n");
		exit(1); // aborta o programa
	}
}

int ler_arquivo(i_song musica[MAX])
{
	// abre o arquivo para leitura
	FILE * arq = fopen("musicas.bin", "rb");

	if(arq != NULL)
	{
		int indice = 0;
		while(1)
		{
			i_song song;

			// fread ler os dados
			// retorna a quantidade de elementos lidos com sucesso
			size_t r = fread(&song, sizeof(i_song), 1, arq);

			// se não houver mais dados para pegar ele sai do loop
			if(r < 1)
				break;
			else
				musica[indice++] = song;
		}
		fclose(arq); // fecha o arquivo
		//retorna o numero de elementos achados no arquivo
		return indice;
	}
	else
	{
		printf("\nErro ao abrir o arquivo para leitura!\n");
		exit(1); // aborta o programa
	}
}
