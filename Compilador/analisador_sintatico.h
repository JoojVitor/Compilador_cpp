#ifndef ANALISADOR_SINTATICO_H
#define ANALISADOR_SINTATICO_H

#include <vector>
#include <string>
#include <stdexcept>

extern std::vector<std::string> tokens;
extern int current_token_index;

std::string get_next_token();
void match(const std::string& expected_token);
void parse_declarations();
void parse_expression();
void parse_condition();
void parse_statements();
void parse_statement();
void parse_program(std::vector<std::string> _tokens);

#endif // ANALISADOR_SINTATICO_H