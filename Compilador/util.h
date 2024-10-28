#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <stdexcept>

std::string remover_comentarios(const std::string& text);
std::string ler_arquivo(const std::string& filename);
void escrever_saida_em_arquivo(const std::vector<std::vector<std::string>>& tokens, const std::string& nome_arquivo = "saida.txt");
std::vector<std::string> read_tokens();