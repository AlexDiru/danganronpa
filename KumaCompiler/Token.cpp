#include "Token.h"

using namespace KumaCompiler;

Token::Token(TokenType tokenType, const std::string& data, TokenDataType tokenDataType, unsigned int line) :
	tokenType(tokenType), data(data), tokenDataType(tokenDataType), line(line) {}

std::string Token::toString() const
{
	std::string out = "[" + std::to_string(line) + "] ";
	out += tokenTypeToString();

	if (data != " ")
		out += ": " + data;
	else
		out += ": [space]";

	if (tokenType == TokenType::LITERAL)
	{
		out += " (";
		if (tokenDataType == TokenDataType::FLOAT)
			out += "float";
		else if (tokenDataType == TokenDataType::INT)
			out += "int";
		else if (tokenDataType == TokenDataType::STRING)
			out += "string";
		else
			out += "<UNKNOWN_TOKEN_DATA_TYPE>";
		out += ")";
	}

	return out;
}

std::string KumaCompiler::Token::tokenTypeToString() const
{
	if (tokenType == TokenType::COMMENT)
		return "Comment";
	else if (tokenType == TokenType::IDENTIFIER)
		return "Identifier";
	else if (tokenType == TokenType::KEYWORD)
		return "Keyword";
	else if (tokenType == TokenType::LITERAL)
		return "Literal";
	else if (tokenType == TokenType::OPERATOR)
		return "Operator";
	else if (tokenType == TokenType::SEPARATOR)
		return "Separator";
	return "<UNKNOWN_TOKEN_TYPE>";
}