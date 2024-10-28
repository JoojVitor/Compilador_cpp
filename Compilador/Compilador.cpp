#include "analisador_lexico.h"
#include "util.h"

using namespace std;

int main()
{
	// \Compilador_cpp\Compilador\entrada.txt
    string text = ler_arquivo("../Compilador/entrada.txt");
    text = remover_comentarios(text);

	try
	{
		vector<vector<string>> tokens = analisador_lexico(text);
		escrever_saida_em_arquivo(tokens);

		auto tokens_1 = read_tokens();
	}
	catch (const exception&)
	{
		cout << "Erro durante analise léxica: ";
		throw exception();
	}
}