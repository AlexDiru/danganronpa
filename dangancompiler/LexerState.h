#pragma once

namespace Dangancompiler
{
	enum class LexerState
	{
		NONE,
		READING_ALPHABETIC,
		READING_NUMERIC,
		READING_SEPARATOR
	};
}