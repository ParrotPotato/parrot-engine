#ifndef PARROT_CORE 

#include <stdint.h>

namespace parrot{

	typedef int8_t int8;
	typedef int16_t int16;
	typedef int32_t int32;
	typedef int64_t int64;

	typedef uint8_t uint8;
	typedef uint16_t uint16;
	typedef uint32_t uint32;
	typedef uint64_t uint64;

	typedef float real32;
	typedef double real64;

	class Core
	{
		public:
			static void init();
			static bool is_running();
			static void terminate_core();
		private:
			static bool is_engine_running;	
	};

}

#define PARROT_CORE
#endif
