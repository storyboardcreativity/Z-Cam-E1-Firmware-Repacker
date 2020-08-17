#include <map>

typedef std::map <std::string, std::map<std::string, std::string>> ini_info_t;

void ini_save(ini_info_t& data, std::string file_path);
ini_info_t ini_load(std::string file_path);