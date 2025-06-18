#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <strings.h>

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
    char Data_emprestimo[20];
    struct emprestimos *proximo;
} emprestimos;

void salvarLivrosCSV(Livro *livros) {
    FILE *file = fopen("livros.csv", "w");
    if (file == NULL) {
        perror("Erro ao abrir arquivo livros.csv");
        return;
    }
    Livro *atual = livros;
    while (atual != NULL) {
        fprintf(file, "%s,%d,%s,%s,%s,%s\n", 
            atual->Titulo,
            atual->Ano_lancamento,
            atual->Genero_livro,
            atual->Genero_secundario_livro,
            atual->Editora,
            atual->Nome_autor);
        atual = atual->proximo;
    }
    fclose(file);
}

void salvarEmprestimosCSV(emprestimos *emp) {
    FILE *file = fopen("emprestimos.csv", "w");
    if (file == NULL) {
        perror("Erro ao abrir arquivo emprestimos.csv");
        return;
    }
    emprestimos *atual = emp;
    while (atual != NULL) {
        fprintf(file, "%s,%d,%s,%s,%s,%s,%s\n",
            atual->Titulo,
            atual->Ano_lancamento,
            atual->Genero_livro,
            atual->Genero_secundario_livro,
            atual->Editora,
            atual->Nome_autor,
            atual->Data_emprestimo);
        atual = atual->proximo;
    }
    fclose(file);
}

void carregarLivrosCSV(Livro **livros) {
    FILE *file = fopen("livros.csv", "r");
    if (file == NULL) {
        return;
    }
    char linha[500];
    while (fgets(linha, sizeof(linha), file) != NULL) {
        linha[strcspn(linha, "\n")] = 0;
        char Titulo[100], Genero_livro[100], Genero_secundario_livro[100], Editora[100], Nome_autor[100];
        int Ano_lancamento;
        if (sscanf(linha, "%99[^,],%d,%99[^,],%99[^,],%99[^,],%99[^,\n]",
                   Titulo, &Ano_lancamento, Genero_livro, Genero_secundario_livro, Editora, Nome_autor) != 6) {
            continue;
        }
        Livro *novo = (Livro*)malloc(sizeof(Livro));
        if (novo == NULL) {
            printf("Erro de memória ao carregar livros\n");
            break;
        }
        strcpy(novo->Titulo, Titulo);
        novo->Ano_lancamento = Ano_lancamento;
        strcpy(novo->Genero_livro, Genero_livro);
        strcpy(novo->Genero_secundario_livro, Genero_secundario_livro);
        strcpy(novo->Editora, Editora);
        strcpy(novo->Nome_autor, Nome_autor);
        novo->proximo = *livros;
        novo->anterior = NULL;

        if (*livros != NULL) {
            (*livros)->anterior = novo;
        }
        *livros = novo;
    }
    fclose(file);
}

void carregarEmprestimosCSV(emprestimos **emp) {
    FILE *file = fopen("emprestimos.csv", "r");
    if (file == NULL) {
        return;
    }
    char linha[500];
    while (fgets(linha, sizeof(linha), file) != NULL) {
        linha[strcspn(linha, "\n")] = 0;
        char Titulo[100], Genero_livro[100], Genero_secundario_livro[100], Editora[100], Nome_autor[100], Data_emprestimo[20];
        int Ano_lancamento;
        if (sscanf(linha, "%99[^,],%d,%99[^,],%99[^,],%99[^,],%99[^,],%19[^,\n]",
                   Titulo, &Ano_lancamento, Genero_livro, Genero_secundario_livro, Editora, Nome_autor, Data_emprestimo) != 7) {
            continue;
        }
        emprestimos *novo = (emprestimos*)malloc(sizeof(emprestimos));
        if (novo == NULL) {
            printf("Erro de memória ao carregar empréstimos\n");
            break;
        }
        strcpy(novo->Titulo, Titulo);
        novo->Ano_lancamento = Ano_lancamento;
        strcpy(novo->Genero_livro, Genero_livro);
        strcpy(novo->Genero_secundario_livro, Genero_secundario_livro);
        strcpy(novo->Editora, Editora);
        strcpy(novo->Nome_autor, Nome_autor);
        strcpy(novo->Data_emprestimo, Data_emprestimo);
        novo->proximo = *emp;
        *emp = novo;
    }
    fclose(file);
}

void adicionarLivro(Livro** Livros) {
    char Titulo[100];
    int Ano_lancamento;
    char Genero_livro[100];
    char Genero_secundario_livro[100];
    char Editora[100];
    char Nome_autor[100];

    Livro *novo_Livro = (Livro*)malloc(sizeof(Livro));
    if(novo_Livro == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    printf("Digite o Titulo do Livro: ");
    scanf(" %[^\n]", Titulo);
    printf("Digite o ano de Lançamento: ");
    scanf(" %d", &Ano_lancamento);
    printf("Digite o Genero do Livro: ");
    scanf(" %[^\n]", Genero_livro);
    printf("Digite o Genero secundario do Livro: ");
    scanf(" %[^\n]", Genero_secundario_livro);
    printf("Digite o Nome da editora: ");
    scanf(" %[^\n]", Editora);
    printf("Digite o Nome do Autor: ");
    scanf(" %[^\n]", Nome_autor);

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

int compararStrings(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        int c1 = tolower((unsigned char)*s1);
        int c2 = tolower((unsigned char)*s2);
        
        if (c1 != c2) {
            return c1 - c2;
        }
        
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

void Dividir_lista(Livro *fonte, Livro **frente, Livro **tras) {
    Livro *rapido;
    Livro *lento;
    
    if (fonte == NULL || fonte->proximo == NULL) {
        *frente = fonte;
        *tras = NULL;
        return;
    }
    
    lento = fonte;
    rapido = fonte->proximo;
    
    while (rapido != NULL) {
        rapido = rapido->proximo;
        if (rapido != NULL) {
            lento = lento->proximo;
            rapido = rapido->proximo;
        }
    }
    
    *frente = fonte;
    *tras = lento->proximo;
    lento->proximo = NULL;
    if (*tras != NULL) {
        (*tras)->anterior = NULL;
    }
}

Livro* merge(Livro *a, Livro *b, char *criterio) {
    Livro *resultado = NULL;
    
    if (a == NULL) 
        return b;
    else if (b == NULL)
        return a;
    
    if (strcmp(criterio, "Titulo") == 0) {
        if (compararStrings(a->Titulo, b->Titulo) <= 0) {
            resultado = a;
            resultado->proximo = merge(a->proximo, b, criterio);
        } else {
            resultado = b;
            resultado->proximo = merge(a, b->proximo, criterio);
        }
    } 
    else if (strcmp(criterio, "Ano_lancamento") == 0) {
        if (a->Ano_lancamento <= b->Ano_lancamento) {
            resultado = a;
            resultado->proximo = merge(a->proximo, b, criterio);
        } else {
            resultado = b;
            resultado->proximo = merge(a, b->proximo, criterio);
        }
    }
    
    if (resultado->proximo != NULL) {
        resultado->proximo->anterior = resultado;
    }
    resultado->anterior = NULL;
    return resultado;
}

void mergeSort(Livro **headRef, char *criterio) {
    Livro *cabeca = *headRef;
    Livro *a;
    Livro *b;
    
    if (cabeca == NULL || cabeca->proximo == NULL) {
        return;
    }
    
    Dividir_lista(cabeca, &a, &b);
    
    mergeSort(&a, criterio);
    mergeSort(&b, criterio);
    
    *headRef = merge(a, b, criterio);
    if (*headRef != NULL && (*headRef)->proximo != NULL) {
        (*headRef)->proximo->anterior = *headRef;
    }
}

void ordenadorMergeSort(Livro** Livros) {
    if (*Livros == NULL || (*Livros)->proximo == NULL) {
        return; // Lista vazia ou com apenas um elemento
    }
    
    int opcao;
    printf("\nMergeSort - Escolha o critério:\n");
    printf("1 - Ordenar por título\n");
    printf("2 - Ordenar por Ano\n");
    scanf("%d", &opcao);
    
    if (opcao == 1) {
        mergeSort(Livros, "Titulo"); // Ordenar por título
        printf("Livros ordenados por título.\n");

    } else if (opcao == 2) {
        mergeSort(Livros, "Ano_lancamento"); // Ordenar por ano
        printf("Livros ordenados por ano.\n");
    } else {
        printf("Opção inválida!\n");
        return;
    }
}

void trocarDadosLivro(Livro* a, Livro* b) {
    Livro temp = *a;
    
    strcpy(a->Titulo, b->Titulo);
    a->Ano_lancamento = b->Ano_lancamento;
    strcpy(a->Genero_livro, b->Genero_livro);
    strcpy(a->Genero_secundario_livro, b->Genero_secundario_livro);
    strcpy(a->Editora, b->Editora);
    strcpy(a->Nome_autor, b->Nome_autor);
    
    strcpy(b->Titulo, temp.Titulo);
    b->Ano_lancamento = temp.Ano_lancamento;
    strcpy(b->Genero_livro, temp.Genero_livro);
    strcpy(b->Genero_secundario_livro, temp.Genero_secundario_livro);
    strcpy(b->Editora, temp.Editora);
    strcpy(b->Nome_autor, temp.Nome_autor);
}

Livro* encontrarMinimo(Livro *inicio, char *criterio) {
    Livro *min = inicio;
    Livro *atual = inicio->proximo;
    
    while (atual != NULL) {
        if (strcmp(criterio, "genero") == 0) {
            if (compararStrings(atual->Genero_livro, min->Genero_livro) < 0) {
                min = atual;
            }
        } 
        else if (strcmp(criterio, "autor") == 0) {
            if (compararStrings(atual->Nome_autor, min->Nome_autor) < 0) {
                min = atual;
            }
        }
        atual = atual->proximo;
    }
    return min;
}

void trocarNos(Livro **headRef, Livro *a, Livro *b) {
    if (a == b) return;

    // Guarda os vizinhos originais
    Livro *aPrev = a->anterior;
    Livro *aNext = a->proximo;
    Livro *bPrev = b->anterior;
    Livro *bNext = b->proximo;

    if (a->proximo == b) {
        a->proximo = bNext;
        b->anterior = aPrev;
        a->anterior = b;
        b->proximo = a;
        
        if (aPrev) aPrev->proximo = b;
        else *headRef = b;
        
        if (bNext) bNext->anterior = a;
    }
    else if (b->proximo == a) {
        b->proximo = aNext;
        a->anterior = bPrev;
        b->anterior = a;
        a->proximo = b;
        
        if (bPrev) bPrev->proximo = a;
        else *headRef = a;
        
        if (aNext) aNext->anterior = b;
    }
    else {
        a->anterior = bPrev;
        a->proximo = bNext;
        b->anterior = aPrev;
        b->proximo = aNext;
        
        if (aPrev) aPrev->proximo = b;
        else *headRef = b;
        
        if (aNext) aNext->anterior = b;
        
        if (bPrev) bPrev->proximo = a;
        else *headRef = a;
        
        if (bNext) bNext->anterior = a;
    }
}

void selectionSort(Livro **headRef, char *criterio) {
    if (*headRef == NULL || (*headRef)->proximo == NULL) return;
    
    Livro *atual = *headRef;
    while (atual != NULL) {
        Livro *min = encontrarMinimo(atual, criterio);
        
        if (min != atual) {
            trocarNos(headRef, atual, min);
        }
        atual = atual->proximo;
    }
}

void ordenadorSelectionSort(Livro** Livros) {
    if (*Livros == NULL || (*Livros)->proximo == NULL) {
        return; // Lista vazia ou com apenas um elemento
    }
    
    int opcao;
    printf("\nSelectionSort - Escolha o critério:\n");
    printf("1 - Ordenar por Genero\n");
    printf("2 - Ordenar por Autor\n");
    scanf("%d", &opcao);
    
    if (opcao == 1) {
        selectionSort(Livros, "genero");
        printf("Livros ordenados por Genero.\n");

    } else if (opcao == 2) {
        selectionSort(Livros, "autor");
        printf("Livros ordenados por Autor.\n");
    } else {
        printf("Opção inválida!\n");
        return;
    }
}

void imprimirLista(Livro **lista) {
    Livro *atual = *lista;
    printf("\nLista de Livros:\n");
    while(atual != NULL) {
        printf("\nTítulo: %s\n", atual->Titulo);
        printf("Ano: %d\n", atual->Ano_lancamento);
        printf("Gênero: %s\n", atual->Genero_livro);
        printf("Gênero secundario: %s\n", atual->Genero_secundario_livro);
        printf("Editora: %s\n", atual->Editora);
        printf("Autor: %s\n\n", atual->Nome_autor);
        atual = atual->proximo;
    }
}

void imprimirLista_emprestimos(emprestimos **lista) {
    emprestimos *atual = *lista;
    printf("Lista de emprestimos: \n");
    while(atual != NULL) {
        printf("\nTítulo: %s\n", atual->Titulo);
        printf("Ano: %d\n", atual->Ano_lancamento);
        printf("Gênero: %s\n", atual->Genero_livro);
        printf("Gênero secundario: %s\n", atual->Genero_secundario_livro);
        printf("Editora: %s\n", atual->Editora);
        printf("Autor: %s\n", atual->Nome_autor);
        printf("Data do Empréstimo: %s\n\n", atual->Data_emprestimo);
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
    while (atual != NULL && strcmp(atual->Titulo, titulo) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Livro com título '%s' não encontrado!\n", titulo);
        return;
    }
    if (anterior == NULL) {
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
    free(atual);
    printf("Livro '%s' removido com sucesso!\n", titulo);
}

void obter_data_atual(char *data_str) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(data_str, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void removerParaEmprestimo(Livro** lista_livros, emprestimos** lista_emprestimos, char* titulo) {
    if (*lista_livros == NULL) {
        printf("Lista de livros vazia!\n");
        return;
    }
    Livro* atual = *lista_livros;
    Livro* anterior = NULL;
    while (atual != NULL && strcmp(atual->Titulo, titulo) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Livro com título '%s' não encontrado!\n", titulo);
        return;
    }
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
    emprestimos* novo_emprestimo = (emprestimos*)malloc(sizeof(emprestimos));
    obter_data_atual(novo_emprestimo->Data_emprestimo);
    if (novo_emprestimo == NULL) {
        printf("Erro ao alocar memória para empréstimo!\n");
        return;
    }
    strcpy(novo_emprestimo->Titulo, atual->Titulo);
    novo_emprestimo->Ano_lancamento = atual->Ano_lancamento;
    strcpy(novo_emprestimo->Genero_livro, atual->Genero_livro);
    strcpy(novo_emprestimo->Genero_secundario_livro, atual->Genero_secundario_livro);
    strcpy(novo_emprestimo->Editora, atual->Editora);
    strcpy(novo_emprestimo->Nome_autor, atual->Nome_autor);
    novo_emprestimo->proximo = *lista_emprestimos;
    *lista_emprestimos = novo_emprestimo;
    free(atual);
    printf("Livro '%s' movido para empréstimos com sucesso!\n", titulo);
}

void devolverParaLivros(emprestimos** lista_emprestimos, Livro** lista_livros, char* titulo) {
    if (*lista_emprestimos == NULL) {
        printf("Lista de empréstimos vazia!\n");
        return;
    }
    emprestimos* atual = *lista_emprestimos;
    emprestimos* anterior = NULL;
    while (atual != NULL && strcmp(atual->Titulo, titulo) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Livro com título '%s' não encontrado nos empréstimos!\n", titulo);
        return;
    }
    if (anterior == NULL) {
        *lista_emprestimos = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    Livro* novo_livro = (Livro*)malloc(sizeof(Livro));
    if (novo_livro == NULL) {
        printf("Erro ao alocar memória para livro!\n");
        return;
    }
    strcpy(novo_livro->Titulo, atual->Titulo);
    novo_livro->Ano_lancamento = atual->Ano_lancamento;
    strcpy(novo_livro->Genero_livro, atual->Genero_livro);
    strcpy(novo_livro->Genero_secundario_livro, atual->Genero_secundario_livro);
    strcpy(novo_livro->Editora, atual->Editora);
    strcpy(novo_livro->Nome_autor, atual->Nome_autor);
    novo_livro->proximo = *lista_livros;
    novo_livro->anterior = NULL;
    if (*lista_livros != NULL) {
        (*lista_livros)->anterior = novo_livro;
    }
    *lista_livros = novo_livro;
    free(atual);
    printf("Livro '%s' devolvido para a lista de livros com sucesso!\n", titulo);
}

void buscaBinaria(Livro *livros) {
    if (livros == NULL) {
        printf("Nenhum livro cadastrado!\n");
        return;
    }

    int opcao;
    printf("\nBusca Binária - Escolha o critério:\n");
    printf("1 - Buscar por ano de lançamento\n");
    printf("2 - Buscar por Titulo\n");
    printf("Escolha: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        int ano;
        printf("Digite o ano de lançamento: ");
        scanf("%d", &ano);
        
        Livro *inicio = livros;
        Livro *fim = NULL;
        Livro *encontrado = NULL;
        
        while (inicio != fim) {
            Livro *lento = inicio;
            Livro *rapido = inicio->proximo;
            
            while (rapido != fim && rapido->proximo != fim) {
                lento = lento->proximo;
                rapido = rapido->proximo->proximo;
            }
            
            Livro *meio = lento;
            
            if (meio->Ano_lancamento == ano) {
                encontrado = meio;
                break;
            } else if (meio->Ano_lancamento < ano) {
                inicio = meio->proximo;
            } else {
                fim = meio;
            }
        }
        
        if (encontrado != NULL) {
            printf("\nLivros encontrados no ano %d:\n", ano);
            
            Livro *atual = encontrado;
            while (atual->anterior != NULL && atual->anterior->Ano_lancamento == ano) {
                atual = atual->anterior;
            }
            
            while (atual != NULL && atual->Ano_lancamento == ano) {
                printf("\nTítulo: %s\n", atual->Titulo);
                printf("Autor: %s\n", atual->Nome_autor);
                printf("Gênero Principal: %s\n", atual->Genero_livro);
                printf("Gênero Secundário: %s\n", atual->Genero_secundario_livro);
                printf("Editora: %s\n", atual->Editora);
                printf("Ano: %d\n", atual->Ano_lancamento);
                atual = atual->proximo;
            }
        } else {
            printf("Nenhum livro encontrado com o ano %d\n", ano);
        }
    } 
    else if (opcao == 2) {
        char titulo[100];
        printf("Digite o Titulo: ");
        scanf(" %[^\n]", titulo);
        
        Livro *inicio = livros;
        Livro *fim = NULL;
        Livro *encontrado = NULL;
        
        while (inicio != fim) {
            Livro *lento = inicio;
            Livro *rapido = inicio->proximo;
            
            while (rapido != fim && rapido->proximo != fim) {
                lento = lento->proximo;
                rapido = rapido->proximo->proximo;
            }
            
            Livro *meio = lento;
            
            int cmp = strcasecmp(meio->Titulo, titulo);
            if (cmp == 0) {
                encontrado = meio;
                break;
            } else if (cmp < 0) {
                inicio = meio->proximo;
            } else {
                fim = meio;
            }
        }
        
        if (encontrado != NULL) {
            printf("\nLivros encontrados do titulo '%s':\n", titulo);
            
            Livro *atual = encontrado;
            while (atual->anterior != NULL && strcasecmp(atual->anterior->Titulo, titulo) == 0) {
                atual = atual->anterior;
            }
            
            while (atual != NULL && strcasecmp(atual->Titulo, titulo) == 0) {
                printf("\nTítulo: %s\n", atual->Titulo);
                printf("Autor: %s\n", atual->Nome_autor);
                printf("Gênero Principal: %s\n", atual->Genero_livro);
                printf("Gênero Secundário: %s\n", atual->Genero_secundario_livro);
                printf("Editora: %s\n", atual->Editora);
                printf("Ano: %d\n", atual->Ano_lancamento);
                atual = atual->proximo;
            }
        } else {
            printf("Nenhum livro encontrado do Titulo '%s'\n", titulo);
        }
    }
    else {
        printf("Opção inválida!\n");
    }
}

char* meu_strcasestr(const char *haystack, const char *needle) {
    if (!*needle) return (char*)haystack;
    
    for (; *haystack; haystack++) {
        if (tolower((unsigned char)*haystack) == tolower((unsigned char)*needle)) {
            const char *h = haystack + 1;
            const char *n = needle + 1;
            while (*h && *n && tolower((unsigned char)*h) == tolower((unsigned char)*n)) {
                h++;
                n++;
            }
            if (!*n) return (char*)haystack;
        }
    }
    return NULL;
}

void buscaLinear(Livro *livros) {
    if (livros == NULL) {
        printf("Nenhum livro cadastrado!\n");
        return;
    }

    int opcao;
    printf("\nBusca Linear - Escolha o critério:\n");
    printf("1 - Buscar por Genero\n");
    printf("2 - Buscar por autor\n");
    scanf("%d", &opcao);

    if (opcao == 1) {
        char genero[100];
        printf("Digite o Genero do livro (ou parte dele): ");
        scanf(" %[^\n]", genero);

        printf("\nLivros encontrados com '%s' no Genero:\n", genero);
        Livro *atual = livros;
        bool encontrado = false;

        while (atual != NULL) {
            if (meu_strcasestr(atual->Genero_livro, genero) != NULL) {
                printf("\nTítulo: %s\n", atual->Titulo);
                printf("Autor: %s\n", atual->Nome_autor);
                printf("Gênero Principal: %s\n", atual->Genero_livro);
                printf("Gênero Secundário: %s\n", atual->Genero_secundario_livro);
                printf("Editora: %s\n", atual->Editora);
                printf("Ano: %d\n", atual->Ano_lancamento);
                encontrado = true;
            }
            atual = atual->proximo;
        }

        if (!encontrado) {
            printf("Nenhum livro encontrado com '%s' no Genero\n", genero);
        }
    } else if (opcao == 2) {
        char autor[100];
        printf("Digite o nome do autor (ou parte dele): ");
        scanf(" %[^\n]", autor);

        printf("\nLivros encontrados do autor '%s':\n", autor);
        Livro *atual = livros;
        bool encontrado = false;

        while (atual != NULL) {
            if (meu_strcasestr(atual->Nome_autor, autor) != NULL) {
                printf("\nTítulo: %s\n", atual->Titulo);
                printf("Autor: %s\n", atual->Nome_autor);
                printf("Gênero Principal: %s\n", atual->Genero_livro);
                printf("Gênero Secundário: %s\n", atual->Genero_secundario_livro);
                printf("Editora: %s\n", atual->Editora);
                printf("Ano: %d\n", atual->Ano_lancamento);
                encontrado = true;
            }
            atual = atual->proximo;
        }

        if (!encontrado) {
            printf("Nenhum livro encontrado do autor '%s'\n", autor);
        }
    } else {
        printf("Opção inválida!\n");
    }
}

int main() {
    Livro* topo = NULL;
    emprestimos* cabeca = NULL;
    bool loop = true;
    char chave[100];
    int opcao;

    carregarLivrosCSV(&topo);
    carregarEmprestimosCSV(&cabeca);

    while(loop) {
        printf("\n Menu:\n");
        printf("Digite: 1 / Cadastrar Livros\n");
        printf("Digite: 2 / Ordenar livros pro MergeSort\n");
        printf("Digite: 3 / Ordenar livros por SelectionSort\n");
        printf("Digite: 4 / Remover Livro\n");
        printf("Digite: 5 / Emprestar Livro\n");
        printf("Digite: 6 / Devolver livro\n");
        printf("Digite: 7 / Lista Livros\n");
        printf("Digite: 8 / Busca Binária\n");
        printf("Digite: 9 / Busca Linear\n");
        printf("Digite: 10 / Lista emprestimos\n");
        printf("Digite: 11 / Sair\n");
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
                printf("Livros ordenados");
                break;
            case 4:
                printf("qual titulo de livro vc quer retirar: ");
                scanf(" %[^\n]", chave);
                removerLivro(&topo, chave);
                break;
            case 5:
                printf("qual titulo de livro vc quer emprestar: ");
                scanf(" %[^\n]", chave);
                removerParaEmprestimo(&topo, &cabeca, chave);
                break;
            case 6:
                printf("qual titulo de livro vc quer devolver: ");
                scanf(" %[^\n]", chave);
                devolverParaLivros(&cabeca, &topo, chave);
                break;
            case 7:
                imprimirLista(&topo);
                break;
            case 8:
                 buscaBinaria(topo);;
                break;
            case 9:
                buscaLinear(topo);
                break;
            case 10:
                printf("emprestimos cadastrados: \n\n");
                imprimirLista_emprestimos(&cabeca);
                break;
            case 11:
                salvarLivrosCSV(topo);
                salvarEmprestimosCSV(cabeca);
                loop = false;
                break;
            default:
                printf("opcao invalida, tente novamente.");
                break;
        }
    }

    Livro* temp_livro = topo;
    while (temp_livro != NULL) {
        Livro* proximo = temp_livro->proximo;
        free(temp_livro);
        temp_livro = proximo;
    }

    emprestimos* temp_emp = cabeca;
    while (temp_emp != NULL) {
        emprestimos* proximo = temp_emp->proximo;
        free(temp_emp);
        temp_emp = proximo;
    }

    return 0;
}
