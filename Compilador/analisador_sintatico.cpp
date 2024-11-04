#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include "analisador_sintatico.h"

using namespace std;

vector<string> tokens;
int current_token_index = 0;

string get_next_token()
{
    if (current_token_index < tokens.size())
    {
        return tokens[current_token_index++];
    }
    return "";  // Retorna string vazia para indicar o fim
}

void match(const string& expected_token)
{
    string token = get_next_token();
    if (token.empty())
    {
        throw runtime_error("Erro de sintaxe: Fim de arquivo inesperado");
    }
    if (token != expected_token)
    {
        throw runtime_error("Erro de sintaxe: Esperado " + expected_token + ", encontrado " + token);
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
    if (tokens[current_token_index] == "id")
    {
        match("id");
    }
    else if (tokens[current_token_index] == "nu")
    {
        match("nu");
    }
    else if (tokens[current_token_index] == "fr")
    {
        match("fr");
    }
    else if (tokens[current_token_index] == "readline")
    {
        match("readline");
        match("(");
        if (tokens[current_token_index] == "fr")
        {
            match("fr");
        }
        match(")");
    }

    while (tokens[current_token_index] == "om")
    {
        match("om");
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
            throw runtime_error("Erro de sintaxe: Valor esperado após operador matemático, encontrado " + tokens[current_token_index]);
        }
    }
}

void parse_condition()
{
    parse_expression();

    while (tokens[current_token_index] == "ol" || tokens[current_token_index] == "cl")
    {
        if (tokens[current_token_index] == "ol")
        {
            match("ol"); 
        }
        else if (tokens[current_token_index] == "cl")
        {
            match("cl");
        }

        parse_expression();
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

        match(";");
    }
    else if (tokens[current_token_index] == "readline")
    {
        match("readline");
        match("(");
        if (tokens[current_token_index] == "fr")
        {
            match("fr");
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
        match("{");
        parse_statements();
        match("}");

        if (current_token_index < tokens.size() && tokens[current_token_index] == "else")
        {
            match("else");
            match("{");
            parse_statements();
            match("}");
        }
    }
    else if (tokens[current_token_index] == "id")
    {
        match("id");
        match("=");
        parse_expression();
        match(";");
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
    match("<?php");
    parse_declarations();
    parse_statements();
    match("?>");
}
