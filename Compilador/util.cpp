#include "util.h"
#include <iostream>

using namespace std;

string remover_comentarios(const string& text) 
{
    string resultado = text;

    // Remove comentários de linha (//)
    resultado = regex_replace(resultado, regex(R"(//.*?\n)"), "\n");

    // Remove comentários de bloco (/* */) - inclui novas linhas
    resultado = regex_replace(resultado, regex(R"(/[\*].*?[\*]/|/\*.*?\*[/])"), "");

    return resultado;
}

string ler_arquivo(const string& filename) 
{
    ifstream file(filename);

    if (!file.is_open()) 
    {
        throw runtime_error("Não foi possível abrir o arquivo: " + filename);
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void escrever_saida_em_arquivo(const vector<vector<string>>& tokens, const string& nome_arquivo) 
{
    ofstream arquivo(nome_arquivo);

    if (!arquivo.is_open()) 
    {
        throw runtime_error("Não foi possível abrir o arquivo para escrita.");
    }

    for (const auto& sublista : tokens) 
    {
        for (const auto& token : sublista) 
        {
            arquivo << token << " ";
        }
        arquivo << "\n";
    }
}

vector<string> read_tokens() 
{
    string input_text = ler_arquivo("saida.txt");
    vector<string> tokens;

    // Remover espaços no início e no final do texto
    input_text.erase(0, input_text.find_first_not_of(" \n\r\t"));
    input_text.erase(input_text.find_last_not_of(" \n\r\t") + 1);

    // Dividir o conteúdo em linhas
    istringstream stream(input_text);
    string line;
    while (getline(stream, line)) 
    {
        // Remover espaços no início e no final da linha
        line.erase(0, line.find_first_not_of(" \n\r\t"));
        line.erase(line.find_last_not_of(" \n\r\t") + 1);

        // Dividir a linha em tokens com base no delimitador "] ["
        istringstream line_stream(line);
        string token;
        while (getline(line_stream, token, ']')) {
            size_t pos = token.find('[');
            if (pos != string::npos) {
                token = token.substr(pos + 1);  // Remover colchetes
                size_t comma_pos = token.find(',');
                if (comma_pos != string::npos) 
                {
                    token = token.substr(0, comma_pos);  // Pegar apenas a primeira parte do token
                }

                token.erase(0, token.find_first_not_of(" \n\r\t"));
                token.erase(token.find_last_not_of(" \n\r\t") + 1);

                if (!token.empty()) 
                {
                    tokens.push_back(token);
                }
            }
        }
    }

    // Imprimir apenas para "debug"
    for (const auto& token : tokens) 
    {
        cout << token << endl;
    }

    return tokens;
}