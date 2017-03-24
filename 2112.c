#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h> //rand
#include <time.h> //ajudar a randomizar, senão fica constante
#define DIM 4 //DIMENSÃO = 4X4
//http://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
//http://www.linuxforums.org/forum/programming-scripting/88-color-console.html
#define ANSI_COLOR_RED "\033[22;31m"
#define ANSI_COLOR_LIGHT_RED "\033[01;31m"
#define ANSI_COLOR_BLUE "\033[22;34m"
#define ANSI_COLOR_LIGHT_BLUE "\033[01;34m"
#define ANSI_COLOR_MAGENTA "\033[22;35m"
#define ANSI_COLOR_LIGHT_MAGENTA "\033[01;35m"
#define ANSI_COLOR_CYAN    "\033[22;36m"
#define ANSI_COLOR_LIGHT_CYAN "\033[01;36m"
#define ANSI_COLOR_WHITE "\033[01;37m"
#define ANSI_COLOR_GREEN "\033[22;32m"
#define ANSI_COLOR_LIGHT_GREEN "\033[01;32m"
#define ANSI_COLOR_BLACK   "\033[22;30m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void help() {
	printf("\nj - Jogar, w - cima, a - esquerda, s- baixo, d - direita, \n");
	printf("u - Desfazer jogada, h - Ajuda, i - Instruções, r - Recomeçar jogo\n");
	printf("c - Continuar jogo salvo, x - Sair");
}

void regras() { //fazer regras
	printf("\n\t\tCOMPLETE 2112!");
	printf("\n\t<insira regras aqui>\n\n");
}

void gerar_num(float *pmatriz) { //gera número aleatório no começo da jogada
	float vetor[] = {2.0625, 2.0625, 4.125}; //vetor com números sorteados a serem gerados
	int r = -1;
	srand(time(NULL));
	while (r == -1 || *(pmatriz + r) != 0) {
		r = rand() % (DIM * DIM);
	}
	*(pmatriz + r) = vetor[rand() % 3];
}

void imprimir_matriz(float *pmatriz) {
	int i;
	printf("\n");
	for (i = 0; i < DIM * DIM; ++i) {
		if (*(pmatriz + i) == 2112.f) {
			printf(ANSI_COLOR_RED);
		}
		else if (*(pmatriz + i) == 1056.f) {
			printf(ANSI_COLOR_LIGHT_RED);
		}
		else if (*(pmatriz + i) == 528.f) {
			printf(ANSI_COLOR_WHITE);
		}
		else if (*(pmatriz + i) == 264.f) {
			printf(ANSI_COLOR_LIGHT_CYAN);
		}
		else if (*(pmatriz + i) == 132.f) {
			printf(ANSI_COLOR_CYAN);
		}
		else if (*(pmatriz + i) == 66.f) {
			printf(ANSI_COLOR_LIGHT_BLUE);
		}
		else if (*(pmatriz + i) == 33.f) {
			printf(ANSI_COLOR_BLUE);
		}
		else if (*(pmatriz + i) == 16.5f) {
			printf(ANSI_COLOR_MAGENTA);
		}
		else if (*(pmatriz + i) == 8.25f) {
			printf(ANSI_COLOR_LIGHT_MAGENTA);
		}
		else if (*(pmatriz + i) == 4.125f) {
			printf(ANSI_COLOR_LIGHT_GREEN);
		}
		else if (*(pmatriz + i) == 2.0625f) {
			printf(ANSI_COLOR_GREEN);
		}
		else {
			printf(ANSI_COLOR_BLACK);
		}
		
		printf("%9.4f  ", *(pmatriz + i));
		
		if (i % DIM == DIM - 1) {
			printf("\n");
		}
		printf(ANSI_COLOR_RESET);
	}
}

int jogada(char dir, float *pmatriz) { //COMO "ENVIAR UMA MATRIZ" EM C?
	int ret = 0; // 1 = Jogada efetuada | 0 = Jogada impossível | 2 = Venceu o jogo!
	int i, j, aux;
	switch (dir) {
		case 'w': {
			for (j = 0; j < DIM; ++j) {
				for (i = DIM; i < DIM * DIM; i += DIM) { //MOVE OS VALORES
					aux = i;
					while ( *( pmatriz + aux - DIM + j ) == .0f && *(pmatriz + aux + j) > .0f && aux > 0) {
						*(pmatriz + aux - DIM + j) = *(pmatriz + aux + j);
						*(pmatriz + aux + j) = .0f;
						if (ret < 1) { //condição para não mudar valor caso seja 2
							ret = 1;
						}
						aux -= DIM;
					}
				}
				
				for (i = DIM; i < DIM * DIM; i += DIM) { //SOMA OS VALORES
					if ( *(pmatriz + i + j) > 0 && *(pmatriz + i + j) == *(pmatriz + i - DIM + j)) {
						*(pmatriz + i - DIM + j) *= 2;
						*(pmatriz + i + j) = .0f;
						
						if (ret < 1) { //condição para não mudar valor caso seja 2
							ret = 1;
						}
						if (*(pmatriz + i - DIM + j) == 2112.0f) {
							ret = 2;
						}
					}
				}
				
				for (i = DIM; i < DIM * DIM; i += DIM) { //MOVE OS VALORES NOVAMENTE
					aux = i;
					while (*(pmatriz + aux - DIM + j) == .0f && *(pmatriz + aux + j) != .0f && aux > .0f) {
						*(pmatriz + aux - DIM + j) = *(pmatriz + aux + j);
						*(pmatriz + aux + j) = 0;
						//na Segunda vez que move, já não é mais preciso alterar o valor de ret
						aux -= DIM;
					}
				}
			}
			break;
		}
		case 'a': {
			for (j = 0; j < DIM * DIM; j += DIM) {
				for (i = 1; i < DIM; ++i) { //MOVE OS VALORES
					aux = i;
					while ( *( pmatriz + aux - 1 + j ) == .0f && *(pmatriz + aux + j) > .0f && aux > 0) {
						*( pmatriz + aux - 1 + j ) = *(pmatriz + aux + j);
						*(pmatriz + aux + j) = .0f;
						if (ret < 1) { //condição para não mudar valor caso seja 2
							ret = 1;
						}
						--aux;
					}
				}
				
				for (i = 1; i < DIM; ++i) { //SOMA OS VALORES
					if ( *(pmatriz + i + j) > 0 && *(pmatriz + i + j) == *(pmatriz + i - 1 + j)) {
						*(pmatriz + i - 1 + j) *= 2;
						*(pmatriz + i + j) = .0f;
						
						if (ret < 1) { //condição para não mudar valor caso seja 2
							ret = 1;
						}
						if (*(pmatriz + i - 1 + j) == 2112.0f) {
							ret = 2;
						}
					}
				}
				
				for (i = 1; i < DIM; ++i) { //MOVE OS VALORES
					aux = i;
					while ( *( pmatriz + aux - 1 + j ) == .0f && *(pmatriz + aux + j) > .0f && aux > 0) {
						*( pmatriz + aux - 1 + j ) = *(pmatriz + aux + j);
						*(pmatriz + aux + j) = .0f;
						//na Segunda vez que move, já não é mais preciso alterar o valor de ret
						--aux;
					}
				}
			}
			break;
		}
		case 's': {
			for (j = 0; j < DIM; ++j) {
				for (i = DIM * DIM - 2 * DIM; i >= 0; i -= DIM) { //MOVE OS VALORES
					aux = i;
					while ( *( pmatriz + aux + DIM + j ) == .0f && *(pmatriz + aux + j) > .0f && aux < DIM * DIM - DIM) { //aux < DIM * DIM - DIM
						*(pmatriz + aux + DIM + j) = *(pmatriz + aux + j);
						*(pmatriz + aux + j) = .0f;
						if (ret < 1) { //condição para não mudar valor caso seja 2
							ret = 1;
						}
						aux += DIM;
					}
				}
				
				for (i = DIM * DIM - 2 * DIM; i >= 0; i -= DIM) { //SOMA OS VALORES
					if ( *(pmatriz + i + j) > 0 && *(pmatriz + i + j) == *(pmatriz + i + DIM + j)) {
						*(pmatriz + i + DIM + j) *= 2;
						*(pmatriz + i + j) = .0f;
						
						if (ret < 1) { //condição para não mudar valor caso seja 2
							ret = 1;
						}
						if (*(pmatriz + i + DIM + j) == 2112.0f) {
							ret = 2;
						}
					}
				}
				
				for (i = DIM * DIM - 2 * DIM; i >= 0; i -= DIM) { //MOVE OS VALORES NOVAMENTE
					aux = i;
					while ( *( pmatriz + aux + DIM + j ) == .0f && *(pmatriz + aux + j) > .0f && aux < DIM * DIM) {
						*(pmatriz + aux + DIM + j) = *(pmatriz + aux + j);
						*(pmatriz + aux + j) = .0f;
						//na Segunda vez que move, já não é mais preciso alterar o valor de ret
						aux += DIM;
					}
				}
			}
			break;
		}
		case 'd': {
			for (j = 0; j < DIM * DIM; j += DIM) {
				for (i = DIM - 2; i >= 0; --i) { //MOVE OS VALORES
					aux = i;
					while ( *( pmatriz + aux + 1 + j ) == .0f && *(pmatriz + aux + j) > .0f && aux < DIM - 1) {
						*( pmatriz + aux + 1 + j ) = *(pmatriz + aux + j);
						*(pmatriz + aux + j) = .0f;
						if (ret < 1) { //condição para não mudar valor caso seja 2
							ret = 1;
						}
						++aux;
					}
				}
				
				for (i = DIM - 2; i >= 0; --i) { //SOMA OS VALORES
					if ( *(pmatriz + i + j) > 0 && *(pmatriz + i + j) == *(pmatriz + i + 1 + j)) {
						*(pmatriz + i + 1 + j) *= 2;
						*(pmatriz + i + j) = .0f;
						
						if (ret < 1) { //condição para não mudar valor caso seja 2
							ret = 1;
						}
						if (*(pmatriz + i + 1 + j) == 2112.0f) {
							ret = 2;
						}
					}
				}
				
				for (i = DIM - 2; i >= 0; --i) { //MOVE OS VALORES
					aux = i;
					while ( *( pmatriz + aux + 1 + j ) == .0f && *(pmatriz + aux + j) > .0f && aux < DIM - 1) {
						*( pmatriz + aux + 1 + j ) = *(pmatriz + aux + j);
						*(pmatriz + aux + j) = .0f;
						//na Segunda vez que move, já não é mais preciso alterar o valor de ret
						++aux;
					}
				}
			}
			break;
		}
	}
	
	return ret;
}

void jogar(bool continuar) {
	float matriz[DIM][DIM], *pmatriz = &matriz[0][0];
	int i;
	if (!continuar) {
		for (i = 0; i < DIM * DIM; ++i) { // zera a matriz, independentemente do tamanho
			*(pmatriz + i) = 0;
		}
		gerar_num(pmatriz);
		gerar_num(pmatriz);
	}
	else {
		printf("\nCarregando jogo salvo...\n");
		char num_salvo[12];
		float num;
		FILE *arq = fopen("2112.txt", "rt");
		for (i = 0; i < DIM * DIM; ++i) {
			fgets(num_salvo, 12, arq);
			sscanf (num_salvo, "%f", &num);
			*(pmatriz + i) = num;
		}
		fclose(arq);
	}
	
	char op = 'z';
	
	int cond = 1, t; //condição
	while (cond == 1) {
		if (op != 10) {
			printf("\n--------------------------------------------");
			imprimir_matriz(pmatriz);
			printf("--------------------------------------------\n\nOpção: ");
		}
		scanf("%c", &op);
		if (op != 10) {
			op = tolower(op);			
			switch (op) {
				case 'w': {
					printf("Cima");
					t = jogada(op, pmatriz);
					if (t) {
						if (t > 1) {
							cond = t;
						}
						gerar_num(pmatriz);
					}
					else {
						printf("\nIMPOSSÍVEL EFETUAR JOGADA\n");
					}
					break;
				}
				case 'a': {
					printf("Esquerda");
					t = jogada(op, pmatriz);
					if (t) {
						if (t > 1) {
							cond = t;
						}
						gerar_num(pmatriz);
					}
					else {
						printf("\nIMPOSSÍVEL EFETUAR JOGADA\n");
					}
					break;
				}
				case 's': {
					printf("Baixo");
					t = jogada(op, pmatriz);
					if (t) {
						if (t > 1) {
							cond = t;
						}
						gerar_num(pmatriz);
					}
					else {
						printf("\nIMPOSSÍVEL EFETUAR JOGADA\n");
					}
					break;
				}
				case 'd': {
					t = jogada(op, pmatriz);
					if (t) {
						if (t > 1) {
							cond = t;
						}
						gerar_num(pmatriz);
					}
					else {
						printf("\nIMPOSSÍVEL EFETUAR JOGADA\n");
					}
					break;
				}// case P: W.A.S.P;
				case 'h': help(); break;
				case 'i': regras(); break;
				case 'x': {
					printf("Salvando o jogo...");
					FILE *arq = fopen("2112.txt", "w");
					for (i = 0; i < DIM*DIM; ++i) {
						fprintf(arq, "%f\n", *(pmatriz + i));
					}
					fclose(arq);
					cond = 0;
					break;
				}
				default: printf("Opção inválida!\n"); break;
			}
		}
	}
	if (cond == t && cond == 2) {
		printf("\n--------------------------------------------");
		imprimir_matriz(pmatriz);
		printf("--------------------------------------------\n\n");
		printf(ANSI_COLOR_LIGHT_RED "\tPARABÉNS!!!\n");
		printf("Você venceu o desafio! Agora vá em frente, e mostre sua incrível descoberta\n");
		printf("aos sacerdotes, utilizando-a para cantar uma canção...\n");
		printf("\n\n<<Contextualização baseada na música \"2112\", da banda Rush>>\n");
		printf(ANSI_COLOR_RESET);
		
	}
}

void introducao() {
	printf("Você encontrou um estranho dispositivo por trás de uma cachoeira, ");
	printf("num pequeno\nquarto que estava escondido abaixo da caverna.\n\n");
	printf("Você se pergunta o que pode ser essa estranho dispositivo. ");
	printf("Quando o toca, ele\nemite um som. Possui cordas que vibram e fazem música!\n\n");
	printf("Você está ansioso para compartilhar essa nova maravilha, ");
	printf("deixar que as pessoas\nfaçam suas próprias músicas.\n\n");
	printf("Então você decidiu mostrar o estranho instrumento aos Sacerdotes dos Templos de Syrinx. ");
	printf("Entretanto, para ter acesso ao salão, é necessário resolver o seguinte\ndesafio:\n\n");
	regras();
}

int main() {
	introducao();
	char op = 'z';
	while (1) {
		if (op != 10) { //não lê ENTER
			printf("\n\n\nO que deseja fazer? (Escolha h para visualizar a lista de comandos)\nOpção: ");
		}
		scanf("%c", &op);
		if (op != 10) {
			op = tolower(op);
			switch (op) {
				case 'h': help(); break;
				case 'i': regras(); break;
				case 'j': jogar(false); break;
				case 'c': jogar(true); break;
				case 'x': printf("Saindo do programa..."); return 0;
				default: printf("Opção inválida!\n"); break;
			}
		}
	}
}
