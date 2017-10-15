#pragma once

#include <string>

namespace KumaCore
{
	class FileIO
	{
	public:
		static std::string getContent(const std::string& filename);

		static std::string getScripts(const std::string& filename);

		static std::string loadFile(const std::string& filename);
	};
}