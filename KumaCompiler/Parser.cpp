#include "Parser.h"
#include "Scene.h"

using namespace KumaCompiler;

std::unique_ptr<KumaCore::Scene> Parser::parseScene(const std::vector<Token>& tokens)
{
	if (tokens.size() < 4)
	{
		KumaCore::Log::getLog().error("Failed to parse scene, not enough tokens");
		return nullptr;
	}

	unsigned int errorCount = 0; 

	// Ensure first token is a scene
	if (!tokens[0].isKeyword("scene"))
	{
		KumaCore::Log::getLog().error("Failed to parse scene, first token is not 'scene', Line " + std::to_string(tokens[0].getLine()));
		errorCount++;
	}

	// Ensure second token is a (
	if (!tokens[1].isSeparator("("))
	{ 
		KumaCore::Log::getLog().error("Failed to parse scene, second token is not (, Line " + std::to_string(tokens[1].getLine()));
		errorCount++;
	}

	// Ensure third token is an identifier
	if (tokens[2].getTokenType() != TokenType::IDENTIFIER)
	{
		KumaCore::Log::getLog().error("Failed to parse scene, third token is not an identifier, Line " + std::to_string(tokens[2].getLine()));
		errorCount++;
	}

	// Ensure fourth token is a )
	if (!tokens[3].isSeparator(")"))
	{
		KumaCore::Log::getLog().error("Failed to parse scene, second token is not ), Line " + std::to_string(tokens[3].getLine()));
		errorCount++;
	}

	if (errorCount > 0)
		return nullptr;

	return std::make_unique<KumaCore::Scene>(tokens[2].getData());
}