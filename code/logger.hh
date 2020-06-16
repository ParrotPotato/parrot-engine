#ifndef PARROT_LOGGER_HH
#define PARROT_LOGGER_HH

// TODO(nitesh): Implement a simple logger for handling logs
// and error buffer

#include <cstdarg>

namespace parrot
{
	class Log
	{
		public:

		static int trace(const char * formatstring, ...);
		static int debug(const char * formatstring, ...);
		static int info(const char * formatstring, ...);
		static int warn(const char * formatstring, ...);
		static int error(const char * formatstring, ...);
		static int fatal(const char * formatstring, ...);

		static void set_show_time(bool showtime){showtime_ = showtime;}
		static void set_show_date(bool showdate){showdate_ = showdate;}
		static void set_show_type(bool showtype){showtype_ = showtype;}

		private:

		enum Level {
			tracemsg = 0, 
			debugmsg = 1, 
			infomsg = 2, 
			warnmsg = 3, 
			errormsg = 4, 
			fatalmsg = 5
		};

		static int internal_printf(Level level, 
				const char * format, 
				std::va_list ap);

		static inline const char * type_string(Level level);
		static inline const char * color_string(Level level);

		static inline void pre_formatted_string(Level level, char buffer[50]);

		static inline void get_time_embedded_string(char buffer[30]);

		static bool showtime_;
		static bool showdate_;
		static bool showtype_;
	};
} 

#endif 
