#include "util.h"
#include <iostream>

using namespace std;

// Fun��o para remover coment�rios do texto
std::string remover_comentarios(const std::string& text) {
    std::string resultado = text;

    // Remove coment�rios de linha (//)
    resultado = std::regex_replace(resultado, std::regex(R"(//.*?\n)"), "\n");

    // Remove coment�rios de bloco (/* */) - inclui novas linhas
    resultado = std::regex_replace(resultado, std::regex(R"(/[\*].*?[\*]/|/\*.*?\*[/])"), "");

    return resultado;
}

// Fun��o para ler o conte�do de um arquivo
std::string ler_arquivo(const std::string& filename) {
    std::ifstream file(filename); // Abrir o arquivo em modo leitura

    // Verificar se o arquivo foi aberto com sucesso
    if (!file.is_open()) {
        throw std::runtime_error("N�o foi poss�vel abrir o arquivo: " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); // Ler o conte�do do arquivo para um buffer
    return buffer.str(); // Retornar o conte�do como uma string
}

// Fun��o para escrever a sa�da em um arquivo
void escrever_saida_em_arquivo(const std::vector<std::vector<std::string>>& tokens, const std::string& nome_arquivo = "saida.txt") {
    // Abrir o arquivo em modo de escrita
    std::ofstream arquivo(nome_arquivo);

    // Verificar se o arquivo foi aberto com sucesso
    if (!arquivo.is_open()) {
        throw std::runtime_error("N�o foi poss�vel abrir o arquivo para escrita.");
    }

    // Converter lista de listas para uma �nica string com cada sublista em uma nova linha
    for (const auto& sublista : tokens) {
        for (const auto& token : sublista) {
            arquivo << token << " "; // Escrever token seguido de um espa�o
        }
        arquivo << "\n"; // Nova linha ap�s cada sublista
    }

    // O arquivo ser� fechado automaticamente ao sair do escopo
}