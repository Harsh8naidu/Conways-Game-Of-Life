#include "PatternDetector.h"
#include <iostream>

const std::vector<std::pair<int, int>> PatternDetector::blockOffsets = {
    {0,0}, {0,1}, {1,0}, {1,1}
};

const std::vector<std::pair<int, int>> PatternDetector::beehiveOffsets = {
    {0,1}, {0,2}, {1,0}, {1,3}, {2,1}, {2,2}
};

const std::vector<std::pair<int, int>> PatternDetector::blinkerOffsets = {
    {0,0}, {0,1}, {1,0}, {1,1}
};

const std::vector<std::pair<int, int>> PatternDetector::toadOffsets = {
    {0,0}, {0,1}, {1,0}, {1,1}
};

const std::vector<std::pair<int, int>> PatternDetector::gliderOffsets = {
    {0,0}, {0,1}, {1,0}, {1,1}
};

const std::vector<std::pair<int, int>> PatternDetector::lwssOffsets = {
    {0,0}, {0,1}, {1,0}, {1,1}
};

const std::unordered_map<std::string, std::vector<std::pair<int, int>>> PatternDetector::patternOffsets = {
    {"block", PatternDetector::blockOffsets},
    {"beehive", PatternDetector::beehiveOffsets},
    {"blinker", PatternDetector::blinkerOffsets},
    {"toad", PatternDetector::toadOffsets},
    {"glider", PatternDetector::gliderOffsets},
    {"lwss", PatternDetector::lwssOffsets}
};

const std::vector<std::string> PatternDetector::GetAvailablePatterns()
{
    std::vector<std::string> availablePatterns;
    availablePatterns.reserve(patternOffsets.size());
    for (const auto& it : patternOffsets) {
        availablePatterns.emplace_back(it.first);
    }
    return availablePatterns;
}

bool PatternDetector::ContainsPattern(const std::vector<std::vector<bool>>& grid, std::string pattern)
{
    auto it = patternOffsets.find(pattern);
    if (it == patternOffsets.end()) {
        return false;
    }

    const auto& offsets = it->second;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {

            bool found = true;
            for (const auto& offset : offsets) {
                int r = i + offset.first;
                int c = j + offset.second;

                if (r < 0 || c < 0 || r >= grid.size() || c >= grid[r].size() || !grid[r][c]) {
                    found = false;
                    break;
                }
            }

            if (found) return false;
        }
    }

    return false;
}