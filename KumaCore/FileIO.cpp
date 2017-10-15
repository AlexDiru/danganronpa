#include "FileIO.h"
#include <fstream>
#include <sstream>

std::string KumaCore::FileIO::getContent(const std::string& filename)
{
	return "../content/" + filename;
}

std::string KumaCore::FileIO::getScripts(const std::string& filename)
{
	return "../scripts/" + filename;
}

std::string KumaCore::FileIO::loadFile(const std::string& filename)
{
	std::ifstream t(filename.c_str());
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}
	