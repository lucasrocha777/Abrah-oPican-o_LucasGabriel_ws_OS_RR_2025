# Busca Paralela em Arquivos com Multithreading - Sistemas Operacionais I (DCC403)

Repositório referente ao seminário da disciplina de **Sistemas Operacionais I** (DCC403) da **Universidade Federal de Roraima (UFRR)**, ministrada no semestre de 2025.

## 📌 Tema 13: Busca Paralela em Arquivos com Multithreading

###  Objetivo

Desenvolver uma aplicação em **Rust** que realiza a **busca por uma ou mais palavras-chave em múltiplos arquivos de texto** (como arquivos `.txt` localizados em um diretório). O programa utiliza **multithreading** para executar as buscas de forma paralela, melhorando o desempenho da aplicação.

---

##  Funcionalidades

- Busca de uma ou mais palavras-chave.
- Suporte a múltiplos arquivos `.txt` em um diretório.
- Execução paralela utilizando múltiplas threads.
- Exibição das seguintes informações:
  - Nome do arquivo onde a palavra foi encontrada.
  - Linha(s) onde a palavra aparece.
  - Tempo total de execução da busca.

---

##  Tecnologias Utilizadas

- **Rust** (linguagem de programação principal)
- **Crates**:
  - `rayon` (paralelismo)
  - `walkdir` (varredura de diretórios)
  - `regex` (busca por padrões)
  - `chrono` (medição de tempo)

---

##  Como Executar

### Pré-requisitos:

- Ter o [Rust](https://www.rust-lang.org/tools/install) instalado.

### Passos:

Clone o repositório:
git clone https://github.com/Aluno1Aluno2_ws_OS_RR_2025.git  
cd Abrah-oPican-o_LucasGabriel_ws_OS_RR_2025

Compile e execute:
cargo run -- <palavra-chave> <caminho/do/diretorio>

Exemplo:
cargo run -- "sistemas" ./textos/

---

##  Resultados

Durante a apresentação, serão exibidos os seguintes dados:

- Comparativo de tempo entre execução sequencial e paralela.
- Exemplo de execução com múltiplos arquivos.
- Desempenho escalável com base na quantidade de threads e arquivos.

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
│   └── main.rs         # Código-fonte principal  
├── textos/             # Diretório com arquivos .txt de exemplo  
├── resultados/         # Resultados e testes com tempos  
├── slides/             # Slides da apresentação  
└── README.md           # Este arquivo

---

##  Licença

Este projeto é acadêmico e foi desenvolvido como parte das atividades da disciplina de Sistemas Operacionais I - UFRR.
