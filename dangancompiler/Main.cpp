#include "Lexer.h"

#include <iostream>

int main()
{
	Dangancompiler::Lexer lexer{};
	lexer.tokenise("character332hello111");

	for (auto const &token : lexer.getTokens())
		std::cout << token.toString() << std::endl;

	std::cin.get();

	return 0;
}