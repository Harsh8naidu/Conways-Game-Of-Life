#include "StringUtils.h"
#include <algorithm>
#include <cctype>

void Trim(std::string& s)
{
    // Trim leading spaces
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));

    // Trim trailing spaces
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}