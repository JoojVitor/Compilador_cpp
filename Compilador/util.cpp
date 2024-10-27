#include "util.h"
#include <iostream>

using namespace std;

// Função para remover comentários do texto
std::string remover_comentarios(const std::string& text) {
    std::string resultado = text;

    // Remove comentários de linha (//)
    resultado = std::regex_replace(resultado, std::regex(R"(//.*?\n)"), "\n");

    // Remove comentários de bloco (/* */) - inclui novas linhas
    resultado = std::regex_replace(resultado, std::regex(R"(/[\*].*?[\*]/|/\*.*?\*[/])"), "");

    return resultado;
}

// Função para ler o conteúdo de um arquivo
std::string ler_arquivo(const std::string& filename) {
    std::ifstream file(filename); // Abrir o arquivo em modo leitura

    // Verificar se o arquivo foi aberto com sucesso
    if (!file.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo: " + filename);
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); // Ler o conteúdo do arquivo para um buffer
    return buffer.str(); // Retornar o conteúdo como uma string
}

// Função para escrever a saída em um arquivo
void escrever_saida_em_arquivo(const std::vector<std::vector<std::string>>& tokens, const std::string& nome_arquivo = "saida.txt") {
    // Abrir o arquivo em modo de escrita
    std::ofstream arquivo(nome_arquivo);

    // Verificar se o arquivo foi aberto com sucesso
    if (!arquivo.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo para escrita.");
    }

    // Converter lista de listas para uma única string com cada sublista em uma nova linha
    for (const auto& sublista : tokens) {
        for (const auto& token : sublista) {
            arquivo << token << " "; // Escrever token seguido de um espaço
        }
        arquivo << "\n"; // Nova linha após cada sublista
    }

    // O arquivo será fechado automaticamente ao sair do escopo
}