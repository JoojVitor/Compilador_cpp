#include <regex>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <fstream>

using namespace std;

// Função para escrever a saída em um arquivo
void escrever_saida_em_arquivo(const std::vector<std::vector<std::string>>& tokens, const std::string& nome_arquivo = "saida.txt") {
    // Abrir o arquivo em modo de escrita
    std::ofstream arquivo(nome_arquivo);

    // Verificar se o arquivo foi aberto com sucesso
    if (!arquivo.is_open()) {
        throw std::runtime_error("Não foi possível abrir o arquivo para escrita.");
    }

    // Converter a lista de listas para uma única string, com cada sublista em uma nova linha
    for (const auto& sublista : tokens) {
        for (const auto& token : sublista) {
            arquivo << token << " ";
        }
        arquivo << "\n"; // Nova linha para cada sublista
    }

    // Fechar o arquivo (opcional aqui, pois o destrutor de ofstream fechará o arquivo automaticamente)
    arquivo.close();
}


int main()
{
    regex padrao_tokens(R"("(?:\\\"|[^"])*?"|\w+|[^\w\s"])");
}