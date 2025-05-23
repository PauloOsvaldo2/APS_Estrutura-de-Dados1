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
	char Genero_secundario_livro[100];
	char Editora[100];
	char Nome_autor[100];
	struct Livro *proximo;
} Livro;

typedef struct emprestimos {
	char Titulo[100];
	int Ano_lancamento;
	char Genero_livro[100];
	char Genero_secundario_livro[100];
	char Editora[100];
	char Nome_autor[100];
	struct emprestimos *proximo;
} emprestimos;

void adicionarLivro(Livro** Livros) {
	char Titulo[100];
	int Ano_lancamento;
	char Genero_livro[100];
	char Genero_secundario_livro[100];
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

	printf("Digite o Genero secundario do Livro: ");
	scanf("%99s", Genero_secundario_livro);

	printf("Digite o Nome da editora: ");
	scanf("%99s", Editora);

	printf("Digite o Nome do Autor: ");
	scanf("%99s", Nome_autor);


	strcpy(novo_Livro->Titulo, Titulo);
	novo_Livro->Ano_lancamento = Ano_lancamento;
	strcpy(novo_Livro->Genero_livro, Genero_livro);
	strcpy(novo_Livro->Genero_secundario_livro, Genero_secundario_livro);
	strcpy(novo_Livro->Editora, Editora);
	strcpy(novo_Livro->Nome_autor, Nome_autor);

	novo_Livro->proximo = *Livros;
	novo_Livro->anterior = NULL;

	if(*Livros != NULL) {
		(*Livros)->anterior = novo_Livro;
	}

	*Livros = novo_Livro;
}

void ordenadorMergeSort(Livro** Livros) {

	if (*Livros == NULL || (*Livros)->proximo == NULL) {
		return;
	}

	Livro* rapido = (*Livros)->proximo;
	Livro* lento = *Livros;

	while (rapido != NULL && rapido->proximo != NULL) {
		rapido = rapido->proximo->proximo;
		lento = lento->proximo;
	}

	Livro* segundaParte = lento->proximo;
	lento->proximo = NULL;
	if (segundaParte != NULL) {
		segundaParte->anterior = NULL;
	}

	ordenadorMergeSort(Livros);
	ordenadorMergeSort(&segundaParte);

	Livro* mesclar(Livro* a, Livro* b) {
		if (a == NULL) return b;
		if (b == NULL) return a;


		if (strcmp(a->Titulo, b->Titulo) <= 0) {
			a->proximo = mesclar(a->proximo, b);
			a->proximo->anterior = a;
			a->anterior = NULL;
			return a;
		} else {
			b->proximo = mesclar(a, b->proximo);
			b->proximo->anterior = b;
			b->anterior = NULL;
			return b;
		}
	}


	*Livros = mesclar(*Livros, segundaParte);
}

void ordenadorSelectionSort(Livro** Livros) {
	Livro* atual = *Livros;

	while (atual != NULL) {

		Livro* min = atual;
		Livro* temp = atual->proximo;

		while (temp != NULL) {
			if (strcmp(temp->Titulo, min->Titulo) < 0) {
				min = temp;
			}
			temp = temp->proximo;
		}

		if (min != atual) {

			Livro* antAtual = atual->anterior;
			Livro* proxAtual = atual->proximo;
			Livro* antMin = min->anterior;
			Livro* proxMin = min->proximo;

			if (atual->proximo == min) {
				atual->proximo = proxMin;
				if (proxMin != NULL) proxMin->anterior = atual;

				min->proximo = atual;
				atual->anterior = min;

				min->anterior = antAtual;
				if (antAtual != NULL) antAtual->proximo = min;
				else *Livros = min;
			}

			else {

				atual->proximo = proxMin;
				if (proxMin != NULL) proxMin->anterior = atual;

				atual->anterior = antMin;
				if (antMin != NULL) antMin->proximo = atual;
				else *Livros = atual;


				min->proximo = proxAtual;
				if (proxAtual != NULL) proxAtual->anterior = min;

				min->anterior = antAtual;
				if (antAtual != NULL) antAtual->proximo = min;
				else *Livros = min;
			}

			atual = min->proximo;
		} else {
			atual = atual->proximo;
		}
	}
}

void imprimirLista(Livro **lista) {
	Livro *atual = *lista;
	printf("\nLista de Livros:\n");
	while(atual != NULL) {
		printf("TC-tulo: %s\n", atual->Titulo);
		printf("Ano: %d\n", atual->Ano_lancamento);
		printf("GC*nero: %s\n", atual->Genero_livro);
		printf("GC*nero secundario: %s\n", atual->Genero_secundario_livro);
		printf("Editora: %s\n", atual->Editora);
		printf("Autor: %s\n\n", atual->Nome_autor);
		atual = atual->proximo;
	}
}

void imprimirLista_emprestimos(emprestimos **lista) {
	emprestimos *atual = *lista;
	printf("\nLista de emprestimos:\n");
	while(atual != NULL) {
		printf("TC-tulo: %s\n", atual->Titulo);
		printf("Ano: %d\n", atual->Ano_lancamento);
		printf("GC*nero: %s\n", atual->Genero_livro);
		printf("GC*nero secundario: %s\n", atual->Genero_secundario_livro);
		printf("Editora: %s\n", atual->Editora);
		printf("Autor: %s\n\n", atual->Nome_autor);
		atual = atual->proximo;
	}
}

void removerLivro(Livro** lista, char* titulo) {
    if (*lista == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    Livro* atual = *lista;
    Livro* anterior = NULL;

    // Percorre a lista procurando o livro
    while (atual != NULL && strcmp(atual->Titulo, titulo) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Livro não encontrado
    if (atual == NULL) {
        printf("Livro com título '%s' não encontrado!\n", titulo);
        return;
    }

    // Atualiza os ponteiros para remover o nó
    if (anterior == NULL) {
        // Remoção do primeiro elemento
        *lista = atual->proximo;
        if (atual->proximo != NULL) {
            atual->proximo->anterior = NULL;
        }
    } else {
        anterior->proximo = atual->proximo;
        if (atual->proximo != NULL) {
            atual->proximo->anterior = anterior;
        }
    }

    // Libera a memória do livro removido
    free(atual);
    printf("Livro '%s' removido com sucesso!\n", titulo);
}

void removerParaEmprestimo(Livro** lista_livros, emprestimos** lista_emprestimos, char* titulo) {
    // Verifica se a lista de livros está vazia
    if (*lista_livros == NULL) {
        printf("Lista de livros vazia!\n");
        return;
    }

    // Procura o livro na lista
    Livro* atual = *lista_livros;
    Livro* anterior = NULL;

    while (atual != NULL && strcmp(atual->Titulo, titulo) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Livro não encontrado
    if (atual == NULL) {
        printf("Livro com título '%s' não encontrado!\n", titulo);
        return;
    }

    // Remove o livro da lista de livros
    if (anterior == NULL) {
        *lista_livros = atual->proximo;
        if (atual->proximo != NULL) {
            atual->proximo->anterior = NULL;
        }
    } else {
        anterior->proximo = atual->proximo;
        if (atual->proximo != NULL) {
            atual->proximo->anterior = anterior;
        }
    }

    // Cria novo registro de empréstimo
    emprestimos* novo_emprestimo = (emprestimos*)malloc(sizeof(emprestimos));
    if (novo_emprestimo == NULL) {
        printf("Erro ao alocar memória para empréstimo!\n");
        return;
    }

    // Copia os dados do livro para o empréstimo
    strcpy(novo_emprestimo->Titulo, atual->Titulo);
    novo_emprestimo->Ano_lancamento = atual->Ano_lancamento;
    strcpy(novo_emprestimo->Genero_livro, atual->Genero_livro);
    strcpy(novo_emprestimo->Genero_secundario_livro, atual->Genero_secundario_livro);
    strcpy(novo_emprestimo->Editora, atual->Editora);
    strcpy(novo_emprestimo->Nome_autor, atual->Nome_autor);

    // Insere no início da lista de empréstimos
    novo_emprestimo->proximo = *lista_emprestimos;
    *lista_emprestimos = novo_emprestimo;

    // Libera o livro da lista original
    free(atual);
    printf("Livro '%s' movido para empréstimos com sucesso!\n", titulo);
}

void devolverParaLivros(emprestimos** lista_emprestimos, Livro** lista_livros, char* titulo) {
    // Verifica se a lista de empréstimos está vazia
    if (*lista_emprestimos == NULL) {
        printf("Lista de empréstimos vazia!\n");
        return;
    }

    // Procura o livro na lista de empréstimos
    emprestimos* atual = *lista_emprestimos;
    emprestimos* anterior = NULL;

    while (atual != NULL && strcmp(atual->Titulo, titulo) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Livro não encontrado
    if (atual == NULL) {
        printf("Livro com título '%s' não encontrado nos empréstimos!\n", titulo);
        return;
    }

    // Remove o livro da lista de empréstimos
    if (anterior == NULL) {
        *lista_emprestimos = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    // Cria novo registro na lista de livros
    Livro* novo_livro = (Livro*)malloc(sizeof(Livro));
    if (novo_livro == NULL) {
        printf("Erro ao alocar memória para livro!\n");
        return;
    }

    // Copia os dados do empréstimo para o livro
    strcpy(novo_livro->Titulo, atual->Titulo);
    novo_livro->Ano_lancamento = atual->Ano_lancamento;
    strcpy(novo_livro->Genero_livro, atual->Genero_livro);
    strcpy(novo_livro->Genero_secundario_livro, atual->Genero_secundario_livro);
    strcpy(novo_livro->Editora, atual->Editora);
    strcpy(novo_livro->Nome_autor, atual->Nome_autor);

    // Insere no início da lista de livros (duplamente encadeada)
    novo_livro->proximo = *lista_livros;
    novo_livro->anterior = NULL;
    
    if (*lista_livros != NULL) {
        (*lista_livros)->anterior = novo_livro;
    }
    
    *lista_livros = novo_livro;

    // Libera o empréstimo
    free(atual);
    printf("Livro '%s' devolvido para a lista de livros com sucesso!\n", titulo);
}

int main()
{
	Livro* topo = NULL;
	Livro* liberar = topo;
	emprestimos* cabeca = NULL;
	bool loop = true;
	char chave[100];
	int opcao;

	while(loop)
	{
		printf("\nMenu:\n");
		printf("Digite: 1 / Cadastrar Livros\n");
		printf("Digite: 2 / Ordenar livros pro mergeSort\n");
		printf("Digite: 3 / Ordenar livros por selectionSort\n");
		printf("Digite: 4 / remover Livro\n");
		printf("Digite: 5 / emprestar Livro\n");
		printf("Digite: 6 / Devolver livro\n");
		printf("Digite: 7 /Lista Livros\n");
		printf("Digite: 8 /Lista emprestimos\n");
		printf("Digite: 9 /Sair\n");
		scanf("%d", &opcao);

		switch(opcao) {
		case 1:
			adicionarLivro(&topo);
			break;

		case 2:
			ordenadorMergeSort(&topo);
			break;

		case 3:
			ordenadorSelectionSort(&topo);
			break;
			
		case 4:
		    printf("qual titulo de livro vc quer retirar: ");
		    scanf("%99s", chave);
			removerLivro(&topo, chave);
			break;
		
		case 5:
		    printf("qual titulo de livro vc quer emprestar: ");
		    scanf("%99s", chave);
			removerParaEmprestimo(&topo, &cabeca, chave);
			break;
			
		case 6:
		    printf("qual titulo de livro vc quer devolver: ");
		    scanf("%99s", chave);
			devolverParaLivros(&cabeca, &topo, chave);
			break;
			
		case 7:
			printf("Livros cadastrados: \n\n");
			imprimirLista(&topo);

			Livro* temp;

			while(liberar != NULL) {
				temp = liberar;
				liberar = liberar->proximo;
				free(temp);
			}
			break;
			
			case 8:
			printf("emprestimos cadastrados: \n\n");
			imprimirLista_emprestimos(&cabeca);

			emprestimos* temp_emprestimo;

			while(liberar != NULL) {
				temp_emprestimo = liberar;
				liberar = liberar->proximo;
				free(temp_emprestimo);
			}
			break;

		case 9:
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
