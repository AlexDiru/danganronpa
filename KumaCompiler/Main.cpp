#include "Lexer.h"
#include "Scene.h"
#include "Parser.h"

#include <iostream>

int main()
{
	std::string source = 
		/*"character(KokichiOma)\n"
		"{\n"
		"	name = \"Kokichi Oma\";\n"
		"	baseFolder = \"KokichiOma\";\n"
		"	defaultEmotion = happy;\n"
		"	sprite(happy) = \"Kokichi_happy.png\";\n"
		"	sprite(angry) = \"Kokichi_angry.png\";\n"
		"}\n"
		"\n"*/
		"scene(Outside)\n"
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

	KumaCompiler::Parser parser;
	auto parsedScene = parser.parseScene(lexer.getTokens());

	if (parsedScene != nullptr)
		parsedScene->show();

	KumaCore::Scene scene("ONI");
	scene.addAction(KumaCore::DialogSceneAction("Alex", "public static void main"));
	scene.addAction(KumaCore::DialogSceneAction("Jon", "Are we writing Java now?"));

	scene.show();
	std::cin.get();
	scene.show();
	std::cin.get();

	return 0;
}