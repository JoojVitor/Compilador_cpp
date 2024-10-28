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
    // Tratar um n�mero inteiro, vari�vel ou chamada para readline()
    if (tokens[current_token_index] == "id")
    {
        match("id");
    }
    else if (tokens[current_token_index] == "nu")
    {
        match("nu");  // N�meros inteiros
    }
    else if (tokens[current_token_index] == "fr")
    {
        match("fr");  // N�meros inteiros
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

    // Verificar operadores matem�ticos ap�s o valor inicial
    while (tokens[current_token_index] == "om")
    {
        match("om");  // Operador matem�tico
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
            throw std::runtime_error("Erro de sintaxe: Valor esperado ap�s operador matem�tico, encontrado " + tokens[current_token_index]);
        }
    }
}

void parse_condition()
{
    parse_expression();  // Condi��o antes do operador

    // Permitir operadores relacionais e l�gicos ap�s a primeira express�o
    while (tokens[current_token_index] == "ol" || tokens[current_token_index] == "cl")
    {
        if (tokens[current_token_index] == "ol")
        {
            match("ol");  // Operador relacional
        }
        else if (tokens[current_token_index] == "cl")
        {
            match("cl");  // Operador l�gico
        }

        parse_expression();  // Condi��o depois do operador
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

        match(";");  // Final da instru��o
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
        match("{");  // In�cio do bloco de c�digo
        parse_statements();
        match("}");  // Fim do bloco
        // Verifica se h� um "else" ap�s o bloco "if"
        if (current_token_index < tokens.size() && tokens[current_token_index] == "else")
        {
            match("else");
            match("{");  // In�cio do bloco de c�digo para else
            parse_statements();
            match("}");  // Fim do bloco
        }
    }
    else if (tokens[current_token_index] == "id")
    {
        match("id");
        match("=");
        parse_expression();
        match(";");  // Final da atribui��o
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
    match("<?php");  // In�cio do c�digo PHP
    parse_declarations();
    parse_statements();
    match("?>");  // Fim do c�digo PHP
}
