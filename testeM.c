#include <stdio.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <locale.h>

#define MAX 50 

//declaração da struct song
typedef struct song
{
	char title[30];
	int bpm;
	int n[50]; //posições da nota no vetor baseNotes
	int d[50]; //durações escolhidas
	char aumento[50];
	int size;
} i_song;


int processNote(char note);
void gravar_arquivo(i_song musica);
int ler_arquivo(i_song musica[MAX]);
void reescrever(i_song musica[], int tam);
void metronomo(int bpm);
int confereDur(int d);
void construirString(char n, int d, char aum);

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Portuguese");

	double const baseNotes[12] = {32.70, 34.65, 36.71, 38.89, 41.20, 43.65, 46.25, 49.00, 51.91, 55.00, 58.27, 61.74};//frequencias basicas a partir da primeira oitava de um teclado

	int q, bpm, i, pos, oct, d, s, aux = 0, len_vet, nota;

	char note, type, cont;

	//declaração do vetor de musicas salvas
	i_song musicas[MAX];

	i_song atual; //música atual
	
	double ratio; //duração de uma nota

	char op;
	int e = 0;
	
	do
	{
		system("cls");
		printf("\nCriar música - 1\nConsultar músicas - 2\nTocar música - 3\nSair - qualquer outra coisa outra coisa");
		printf("\n\nOpção: ");
		op = getche();
		printf("\n");
		switch(op)
		{
			case '1': //criar música
				printf("\nCriar música");
				
				printf("Defina o andamento em bpm (batidas por minuto) com um valor inteiro: ");
				scanf("%i", &bpm);
				
				metronomo(bpm);
				
				atual.bpm = bpm;
				
				printf("\nNúmero de notas: ");
				scanf("%i", &q);
				
				for(i = 0; i < q; i++)
				{
					system("cls");
					do
					{
						printf("\nQue nota é? ");
						printf("\n c -> dó\n d -> ré\ne -> mi\nf -> fá\ng->sol\na -> lá\nb -> si");
						note = getche();//recebe um caracter que corresponde a uma nota
					}
					while(note < 97 || note > 103); //verifica se a coisa digitada esta entre o intervalo de notas validas
					pos = processNote(note);
					
					printf("\nOitava: ");
					scanf("%i", &oct);//guarda a oitava na qual a nota esta
					printf("'#' para sustenido (sobe um semitom), 'b' para bemol (desce um semitom) e qualquer outra coisa para natural\n");
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
					//songs.f[i] = baseNotes[pos]*pow(2, oct); //cálculo da oitava, setar a frequência na oitava exata
					
					atual.n[i] = pos;
					
					do
					{
						printf("\nInsira a duração: ");
						printf("\n1 -> semibreve (dura 4 batidas)\n2 -> mínima (dura 2 batidas)\n4 -> semínima (dura 1 batida)\n8 -> colcheia (dura meia batida)\n16 -> semicolcheia (dura um quarto de batida)");
						scanf("%i", &d);
					}
					while(confereDur(d) > 0)
					
					atual.d[i] = d;
					
					printf("\n Ponto de aumento? (aumenta a duração em 50%)");
					printf("\n Insira '.' para sim e outra coisa para não");
					
					atual.aumento[i] = getche();
				}

				fflush(stdin);
				printf("Título da música: ");
				gets(atual.title);
				
				atual.size = q; //guarda quantas notas tem a música
				gravar_arquivo(atual);
				break;
				
			case '2':
				printf("\tLista de músicas\n");
				len_vet = ler_arquivo(musicas);
				for(i = 0; i < len_vet; i++)
				{
					printf("\nTítulo: %s - Posição: %i\n", musicas[i].title, i);
				}
				system("pause");
				break;

			case '3': //tocar mmúsica
				ler_arquivo(musicas);
				printf("Posição da música: ");
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

				printf("\nTocando %s", musicas[s].title);
				for(i = 0; i < musicas[s].size; i++)
				{
					Beep(musicas[s].f[i], musicas[s].d[i]);
				}
				break;
				
			case '4':
				printf("\tLista de músicas\n");
				len_vet = ler_arquivo(musicas);
				
				//listagem das músicas
				for(i = 0; i < len_vet; i++)
				{
					printf("\nTítulo: %s - Posição: %i\n", musicas[i].title, i);
				}

				printf("Qual música você deseja apagar? ");
				scanf("%i", &s);

				for(i = s; i < len_vet - 1; i++) 
					musicas[i] = musicas[i+1];

				reescrever(musicas, len_vet-1);
				break;
				
			case '5':
				printf("\tLista de músicas\n");
				len_vet = ler_arquivo(musicas);
				
				//listagem das músicas
				for(i = 0; i < len_vet; i++)
				{
					printf("\nTítulo: %s - Posição: %i\n", musicas[i].title, i);
				}
				
				printf("Qual música você deseja editar? ");
				scanf("%i", &s);
				
				system("cls");
				
				printf("%s selecionada com sucesso!", musicas[s].title);
				
				printf("\n1 -> editar andamento (andamento atual: %i bpm)\n2 -> visualizar e editar notas\nOutro valor para voltar", musicas[s].bpm);
				op = getche();
				
				switch(op)
				{
					case '1':
						printf("Defina o andamento em bpm (batidas por minuto) com um valor inteiro: ");
						scanf("%i", &bpm);
						
						metronomo(bpm);
						
						musicas[s].bpm = bpm;
						break;
						
					case '2':
						for(i = 0; i < musicas[s].size; i++)
						{
							printf("\nPosição %i: ", i + 1);
							construirString(musicas[s].n[i], musicas[s].d[i], musicas[s].aumento[i]);
						}
						
						do
						{
							printf("Editar nota de posição: ");
							scanf("%i", &nota);
							
							do
							{
								printf("\nQue nota é? ");
								printf("\n c -> dó\n d -> ré\ne -> mi\nf -> fá\ng->sol\na -> lá\nb -> si");
								note = getche();//recebe um caracter que corresponde a uma nota
							}
							while(note < 97 || note > 103); //verifica se a coisa digitada esta entre o intervalo de notas validas
							pos = processNote(note);
							
							printf("\nOitava: ");
							scanf("%i", &oct);//guarda a oitava na qual a nota esta
							printf("'#' para sustenido (sobe um semitom), 'b' para bemol (desce um semitom) e qualquer outra coisa para natural\n");
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
							//songs.f[i] = baseNotes[pos]*pow(2, oct); //cálculo da oitava, setar a frequência na oitava exata
							
							musicas[s].n[nota] = pos;
							
							do
							{
								printf("\nInsira a duração: ");
								printf("\n1 -> semibreve (dura 4 batidas)\n2 -> mínima (dura 2 batidas)\n4 -> semínima (dura 1 batida)\n8 -> colcheia (dura meia batida)\n16 -> semicolcheia (dura um quarto de batida)");
								scanf("%i", &d);
							}
							while(confereDur(d) > 0)
							
							atual.d[nota] = d;
							
							printf("\n Ponto de aumento? (aumenta a duração em 50%)");
							printf("\n Insira '.' para sim e outra coisa para não");
							
							atual.aumento[nota] = getche();
							
							printf("Nota %i atualizada com sucesso!", )
						}
						while(cont == '1')
				}
				
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
	else //se caso ele nÃ£o consiga abrir o arquivo para gravação
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
		printf("\nErro ao abrir o arquivo!\n");
		exit(1); // aborta o programa
	}
}

void metronomo(int bpm)
{
	float b = 60/bpm * 1000;
	int i;
	
	for(i = 0; i < 4; i++)
	{
		Beep(440, b);
	}
}

int confereDur(int d)
{
	int valido[5] = {1, 2, 4, 8, 16}, i;
	int r = 0;
	
	for(i = 0; i < 5; i++)
	{
		if(d == valido[i])
		{
			r++;
			break;
		}
	}
	
	return r;
}

void construirString(int n, int d, char aum)
{
	switch(n)
	{
		case '0':
			printf("Dó natural");
			break;
		
		case '1':
			printf("Dó sustenido / Ré bemol");
			break;
			
		case '2':
			printf("Ré natural");
			break;
			
		case '3':
			printf("Ré sustenido / Mi bemol");
			break;
		
		case '4':
			printf("Mi natural / Fá bemol");
			break;
			
		case '5':
			printf("Fá natural");
			break;
			
		case '6':
			printf("Fá sustenido / Sol bemol");
			break;
			
		case '7':
			printf("Sol natural");
			break;
		
		case '8':
			printf("Sol sustenido / Lá bemol");
			break;
			
		case '9':
			printf("Lá natural");
			break;
			
		case '10':
			printf("Lá sustenido / Si bemol");
			break;
		
		case '11':
			printf("Si natural / Dó bemol");
	}
	
	printf(" | ");
	
	switch(d)
	{
		case '1':
			printf("Semibreve (4 batidas)");
			break;
		
		case '2':
			printf("Mínima (2 batidas)");
			break;
			
		case '4':
			printf("Semínima (1 batida)");
			break;
			
		case '8':
			printf("Colcheia (meia batida)");
			break;
		
		case '16':
			printf("Semicolcheia (um quarto de batida)");
			break;
	}
	
	if(aum == '.')
	{
		printf("com ponto de aumento");
	}
	
	printf(";");
}
