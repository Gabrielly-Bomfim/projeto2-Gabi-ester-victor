#include "tarefas.h"
#include <stdio.h>
#include <string.h>

#define categoria_categoria 100
#define descricao_descricao 300

ERROS criar(Tarefa tarefas[], int *pos) {
  if (*pos >= TOTAL)
    return MAX_TAREFA;

  printf("Entre com a prioridade: ");
  scanf("%d", &tarefas[*pos].prioridade);
  if (tarefas[*pos].prioridade < 1 ||
      tarefas[*pos].prioridade > 10) // limitando a prioridade
    return erro_prioridade; // se a prioridade for maior que 10 ou menor que 1,
                            // retornamos 1 erro. Esse novo erro esta no enum da
                            // tarefas.h
  else
    clearBuffer();
  printf("Entre com a categoria: ");
  fgets(tarefas[*pos].categoria, categoria_categoria, stdin);
  clearBuffer(); // eliminando a quebra de linha
  printf("Entre com a descricao: ");
  fgets(tarefas[*pos].descricao, descricao_descricao, stdin);
  clearBuffer(); // tirando a quebra de linha

  *pos = *pos + 1;

  return OK;
}

ERROS deletar(Tarefa tarefas[], int *pos) {
  // teste se existem tarefas
  if (*pos == 0)
    return SEM_TAREFAS;

  // verifica se a tarefa escolhida existe
  int pos_deletar;
  printf("Entre com a posicao da tarefa a ser deletada: ");
  scanf("%d", &pos_deletar);
  pos_deletar--; // garantir posicao certa no array
  if (pos_deletar >= *pos || pos_deletar < 0)
    return NAO_ENCONTRADO;

  for (int i = pos_deletar; i < *pos; i++) {
    tarefas[i].prioridade = tarefas[i + 1].prioridade;
    strcpy(tarefas[i].categoria, tarefas[i + 1].categoria);
    strcpy(tarefas[i].descricao, tarefas[i + 1].descricao);
  }

  *pos = *pos - 1;

  return OK;
}

ERROS listar(Tarefa tarefas[], int *pos) {
  if (*pos == 0)
    return SEM_TAREFAS;
  char cat[100];

  printf("Entre com a categoria: \n");
  fgets(cat, 100, stdin);

  for (int i = 0; i < *pos; i++) {

    if (strcmp(cat, tarefas[i].categoria) == 0) {
      printf("Pos: %d\t", i + 1);
      printf("Prioridade: %d\t", tarefas[i].prioridade);
      tarefas[i].categoria[strlen(tarefas[i].categoria) - 1] = '\0';
      printf("Categoria: %s\t", tarefas[i].categoria);
      printf("Descricao: %s\n", tarefas[i].descricao);
    } else if (strcmp(cat, "\n") == 0) {
      printf("Pos: %d\t", i + 1);
      printf("Prioridade: %d\t", tarefas[i].prioridade);
      tarefas[i].categoria[strlen(tarefas[i].categoria) - 1] = '\0';
      printf("Categoria: %s\t", tarefas[i].categoria);
      printf("Descricao: %s\n", tarefas[i].descricao);
    } else {
      printf("Nenhuma tarefa encontrada\n");
      break;
    }
  }

  return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos) {
  FILE *f = fopen("tarefas.bin", "wb");
  if (f == NULL)
    return ABRIR;

  int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
  if (qtd == 0)
    return ESCREVER;

  qtd = fwrite(pos, 1, sizeof(int), f);
  if (qtd == 0)
    return ESCREVER;

  if (fclose(f))
    return FECHAR;

  return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos) {
  FILE *f = fopen("tarefas.bin", "rb");
  if (f == NULL)
    return ABRIR;

  int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
  if (qtd == 0)
    return LER;

  qtd = fread(pos, 1, sizeof(int), f);
  if (qtd == 0)
    return LER;


    if(fclose(f))
        return FECHAR;

        return OK;
        }
ERROS salvarbinario(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "wb");
        if (f == NULL)
            return ABRIR;
        fwrite(tarefas, sizeof(Tarefa), *pos, f);
         if (fclose(f))
            return FECHAR;
        return OK;
        
    }
ERROS carregarbinario(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "rb");
        if (f == NULL)
            return ABRIR;
        *pos = fread(tarefas, sizeof(Tarefa), TOTAL, f);

            if(fclose(f))
             return FECHAR;
            return OK;
    }


void clearBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}