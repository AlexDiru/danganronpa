#include "Lexer.h"
#include "Scene.h"
#include "Parser.h"
#include "ParserDatabase.h"
#include "FileIO.h"
#include "Scene.h"

#include <iostream>

//TODO Support <ID>.say(<StrLit>,<ID>);
//Where the second parameter is the ID for the sprite to use


int main()
{
	std::string source = KumaCore::FileIO::loadFile(KumaCore::FileIO::getScripts("test.txt"));

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


	KumaCompiler::Parser parser(lexer.getTokens());
	parser.parse();
	
	auto parsedScene = parser.getDatabase().lookupScene("Outside");

	if (parsedScene != nullptr)
		while (parsedScene->hasActionsLeft())
		{
			parsedScene->show();
			std::cin.get();
		}

	return 0;
}