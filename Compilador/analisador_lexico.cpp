#include "analisador_lexico.h"
#include "util.h"
#include <iostream>

using namespace std;

bool eh_identificador(const string& palavra) {
    regex padrao_identificador(R"(^\$[a-zA-Z_]\w*$)");
    return regex_match(palavra, padrao_identificador);
}

vector<vector<string>> analisador_lexico(const string& codigo) {
    vector<vector<string>> tokens;
    unordered_map<string, int> identificadores;

    // Regex para identificar tokens
    regex padrao_tokens(R"(<\?php|\?>|\$[a-zA-Z_]\w*|=|echo|if|else|\(|\)|;)");

    size_t linha_numero = 0;
    string linha;
    istringstream stream(codigo);

    while (getline(stream, linha)) {
        linha_numero++;
        vector<string> linha_tokens;

        for (auto it = sregex_iterator(linha.begin(), linha.end(), padrao_tokens);
            it != sregex_iterator(); ++it) {
            string palavra = it->str();

            // Verificar a categoria da palavra
            if (palavra == "<?php" || palavra == "?>" || palavra == "$" || palavra == "=" ||
                palavra == "echo" || palavra == "if" || palavra == "else" || palavra == "(" ||
                palavra == ")" || palavra == ":" || palavra == ";") {
                linha_tokens.push_back("[" + palavra + ", ]");
            }
            else if (palavra.front() == '"' && palavra.back() == '"') {
                palavra = palavra.substr(1, palavra.size() - 2);
                linha_tokens.push_back("[fr, " + palavra + "]");
            }
            else if (all_of(palavra.begin(), palavra.end(), ::isdigit)) {
                linha_tokens.push_back("[nu, " + palavra + "]");
            }
            else if (palavra == "<" || palavra == ">" || palavra == "<=" || palavra == ">=" || palavra == "==") {
                linha_tokens.push_back("[ol, " + palavra + "]");
            }
            else if (palavra == "+" || palavra == "-" || palavra == "*" || palavra == "/") {
                linha_tokens.push_back("[om, " + palavra + "]");
            }
            else if (palavra == "&&" || palavra == "||" || palavra == "!") {
                linha_tokens.push_back("[cl, " + palavra + "]");
            }
            else if (eh_identificador(palavra)) {
                int numero_identificador;
                if (identificadores.count(palavra)) {
                    numero_identificador = identificadores[palavra];
                }
                else {
                    numero_identificador = identificadores.size() + 1;
                    identificadores[palavra] = numero_identificador;
                }
                linha_tokens.push_back("[id, " + to_string(numero_identificador) + "]");
            }
            else {
                throw invalid_argument("Token não reconhecido na linha " + to_string(linha_numero) + ": " + palavra);
            }
        }

        tokens.push_back(linha_tokens);
    }

    return tokens;
}

void executar()
{
    try {
        string text = ler_arquivo("entrada.txt");

        text = remover_comentarios(text);

        auto tokens = analisador_lexico(text);

        escrever_saida_em_arquivo(tokens);
    }
    catch (const exception& e) {
        cerr << "Erro durante a análise léxica: " << e.what() << endl;
    }
}