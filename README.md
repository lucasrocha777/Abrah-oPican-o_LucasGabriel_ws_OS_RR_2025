# Busca Paralela em Arquivos com Multithreading - Sistemas Operacionais I (DCC403)

Repositório referente ao seminário da disciplina de **Sistemas Operacionais I** (DCC403) da **Universidade Federal de Roraima (UFRR)**, ministrada no semestre de 2025.

## 📌 Tema 13: Busca Paralela em Arquivos com Multithreading

###  Objetivo

Este projeto tem como objetivo desenvolver uma ferramenta eficiente para realizar buscas paralelas de palavras-chave em múltiplos arquivos de texto, utilizando multithreading em linguagem C. A solução busca otimizar o desempenho em sistemas com múltiplos núcleos, permitindo a análise de grandes quantidades de dados armazenados em arquivos .txt, com aplicações práticas em indexação de textos, análise de logs e pesquisa de documentos..

---

##  Funcionalidades

- Busca paralela de palavras-chave
- Processa até 1000 arquivos
- Exibe arquivo, linha e conteúdo
- Mede tempo de execução
- Adapta threads ao hardware

---

##  Tecnologias Utilizadas

- **C** (linguagem de programação principal)
- **Bibliotecas**:
  <pthread.h> (paralelismo com POSIX Threads)
  <windows.h> (listagem de arquivos com FindFirstFile no Windows)
  <time.h> (medição de tempo com clock_gettime)
  <string.h> (manipulação de strings para busca)
  <stdlib.h> (alocação de memória dinâmica)

---

##  Como Executar

### Pré-requisitos:

- Compilador C com suporte a pthread (ex.: MinGW no Windows).
- Sistema Windows (código usa APIs específicas como FindFirstFile).

### Passos:

Clone o repositório:
git clone https://github.com/Abrah-oPican-o_LucasGabriel_ws_OS_RR_2025.git
cd Abrah-oPican-o_LucasGabriel_ws_OS_RR_2025

Compile o projeto:
gcc -o buscador src/Threadss.c -pthread

Execute o programa:
./buscador <palavra-chave> <caminho/do/diretorio>

Exemplo:
./buscador 

---

##  Resultados

Durante a apresentação, serão exibidos os seguintes dados:

- Tempo total de execução da busca paralela.
- Exemplo de execução com múltiplos arquivos.
- Desempenho escalável com base no número de threads (adaptado ao hardware).

---

##  Testes Realizados

- Testes com diretórios contendo 10, 100 e 1000 arquivos `.txt`.
- Palavras existentes e inexistentes nos arquivos.
- Medição de desempenho com e sem paralelismo.
- Verificação da precisão das linhas encontradas.

---

##  Integrantes

- Abrahão Picanço – [@github1](https://github.com/github1)
- Lucas Rocha – [@github2](https://github.com/lucasrocha777)

---

##  Estrutura do Projeto

Aluno1Aluno2_ws_OS_RR_2025/  
├── src/  
│   └── main.cpp        # Código-fonte principal  
├── textos/             # Diretório com arquivos .txt de exemplo  
├── resultados/         # Resultados e testes com tempos  
├── slides/             # Slides da apresentação  
└── README.md           # Este arquivo

---

##  Licença

Este projeto é acadêmico e foi desenvolvido como parte das atividades da disciplina de Sistemas Operacionais I - UFRR.
