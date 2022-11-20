#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <locale.h>

#define MAX 50 

//declação da struct song
typedef struct song
{
	char title[30];
	double f[50]; //frequencias
	double d[50]; //duração de uma nota
	int size;
} i_song;


int processNote(char note);
void gravar_arquivo(i_song musica);
int ler_arquivo(i_song musica[MAX]);
void reescrever(i_song musica[], int tam);

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Portuguese");

	double const baseNotes[12] = {32.70, 34.65, 36.71, 38.89, 41.20, 43.65, 46.25, 49.00, 51.91, 55.00, 58.27, 61.74};//frequencias basicas a partir da primeira oitava de um teclado

	int const baseRatio = 500;//duração base em milisegundos

	int n, i, pos, oct, count = -1, s, aux = 0, len_vet;

	char note, type;

	//declaração do vetor de musicas salvas
	i_song musicas[MAX];

	i_song songs;
	
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
					songs.f[i] = baseNotes[pos]*pow(2, oct); //calculo da oitava, setar a frequencia na oitava exata

					printf("\nInsert duration ratio: ");
					scanf("%lf", &ratio);
					songs.d[i] = ratio * baseRatio;//escolha da duração da nota
				}

				fflush(stdin);
				printf("Songs's title: ");
				gets(songs.title);
				songs.size = n;//guarda quantas notas tem a musica
				gravar_arquivo(songs);
				break;
			case '2':
				printf("\tLista de musicas\n");
				len_vet = ler_arquivo(musicas);
				for(i = 0; i < len_vet; i++)
				{
					printf("\nT�tulo: %s - Posi��o: %i\n", musicas[i].title, i);
				}
				system("pause");
				break;

			case '3': //tocar músicas
				ler_arquivo(musicas);
				printf("Posi��o da m�sica: ");
				scanf("%i", &s);//pega a posição da música

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
			case '4':
				printf("\tLista de músicas\n");
				len_vet = ler_arquivo(musicas);
				int opcmusica, aux = 0;
				//listagem das músicas
				for(i = 0; i < len_vet; i++)
				{
					printf("\nTítulo: %s - Posição: %i\n", musicas[i].title, i);
				}

				printf("Qual música você deseja apagar? ");
				scanf("%i", &opcmusica);

				for(i = opcmusica; i < len_vet - 1; i++) 
					musicas[i] = musicas[i+1];

				reescrever(musicas, len_vet-1);
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

void gravar_arquivo(i_song musica)
{
	FILE * arq;

	// abre o arquivo para escrita no modo append
	arq = fopen("musicas.txt", "ab");

	if(arq != NULL)
	{
		// escreve cada elemento do vetor no arquivo
		fwrite(&musica, sizeof(i_song), 1, arq);
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
	FILE * arq = fopen("musicas.txt", "rb");
	i_song song;

	if(arq != NULL)
	{
		int indice = 0;
		while( fread(&song, sizeof(i_song), 1, arq) == 1 )
		{
			musica[indice++] = song;
		}
		fclose(arq); // fecha o arquivo
		return indice;//retorna o numero de elementos achados no arquivo
	}
	else
	{
		printf("\nErro ao abrir o arquivo para leitura!\n");
		exit(1); // aborta o programa
	}
}

void reescrever(i_song musica[], int tam)
{
	// abre o arquivo para leitura
	FILE * arq = fopen("musicas.txt", "wb");

	if(arq != NULL)
	{
		int i;
		
		for(i = 0; i<tam; i++)
			fwrite(&musica[i], sizeof(i_song), 1, arq);
		fclose(arq); // fecha o arquivo
	}
	else
	{
		printf("\nErro ao abrir o arquivo para leitura!\n");
		exit(1); // aborta o programa
	}
}
