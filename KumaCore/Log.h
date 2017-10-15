#pragma once

#include <string>
#include <sstream>
#include <iostream>

#define NOMINMAX 
#define STRICT 
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>

namespace KumaCore
{
	class Log
	{
		template <typename T>
		void log(std::ostringstream& o, T t)
		{
			o << t; 
		}

		template<typename T, typename... Args>
		void log(std::ostringstream& o, T t, Args... args)
		{
			log(o, t);
			log(o, args...);
		}

		template<typename... Args>
		void log(int level, Args... args)
		{
			std::ostringstream oss;
			log(oss, args...);
			if (level == 0)
				OutputDebugString((oss.str() + "\n").c_str());
			if (level == 1)
				OutputDebugString((oss.str() + "\n").c_str());
		}

	public:
		static Log &getLog() 
		{
			static Log log{};
			return log;
		}

		template<typename... Args>
		void error(Args... args)
		{
			log(1, args...);
		}
	};
}

// Log macros to reduce verbosity
template<typename... Args>
void LOG_ERROR(Args... args)
{
	KumaCore::Log().error(std::forward<Args>(args)...);
}