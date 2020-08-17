#include <fstream>

#include "ini_processing.h"

void ini_save(ini_info_t& data, std::string file_path)
{
    std::ofstream ini_stream(file_path, std::ios::out | std::ios::trunc);
    if (!ini_stream.is_open())
        return;

    for (auto it0 = data.begin(); it0 != data.end(); ++it0)
    {
        ini_stream << '[' << it0->first << ']' << std::endl;

        for (auto it1 = it0->second.begin(); it1 != it0->second.end(); ++it1)
            ini_stream << it1->first << '=' << it1->second << std::endl;

        ini_stream << std::endl;
    }

    ini_stream.close();
}

ini_info_t ini_load(std::string file_path)
{
}