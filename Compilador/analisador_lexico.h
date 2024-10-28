#include <regex>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <stdexcept>

#ifndef ANALISADOR_LEXICO_H
#define ANALISADOR_LEXICO_H

bool eh_identificador(const std::string& palavra);
std::vector<std::vector<std::string>> analisador_lexico(const std::string& codigo);
void executar();

#endif // !ANALISADOR_LEXICO_H