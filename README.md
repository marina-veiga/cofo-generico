# Trabalho de Implementação 01 - TAD Coleção Genérica

## Descrição do Projeto
Este projeto foi desenvolvido em linguagem C com o objetivo de criar um Tipo Abstrato de Dado (TAD) Genérico para armazenar e gerenciar coleções de dados. Para mostrar como a estrutura funciona na prática, foi desenvolvida uma aplicação simples de gerenciamento de Álbuns Musicais. Nela, o usuário pode cadastrar novos álbuns, buscar informações, remover registros e listar todos os álbuns armazenados, tudo por meio de um menu interativo no terminal.

Cada álbum possui as seguintes informações:
*   `char nome[100]`: Nome do álbum.
*   `int anoLancamento`: Ano de lançamento do álbum.
*   `float faturamento`: Valor arrecadado pelo álbum.

## 1. Ambiente de Desenvolvimento
*   **Sistemas Operacionais:** Windows / Linux Ubuntu.
*   **Compilador:** MinGW no Windows.

## 2. Compilação e Execução

Para compilar o código fonte e gerar o executável, utilize os comandos abaixo conforme o seu sistema:

**Ambiente Windows:**
```bash
gcc -g src/main.c src/colecao.c -o programa.exe
.\programa.exe
```
**Ambiente Linux:**
```bash
gcc -g src/main.c src/colecao.c -o programa
./programa
```

## 3. Funcionalidades Implementadas
- Inicializar Coleção: Cria a coleção e define a quantidade máxima de elementos que poderão ser armazenados.

- Inserir Registro: Permite adicionar um novo álbum informando nome, ano de lançamento e faturamento.

- Remover Registro: Remove um álbum da coleção através da busca pelo nome.

- Consultar Registro: Busca um álbum cadastrado e mostra suas informações.

- Listar Coleção: Exibe todos os álbuns armazenados na coleção.

- Limpar Coleção: Remove todos os elementos da coleção e libera a memória utilizada.

- Finalizar Estrutura: Encerra completamente a estrutura de dados (a coleção deve estar vazia).

- Sair: Fecha o programa.

# Identificação
Disciplina: Estrutura de Dados I
Aluna: Marina Nascimento Veiga
