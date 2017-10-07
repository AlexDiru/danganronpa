#include "Parser.h"
#include "Scene.h"
#include "Character.h"

using namespace KumaCompiler;

bool Parser::parseCharacter()
{
	if (tokens.size() < 4)
	{
		KumaCore::Log::getLog().error("Failed to parse character, not enough tokens");
		return false;
	}

	if (!areNextTokensTheStartOfACharacter())
	{
		KumaCore::Log::getLog().error("Failed to parse character");
		return false;
	}

	// Now we will use a while loop until we reach the final } marking the end of the character
	auto character = std::make_unique<KumaCore::Character>(tokens[currentTokenIndex + 2].getData());
	auto charStartToken = currentTokenIndex;
	currentTokenIndex += 4; //Skip to first {
	unsigned int curlyDepth = 0;
	do
	{
		if (currentTokenIndex >= tokens.size())
			KumaCore::Log::getLog().error("Mismatched {, } not found before end of file in character starting at line ", tokens[charStartToken].getLine());

		if (currentToken().isSeparator("{"))
			curlyDepth++;
		else if (currentToken().isSeparator("}"))
			curlyDepth--;
		else if (currentToken().isIdentifier())
		{
			std::string propertyName = tokens[currentTokenIndex].getData();

			currentTokenIndex++;
			if (!currentToken().isOperator("="))
				errorExpected("=");

			currentTokenIndex++;
			if (currentToken().isStringLiteral())
			{
				if (!character->addProperty(propertyName, currentToken().getData()))
					KumaCore::Log::getLog().error("Failed to add property to character. PropertyName: ", propertyName, " Value: ", currentToken().getData());
			}

			currentTokenIndex++;
			if (!currentToken().isSeparator(";"))
				errorExpected(";");

		}
		currentTokenIndex++;
	} while (curlyDepth != 0);

	parserDatabase.addCharacter(character);

	return true;
}

std::unique_ptr<KumaCore::Scene> Parser::parseScene()
{
	if (tokens.size() < 4)
	{
		KumaCore::Log::getLog().error("Failed to parse scene, not enough tokens");
		return nullptr;
	}

	if (!areNextTokensTheStartOfAScene())
	{
		KumaCore::Log::getLog().error("Failed to parse scene");
		return nullptr;
	}

	// Now we will use a while loop until we reach the final } marking the end of the scene
	auto scene = std::make_unique<KumaCore::Scene>(tokens[currentTokenIndex + 2].getData());
	auto sceneStartToken = currentTokenIndex;
	currentTokenIndex += 4; //Skip to first {
	unsigned int curlyDepth = 0;
	do 
	{
		if (currentTokenIndex >= tokens.size())
			KumaCore::Log::getLog().error("Mismatched {, } not found before end of file in scene starting at line ", tokens[sceneStartToken].getLine());
			
		if (currentToken().isSeparator("{"))
			curlyDepth++;
		else if (currentToken().isSeparator("}"))
			curlyDepth--;
		else if (currentToken().isIdentifier())
		{
			//This eventually needs to do a lookup to a character DB
			std::string identifierName = tokens[currentTokenIndex].getData();
			std::string characterName = "";
			auto character = parserDatabase.lookupCharacter(identifierName);

			if (character == nullptr)
			{
				KumaCore::Log::getLog().error("Character ", identifierName, " is undeclared. Please define this character before using in a scene. Defaulting to identifierName as name");
				characterName = identifierName;
			}
			else
			{
				characterName = character->getDisplayName();
			}

			currentTokenIndex++;
			if (!currentToken().isSeparator("."))
				errorExpected(".");

			currentTokenIndex++;
			if (tokens[currentTokenIndex].isIdentifier())
			{
				//Create an action for this character based on this identifier
				if (tokens[currentTokenIndex].getData() == "say")
				{
					currentTokenIndex++;
					if (!currentToken().isSeparator("("))
						errorExpected("(");

					currentTokenIndex++;
					scene->addAction(KumaCore::DialogSceneAction(characterName, tokens[currentTokenIndex].getData()));

					currentTokenIndex++;
					if (!currentToken().isSeparator(")"))
						errorExpected(")");

					currentTokenIndex++;
					if (!currentToken().isSeparator(";"))
						errorExpected(";");
				}
			}
		}
		currentTokenIndex++;
	} while (curlyDepth != 0);

	return scene;
}

bool KumaCompiler::Parser::areNextTokensTheStartOfAScene() const
{
	if (tokens.size() - currentTokenIndex < 4)
		return false;
	if (!tokens[currentTokenIndex].isKeyword("scene"))
		return false;
	if (!tokens[currentTokenIndex + 1].isSeparator("("))
		return false;
	if (tokens[currentTokenIndex + 2].getTokenType() != TokenType::IDENTIFIER)
		return false;
	if (!tokens[currentTokenIndex + 3].isSeparator(")"))
		return false;
	return true;
}

bool KumaCompiler::Parser::areNextTokensTheStartOfACharacter() const
{
	if (tokens.size() - currentTokenIndex < 4)
		return false;
	if (!tokens[currentTokenIndex].isKeyword("character"))
		return false;
	if (!tokens[currentTokenIndex + 1].isSeparator("("))
		return false;
	if (tokens[currentTokenIndex + 2].getTokenType() != TokenType::IDENTIFIER)
		return false;
	if (!tokens[currentTokenIndex + 3].isSeparator(")"))
		return false;
	return true;
}
