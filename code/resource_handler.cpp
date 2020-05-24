#ifndef PARROT_RESOURCE_HANDLER

#include <fstream>
#include <string>
#include <vector>

namespace parrot
{
	class Resource_Loader
	{
		public:
		static std::string load_file_in_string(std::string filename)
		{
			std::string res;
			std::fstream file;

			file.open(filename, std::ios::in);

			if(file.fail())
			{
				return res;
			}

			file.seekg(0, std::ios::end);
			res.reserve(file.tellg());
			file.seekg(0, std::ios::beg);

			res.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char> ());
			file.close();

			return res;
		}

		static std::vector<std::string> load_file_in_string_vec(std::string filename)
		{
			std::vector<std::string> res;
			std::string line;

			std::fstream file;
			file.open(filename, std::ios::in);

			if(file.fail())
			{
				std::cerr << "Unable to open file " << filename <<  " " ;
				perror("");
				return res;
			}

			while(std::getline(file, line))
				res.push_back(line);

			return res;
		}
	};
}

#define PARROT_RESOURCE_HANDLER
#endif
