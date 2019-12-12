/******************************************************************************
 *  Copyright (C) 2019 - Haohua Dong e Diogo Antunes
 *
 *  This file is a part of TentsTreesRepeater.
 *
 *  TentsTreesRepeater is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  TentsTreesRepeater is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *
 * DESCRIÇÃO
 *  Programa que cria mapas do jogo Tents and Trees baseados num mapa já
 *	existente.
 *
 *  Utilização:
 *      <nome_do_programa> nome_do_ficheiro.camp nmr_de_múltiplos
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **Matriz;  // Matriz que representa o mapa
unsigned int L; // Linhas da Matriz
unsigned int C; // Colunas da Matriz
int *Lrests;    // Vetor de tendas por colocar em cada linha
int *Crests;    // Vetor de tendas por colocar em cada coluna

/* Abre o ficheiro */
FILE *AbreFicheiro(char *ficheiro, char *mode) {
  FILE *fp;
  fp = fopen(ficheiro, mode);
  if (fp == NULL)
    exit(0);

  return (fp);
}
/* Descrição: Liberta a matriz de L linhas.
 * */
void _free_matriz() {
  int i;

  if (Matriz == NULL)
    return;
  for (i = 0; i < L; i++) {
    if (Matriz[i] == NULL)
      break;
    free(Matriz[i]);
  }
  free(Matriz);
}

/* Descrição: Lê os vetores com as Hints, o número de tendas em cada linha e
 * coluna, de um ficheiro, guarda-os e calcula a sua soma.
 * Argumentos: Apontador para o ficheiro de entrada, número de linhas e colunas
 * da matriz e apontadores para os vetores onde guardar as Hints.
 * Retorno: -2 se ocorrer erro, -1 se os vetores forem incoerentes ou alguma
 * Hint for negativa, caso contrário o número de tendas.
 * */
int Fill_Hints_checkSums(FILE *fp) {
  int i, j, tendas, res, somaC;

  res = 0;
  tendas = 0;
  somaC = 0;
  for (i = 0; i < L; i++) {
    if (fscanf(fp, " %d", &j) != 1) {
      // Erro de leitura
      res = -2;
      break;
    }
    if (j < 0) {
      // Hint negativa
      res = -1;
    }
    tendas += j;
    Lrests[i] = j;
  }
  for (i = 0; i < C; i++) {
    if (fscanf(fp, " %d", &j) != 1) {
      // Erro de leitura
      res = -2;
      break;
    }
    if (j < 0) {
      // Hint negativa
      res = -1;
    }
    somaC += j;
    Crests[i] = j;
  }
  if (res < 0)
    return res;
  if (tendas != somaC) // Vetores incoerentes
    return -1;
  return tendas;
}

/* Descrição: Lê a matriz do ficheiro, guarda-a e conta as árvores.
 * Argumentos:
 *  fp          - Apontador para o ficheiro com a Matriz.
 *  Matriz      - Apontador para uma tabela de L apontadores para char onde
 *                guardar a matriz lida.
 *  L e C       - Números de linhas e colunas da matriz.
 * Retorno: O número de árvores se ler bem, -1 se ocorrer erro de
 * alocação ou leitura.
 * */
int Fill_Matriz(FILE *fp) {
  int i, j, arvores = 0;
  char format[32]; // String passada a fscanf que define o formato da leitura.

  // Se C for 16 escreve "%16c", para ler 16 caracteres, uma linha, em cada
  // fscanf.
  sprintf(format, " %%%dc", C);

  for (i = 0; i < L; i++) {
    Matriz[i] = (char *)malloc(C * sizeof(char));
    if (Matriz[i] == NULL)
      return -1;
    if (fscanf(fp, format, Matriz[i]) != 1)
      return -1;
    for (j = 0; j < C; j++) {
      if (Matriz[i][j] == 'A')
        arvores++;
    }
  }
  return arvores;
}

int read_file(FILE *fp_problema) {
  int res;
  if (fscanf(fp_problema, " %d", &L) != 1)
    return -1;
  if (fscanf(fp_problema, " %d", &C) != 1)
    return -1;

  // printf("%d %d  ", L, C);

  Lrests = (int *)malloc(L * sizeof(int));
  if (Lrests == NULL)
    return -1;
  Crests = (int *)malloc(C * sizeof(int));
  if (Crests == NULL) {
    free(Lrests);
    return -1;
  }
  // Ler vetores
  res = Fill_Hints_checkSums(fp_problema);

  // Se ocorreu erro
  if (res == -2) {
    free(Crests);
    free(Lrests);
    return -1;
  }

  Matriz = (char **)calloc(L, sizeof(char *));
  if (Matriz == NULL)
    return -1;

  res = Fill_Matriz(fp_problema);
  // Se ocorreu erro
  if (res < 0) {
    free(Crests);
    free(Lrests);
    _free_matriz();
    return -1;
  }
  return 0;
}

void Generate(int multiplication_factor) {
  char ficheirosaida[64];
  FILE *fp_saida;
  int i, j, n;
  printf("%d\n", multiplication_factor);
  // Cria o nome do ficheiro de saída
  sprintf(ficheirosaida, "%d.camp", multiplication_factor);
  fp_saida = AbreFicheiro(ficheirosaida, "w");
  // Escreve Cabeçalho
  fprintf(fp_saida, "%d %d\n", multiplication_factor * L, C);
  // Escreve Hints
  for (n = 0; n < multiplication_factor; n++) {
    for (j = 0; j < L; j++) {
      fprintf(fp_saida, "%d ", Lrests[j]);
    }
  }
  fprintf(fp_saida, "\n");
  for (j = 0; j < C; j++) {
    fprintf(fp_saida, "%d ", Crests[j] * multiplication_factor);
  }
  fprintf(fp_saida, "\n");
  for (n = 0; n < multiplication_factor; n++) {
    // Escreve mapa
    for (i = 0; i < L; i++) {
      for (j = 0; j < C; j++) {
        fprintf(fp_saida, "%c", Matriz[i][j]);
      }
      fprintf(fp_saida, "\n");
    }
  }
  fclose(fp_saida);
}

int main(int argc, char *argv[]) {
  char *p;
  FILE *fp_in;
  int multiples_to_generate;
  double i, base = 1.41421356237;

  if (argc < 3) {
    printf("Usage: <program_name> problem_to_copy.camp "
           "max_multiple_to_generate\n");
    exit(0);
  }

  multiples_to_generate = atoi(argv[2]);

  if (multiples_to_generate == 0) {
    printf("Usage: <program_name> problem_to_copy.camp "
           "max_multiple_to_generate\n");
    exit(0);
  }

  // verificar se o ficheiro de entrada tem extensão '.camp'
  p = strrchr(argv[1], '.');
  if (p == NULL || strcmp(p, ".camp"))
    exit(0);

  fp_in = AbreFicheiro(argv[1], "rb");

  if (read_file(fp_in) != 0) {
    printf("Error reading problem\n");
    exit(0);
  }
  fclose(fp_in);
  for (i = base; multiples_to_generate > 0; multiples_to_generate--) {
    Generate(i + 1);
    i *= base;
  }
  _free_matriz();
  return 0;
}
