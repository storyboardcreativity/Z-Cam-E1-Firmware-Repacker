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
    ini_info_t ini_info;

    std::ifstream ini_stream(file_path, std::ios::in);
    if (!ini_stream.is_open())
    {
        // Parsing error
        return ini_info;
    }

    std::string group_name;
    for (std::string tmp; std::getline(ini_stream, tmp); )
    {
        // Skip empty lines
        if (tmp.size() == 0)
            continue;

        if (tmp[0] == '[')
        {
            if (tmp[tmp.size() - 1] != ']')
            {
                // Parsing error
                return ini_info;
            }

            group_name = tmp.substr(1, tmp.size() - 2);
            continue;
        }

        auto left = tmp.substr(0, tmp.find("="));
        if (left.size() == tmp.size())
        {
            // Parsing error
            return ini_info;
        }

        auto right = tmp.substr(left.size() + 1, tmp.size() - left.size() - 1);

        ini_info[group_name][left] = right;
    }

    return ini_info;
}