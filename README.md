# Compilador - Documentação

As fases deste projeto são separadas em três etapas:
- Varredura do arquivo;
- Analisador léxico;
- Analisador sintático (Parser).

## Instruções para uso

1. Escrever o código (consultar os exemplos para verificar os tokens que possuem suporte) no arquivo "entrada.txt" que se encontra na pasta `/Compilador_cpp/Compilador/entrada.txt`;
2. Executar e verificar o console;
3. É gerado um arquivo de saída na mesma pasta do arquivo de entrada, este arquivo contém a classificação de cada token/valor que foi identificado no código.

## Descrição breve sobre a sintaxe suportada

Baseado no PHP, é uma implementação bem simplificada dos símbolos dessa linguagem. Está implementada algumas estruturas básicas, excluindo laços de repetição e funções. Segue alguns recursos suportados:

- Estruturas condicionais: if, else;
- Alguns operadores matemáticos: +, -, *, /, %;
- Alguns operadores lógicos/relacionais: <, >, <=, =>, ==, !==, &&, ||, !;
- Entrada/Saída de dados: echo e readline();
- Dados: strings e numeros;

  OBS.: Verificar exemplos na pasta "Examples".

Versão desenvolvida anteriormente em Python disponível no meu Google Collab:
https://colab.research.google.com/drive/1rAFwa2rf0bBSPaRP8Zn_psW5D3H6gmPX#scrollTo=sqflnZLbZFxU

By João Vitor Couto
