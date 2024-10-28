#include "analisador_lexico.h"
#include "util.h"
#include "analisador_sintatico.h"

using namespace std;

int main()
{
	// \Compilador_cpp\Compilador\entrada.txt
    string text = ler_arquivo("../Compilador/entrada.txt");
    text = remover_comentarios(text);

	try
	{
		escrever_saida_em_arquivo(analisador_lexico(text));

		vector<string> tokens_output = ler_tokens();

        parse_program(tokens_output);

		cout << "Compilado com sucesso!" << endl;
	}
	catch (const exception& e)
	{
		cout << "Erro durante compilação: " << e.what() << endl;
		throw;
	}
}