// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Livro {
	struct Livro *anterior;
	char Titulo[100];
	int Ano_lancamento;
	char Genero_livro[100];
	char Editora[100];
	char Nome_autor[100];
	struct Livro *proximo;
} Livro;

void adicionarLivro(Livro** Livros) {
	char Titulo[100];
	int Ano_lancamento;
	char Genero_livro[100];
	char Editora[100];
	char Nome_autor[100];

	Livro *novo_Livro = (Livro*)malloc(sizeof(Livro));

	if(novo_Livro == NULL) {
		printf("Erro ao alocar memC3ria!\n");
		return;
	}

	printf("Digite o Titulo do Livro: ");
	scanf("%99s", Titulo);
	printf("Digite o ano de LanC'amento: ");
	scanf("%d", &Ano_lancamento);
	printf("Digite o Genero do Livro: ");
	scanf("%99s", Genero_livro);
	printf("Digite o Nome da editora: ");
	scanf("%99s", Editora);
	printf("Digite o Nome do Autor: ");
	scanf("%99s", Nome_autor);

	strcpy(novo_Livro->Titulo, Titulo);
	novo_Livro->Ano_lancamento = Ano_lancamento;
	strcpy(novo_Livro->Genero_livro, Genero_livro);
	strcpy(novo_Livro->Editora, Editora);
	strcpy(novo_Livro->Nome_autor, Nome_autor);

	// InserC'C#o no inC-cio da lista duplamente encadeada
	novo_Livro->proximo = *Livros;
	novo_Livro->anterior = NULL;

	if(*Livros != NULL) {
		(*Livros)->anterior = novo_Livro;
	}

	*Livros = novo_Livro;
}

/*void ordenador(Jogador** topo_ref) {
	int trocado;
	Jogador* atual;
	Jogador* temp;
	Jogador* anterior;

	if(topo_ref == NULL) {
		return;
	}

	do {
		trocado = 0;
		atual = *topo_ref;
		anterior =NULL;

		while(atual->proximo != NULL) {

			if(atual->idade > atual->proximo->idade) {

				temp = atual->proximo;

				if(anterior == NULL) {
					*topo_ref = temp;
				} else
				{
					anterior->proximo = temp;
				}

				atual->proximo = temp->proximo;
				temp->proximo = atual;

				trocado = 1;
				anterior = temp;
			} else {
				anterior = atual;
				atual = atual->proximo;
			}
		}
	} while(trocado);

}*/



void imprimirLista(Livro **lista) {
	Livro *atual = *lista;
	printf("\nLista de Livros:\n");
	while(atual != NULL) {
		printf("TC-tulo: %s\n", atual->Titulo);
		printf("Ano: %d\n", atual->Ano_lancamento);
		printf("GC*nero: %s\n", atual->Genero_livro);
		printf("Editora: %s\n", atual->Editora);
		printf("Autor: %s\n\n", atual->Nome_autor);
		atual = atual->proximo;
	}
}

int main()
{
	Livro* topo = NULL;
	Livro* liberar = topo;
	bool loop = true;
	int opcao;

	while(loop)
	{
		printf("\nMenu:\n");
		printf("Digite: 1 / Cadastrar Livros\n");
		printf("Digite: 2 / Ordenar Jogadores\n");
		printf("Digite: 3 /Lista Livros\n");
		printf("Digite: 4 /Sair\n");
		scanf("%d", &opcao);

		switch(opcao) {
		case 1:
			adicionarLivro(&topo);
			break;

		case 2:
			//ordenador(&topo);
			break;

		case 3:
			printf("Jogadores cadastrados: \n\n");
			imprimirLista(&topo);

			Livro* temp;

			while(liberar != NULL) {
				temp = liberar;
				liberar = liberar->proximo;
				free(temp);
			}
			break;

		case 4:
			loop = false;
			break;

		default: {
			printf("opcao invalida, tente novamente.");
			break;
		}
		};
	};
	return 0;
}