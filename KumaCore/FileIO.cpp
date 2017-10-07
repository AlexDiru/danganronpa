#include "FileIO.h"
#include <fstream>
#include <sstream>

std::string KumaCore::FileIO::loadFile(const std::string& filename)
{
	std::ifstream t(filename.c_str());
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}
	