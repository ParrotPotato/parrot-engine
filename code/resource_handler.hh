#ifndef PARROT_RESOURCE_HANDLER

#include <string>
#include <vector>

namespace parrot
{
	class Resource_Loader
	{
		public:
		static std::string load_file_in_string(std::string filename);
		static std::vector<std::string> load_file_in_string_vec(std::string filename);
	};
}

#define PARROT_RESOURCE_HANDLER
#endif
