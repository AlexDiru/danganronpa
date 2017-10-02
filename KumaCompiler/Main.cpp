#include "Lexer.h"

#include <iostream>

int main()
{
	std::string source = 
		"character(KokichiOma)\n"
		"{\n"
		"	name = \"Kokichi Oma\";\n"
		"	baseFolder = \"KokichiOma\";\n"
		"	defaultEmotion = happy;\n"
		"	sprite(happy) = \"Kokichi_happy.png\";\n"
		"	sprite(angry) = \"Kokichi_angry.png\";\n"
		"}\n"
		"\n"
		"dialog(Outside)\n"
		"{\n"
		"	KokichiOma.say(\"Well, don't worry. I'm sure you've gotten a little smarter by now, Gonta.\");\n"
		"	Gonta.say(\"Y - yeah...Gonta do his best to help...\", happy);\n"
		"}\n";

	KumaCompiler::Lexer lexer{};
	KumaCompiler::LexerFlags flags{};
	flags.ignoreWhitespaceTokens = true;

	lexer.setLexerFlags(flags);

	lexer.tokenise(source);

	std::cout << "Source: " << std::endl;
	std::cout << source.c_str() << std::endl;
	std::cout << std::endl;

	for (auto const &token : lexer.getTokens())
		std::cout << token.toString() << std::endl;

	std::cin.get();

	return 0;
}