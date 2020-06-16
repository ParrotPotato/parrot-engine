#include "logger.hh"

#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <ctime>


namespace parrot
{

	bool Log::showtime_ = false;
	bool Log::showdate_ = false;
	bool Log::showtype_ = true;

	int Log::trace(const char * formatstring, ...)
	{
		std::va_list args;
		va_start(args, formatstring);
		int ret = internal_printf(tracemsg, formatstring, args);
		va_end(args);

		return ret;
	}

	int Log::debug(const char * formatstring, ...) 
	{
		std::va_list args;
		va_start(args, formatstring);
		int ret = internal_printf(debugmsg, formatstring, args);
		va_end(args);

		return ret;
	}

	int Log::info(const char * formatstring, ...) 
	{
		std::va_list args;
		va_start(args, formatstring);
		int ret = internal_printf(infomsg, formatstring, args);
		va_end(args);

		return ret;
	}

	int Log::warn(const char * formatstring, ...) 
	{
		std::va_list args;
		va_start(args, formatstring);
		int ret = internal_printf(warnmsg, formatstring, args);
		va_end(args);

		return ret;
	}

	int Log::error(const char * formatstring, ...) 
	{
		std::va_list args;
		va_start(args, formatstring);
		int ret = internal_printf(errormsg, formatstring, args);
		va_end(args);

		return ret;
	}

	int Log::fatal(const char * formatstring, ...) 
	{
		std::va_list args;
		va_start(args, formatstring);
		int ret = internal_printf(fatalmsg, formatstring, args);
		va_end(args);

		return ret;
	}

	int Log::internal_printf(Level level, 
			const char * formatstring, 
			std::va_list args)
	{
		const char * colorstring = color_string(level);
		char buffer[50];
		int ret = 0;

		pre_formatted_string(level, buffer);

		ret += std::printf("%s%s\t", colorstring, buffer);
		ret += std::vprintf(formatstring, args);
		ret += std::printf("%s", color_string(tracemsg));

		return ret;
	}	

	inline const char * Log::type_string(Level level)
	{
		switch(level)
		{
			case tracemsg: 	return "[TRACE]";
			case debugmsg: 	return "[DEBUG]";
			case infomsg: 	return "[INFO ]";
			case warnmsg: 	return "[WARN ]";
			case errormsg: 	return "[ERROR]";
			case fatalmsg: 	return "[FATAL]";
		}
		return "";
	}

	inline const char * Log::color_string(Level level)
	{
		switch(level)
		{
			case tracemsg: 	return "\033[0m";
			case debugmsg: 	return "\033[0;34m";
			case infomsg: 	return "\033[0;32m";
			case warnmsg: 	return "\033[0;33m";
			case errormsg: 	return "\033[0;31m";
			case fatalmsg: 	return "\033[1;31m";
		}

		return "\033[0m";
	}

	inline void Log::get_time_embedded_string(char buffer[30])
	{
		std::time_t now;
		std::time(&now);

		int hours, minutes, seconds;
		int day, month, year;

		tm * local = std::localtime(&now);

		hours = local->tm_hour; 
		minutes = local->tm_min; 
		seconds = local->tm_sec; 

		day = local->tm_mday;
		month = local->tm_mon + 1;
		year = local->tm_year + 1900;

		if(showtime_ && showdate_)
			sprintf(buffer, "[%d/%d/%d][%d:%d:%d] ", 
					day, month, year, hours, minutes, seconds);
		else if(showdate_)
			sprintf(buffer, "[%d/%d/%d] ", day, month, year);
		else if(showtime_)
			sprintf(buffer, "[%d:%d:%d] ", hours, minutes, seconds);

		buffer[0] = '\0';
	}

	inline void Log::pre_formatted_string(Level level, 
			char buffer[50])
	{
		char datetimebuffer[24];
		get_time_embedded_string(datetimebuffer);

		if(showtype_)
			std::sprintf(buffer, "%s%s", type_string(level), 
																	 datetimebuffer);
		else 
			std::sprintf(buffer, "%s", datetimebuffer);
	}
}



