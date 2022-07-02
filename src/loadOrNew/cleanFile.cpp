/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** remove isplaying
*/

#include <vector>
#include <fstream>

static std::vector<std::string> find_isplaying(std::string file_name)
{
    std::vector<std::string> result;
    std::ifstream file(file_name);
    std::string line;

    while (std::getline(file, line))
        if (line.find("::isplaying") != std::string::npos)
            result.push_back(line);
    return result;
}

bool remove_isplaying(const std::string &filename)
{
    std::vector<std::string> strReplace = find_isplaying(filename.c_str());
    std::string tmp;
    std::ifstream filein(filename.c_str());
    std::ofstream fileout("tmp.txt");

    if (!filein || !fileout)
        return false;

    while (filein >> tmp) {
        for (auto &str : strReplace) {
            if (tmp == str)
                tmp = str.substr(0, str.find("::")) + ":";
        }
        tmp += "\n";
        fileout << tmp;
    }
    filein.close();
    fileout.close();
    rename("tmp.txt", filename.c_str());
    return true;
}
