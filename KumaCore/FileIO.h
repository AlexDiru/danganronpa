#pragma once

#include <string_view>

namespace KumaCore
{
	class FileIO
	{
	public:
		static std::string getContent(const std::string& filename)
		{
			return "../content/" + filename;
		}

		static std::string getScripts(const std::string& filename)
		{
			return "../scripts/" + filename;
		}

		static std::string loadFile(const std::string& filename);
	};
}