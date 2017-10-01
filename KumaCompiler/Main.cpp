#include "Lexer.h"

#include <iostream>

int main()
{
	std::string source = 
		"character(KokichiOma)"
		"{"
		"	name = \"Kokichi Oma\";"
		"	baseFolder = \"KokichiOma\";"
		"	defaultEmotion = happy;"
		"	sprite(happy) = \"Kokichi_happy.png\";"
		"	sprite(angry) = \"Kokichi_angry.png\";";
		"}"
		""
		"dialog(Outside)"
		"{"
		"	KokichiOma.say(\"Well, don't worry. I'm sure you've gotten a little smarter by now, Gonta.\");"
		"	Gonta.say(\"Y - yeah...Gonta do his best to help...\", happy);"
		"}";

	KumaCompiler::Lexer lexer{};
	lexer.tokenise("character(hello) { 3324; }");

	for (auto const &token : lexer.getTokens())
		std::cout << token.toString() << std::endl;

	std::cin.get();

	return 0;
}