#pragma once

#include <string>
#include <sstream>
#include <iostream>

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
				std::cout << oss.str() << std::endl;
			if (level == 1)
				std::cerr << oss.str() << std::endl;
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