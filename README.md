# APS_Estrutura-de-Dados1

# G.D.B Gerenciamento de bibliotecas

Este projeto de engenharia de software visa resolver problemas de organização em bibliotecas e livrarias utilizando estruturas de dados como listas encadeadas e algoritmos de busca e ordenação, implementados em linguagem C para gerenciar acervos e empréstimos de livros de forma eficiente. O sistema armazenará informações como títulos, autores, generos, editoras, anos de publicação e datas de empréstimo, facilitando o controle e a localização dos itens.

## Indice
- [Funcionalidades](
- Adicionar livros, listas livros, remover livros, ordenadores: Mergesort e selectionsort(somente da lista de livros), Buscadores: binario e linear(somente da lista de livros), emprestar livro, lista de emprestimos, devolver livro, Salvar/carregar livros em CSV e Salvar/carregar emprestimos em CSV).

## Pré-requisitos (Windows 10/11 - C)

- **Compilador**: MinGW-w64 (via Visual Studio Code).
- **CMake**: Versão 3.15+ (para builds automatizados).
- **Dependências**:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>.

### Configuração Inicial
1. Instale o MinGW-w64 e adicione `C:\msys64\ucrt64\bin` ao `PATH`.
2. Guia de instalação https://code.visualstudio.com/docs/cpp/config-mingw#_installing-the-mingww64-toolchain
3. Clone o repositório:
   ```bash
   [git clone https://github.com/PauloOsvaldo2/APS_Estrutura-de-Dados1.git]
   cd APS_Estrutura-de-Dados1

## Funcionalidades

- **Adicionar_Livro**: Adiciona um livro em uma lista duplamente encadeada com o uso de malloc para a alocação dinamica dos dados.
- **Remover_Livro**: Faz uma remoção de um livro por seu Titulo e depois de remover faz um Free para liberar espaço na memoria.
- **Emprestar_livro**: Ele pega um livro pelo Titulo e faz quase uma Remoção a diferença é que de fez de dar um Free ele transfere esse Dado para a lista de emprestimos.
- **Devolver_livro**: ele faz uma "Remoção" da lista de emprestimos e devolve ele para a lista de Livros.
- **Ordenador MergeSort**:Este algoritmo adapta o MergeSort clássico para listas duplamente encadeadas, dividindo recursivamente a lista até sublistas unitárias e depois fundindo os nós em ordem, reajustando os ponteiros anterior e proximo durante a fusão. Mantém a complexidade O(n log n) sem necessidade de acesso aleatório, sendo ideal para estruturas encadeadas. Preserva a estabilidade dos elementos e opera apenas com reorganização de ponteiros, sem alocação adicional de nós. Requer cuidado especial na manipulação bidirecional durante a fusão, mas oferece desempenho ótimo para ordenação em listas encadeadas.
- **Ordenador SelectionSort**: Este algoritmo percorre a lista repetidamente para encontrar o menor elemento restante e o posiciona no início da sublista não ordenada, ajustando os ponteiros anterior e proximo conforme necessário. Mantém complexidade O(n²) em todos os casos, sendo ineficiente para grandes conjuntos de dados, mas simples de implementar. Não exige espaço adicional de memória, realizando todas as operações através da reorganização dos ponteiros existentes. Apesar de instável (pode alterar a ordem relativa de elementos iguais), é prático para listas pequenas ou quando a simplicidade é prioritária. Sua principal vantagem é o baixo número de trocas (O(n)), sendo útil em cenários onde operações de escrita são custosas.
- **Busca_binaria**:A busca binária divide repetidamente uma lista já ordenada ao meio, comparando o elemento central com o alvo e descartando metade da lista a cada iteração. Com complexidade O(log n), é extremamente eficiente para grandes conjuntos de dados, mas exige acesso aleatório (inviável em listas encadeadas puras). Requer prévia ordenação e opera sobre estruturas de tamanho fixo, como arrays.
- **Busca_linear**: Percorre cada elemento sequencialmente (usando proximo ou anterior) até encontrar o alvo ou chegar ao fim. Complexidade O(n) no pior caso, funcionando em listas ordenadas ou não. Única opção viável para listas encadeadas simples, sem acesso aleatório. Versátil, porém ineficiente para grandes volumes de dados. Ideal para buscas pontuais em listas pequenas ou desordenadas.
- ## Contato

Paulo Osvaldo Goçalves Maia - paulogmaia4@gmail.com
Emanoel da Silva Walek - emanoelwalek@gmail.com

Link do Projeto: https://github.com/PauloOsvaldo2/APS_Estrutura-de-Dados1.git
