#pragma once

#include <string_view>

namespace KumaCore
{
	class FileIO
	{
		static constexpr std::string_view contentDirectory{ "content", 7 };

		std::string getContent(const std::string& filename)
		{
			return "../Content/" + filename;
		}
	};
}