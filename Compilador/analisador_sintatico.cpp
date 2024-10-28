#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include "analisador_sintatico.h"

using namespace std;

vector<string> tokens;
int current_token_index = 0;

std::string get_next_token()
{
    if (current_token_index < tokens.size())
    {
        return tokens[current_token_index++];
    }
    return "";  // Retorna string vazia para indicar o fim
}

void match(const std::string& expected_token)
{
    std::string token = get_next_token();
    if (token.empty())
    {
        throw std::runtime_error("Erro de sintaxe: Fim de arquivo inesperado");
    }
    if (token != expected_token)
    {
        throw std::runtime_error("Erro de sintaxe: Esperado " + expected_token + ", encontrado " + token);
    }
}

void parse_declarations()
{
    while (current_token_index < tokens.size() && tokens[current_token_index] == "var")
    {
        match("var");
        match("id");
        match(";");
    }
}

void parse_expression()
{
    // Tratar um número inteiro, variável ou chamada para readline()
    if (tokens[current_token_index] == "id")
    {
        match("id");
    }
    else if (tokens[current_token_index] == "nu")
    {
        match("nu");  // Números inteiros
    }
    else if (tokens[current_token_index] == "fr")
    {
        match("fr");  // Números inteiros
    }
    else if (tokens[current_token_index] == "readline")
    {
        match("readline");
        match("(");
        if (tokens[current_token_index] == "fr")
        {
            match("fr");  // String de prompt opcional
        }
        match(")");
    }

    // Verificar operadores matemáticos após o valor inicial
    while (tokens[current_token_index] == "om")
    {
        match("om");  // Operador matemático
        if (tokens[current_token_index] == "id")
        {
            match("id");
        }
        else if (tokens[current_token_index] == "nu")
        {
            match("nu");
        }
        else
        {
            throw std::runtime_error("Erro de sintaxe: Valor esperado após operador matemático, encontrado " + tokens[current_token_index]);
        }
    }
}

void parse_condition()
{
    parse_expression();  // Condição antes do operador

    // Permitir operadores relacionais e lógicos após a primeira expressão
    while (tokens[current_token_index] == "ol" || tokens[current_token_index] == "cl")
    {
        if (tokens[current_token_index] == "ol")
        {
            match("ol");  // Operador relacional
        }
        else if (tokens[current_token_index] == "cl")
        {
            match("cl");  // Operador lógico
        }

        parse_expression();  // Condição depois do operador
    }
}


void parse_statements();

void parse_statement()
{
    if (tokens[current_token_index] == "echo")
    {
        match("echo");

        if (tokens[current_token_index] == "fr")
        {
            match("fr");
        }
        parse_expression();

        match(";");  // Final da instrução
    }
    else if (tokens[current_token_index] == "readline")
    {
        match("readline");
        match("(");
        if (tokens[current_token_index] == "fr")
        {
            match("fr");  // String de prompt opcional
        }
        match(")");
        match(";");
    }
    else if (tokens[current_token_index] == "if")
    {
        match("if");
        match("(");
        parse_condition();
        match(")");
        match("{");  // Início do bloco de código
        parse_statements();
        match("}");  // Fim do bloco
        // Verifica se há um "else" após o bloco "if"
        if (current_token_index < tokens.size() && tokens[current_token_index] == "else")
        {
            match("else");
            match("{");  // Início do bloco de código para else
            parse_statements();
            match("}");  // Fim do bloco
        }
    }
    else if (tokens[current_token_index] == "id")
    {
        match("id");
        match("=");
        parse_expression();
        match(";");  // Final da atribuição
    }
}

void parse_statements()
{
    while (current_token_index < tokens.size() &&
        (tokens[current_token_index] == "echo" ||
            tokens[current_token_index] == "if" ||
            tokens[current_token_index] == "id" ||
            tokens[current_token_index] == "readline"))
    {
        parse_statement();
    }
}

void parse_program(vector<string> _tokens)
{
    tokens = _tokens;
    match("<?php");  // Início do código PHP
    parse_declarations();
    parse_statements();
    match("?>");  // Fim do código PHP
}
