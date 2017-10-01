#include "Lexer.h"

#include <iostream>

int main()
{
	Dangancompiler::Lexer lexer{};
	lexer.tokenise("character(hello) { 3324; }");

	for (auto const &token : lexer.getTokens())
		std::cout << token.toString() << std::endl;

	std::cin.get();

	return 0;
}