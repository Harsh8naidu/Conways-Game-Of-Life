#include "PatternDetector.h"
#include <iostream>

const std::vector<std::pair<int, int>> PatternDetector::blockOffsets = {
    {0,0}, {0,1}, {1,0}, {1,1}
};

const std::vector<std::pair<int, int>> PatternDetector::beehiveOffsets = {
    {0,1}, {0,2}, {1,0}, {1,3}, {2,1}, {2,2}
};

const std::vector<std::pair<int, int>> PatternDetector::blinkerOffsets = {
    {0,0}, {0,1}, {0,2}
};

const std::vector<std::pair<int, int>> PatternDetector::toadOffsets = {
    {0,0}, {0,1}, {0,2}, {1,1}, {1,2}
};

const std::vector<std::pair<int, int>> PatternDetector::gliderOffsets = {
    {0,1}, {1,2}, {2,0}, {2,1}, {2,2}
};

const std::vector<std::pair<int, int>> PatternDetector::lwssOffsets = {
    {0,1}, {0,2}, {1,0}, {1,3}, {2,0}, {2,3}, {3,1}, {3,2}
};

const std::vector<std::pair<int, int>> PatternDetector::pulsarOffsets = {
    {0,2}, {0,3}, {0,4}, {1,0}, {1,5}, {2,0}, {2,5}, {3,2}, {3,3}, {3,4}, {4,2}, {4,3}, {4,4}, {5,0}, {5,5}
};

const std::vector<std::pair<int, int>> PatternDetector::gliderGunOffsets = {
    {0,24}, {1,24}, {2,24}, {10,22}, {10,23}, {10,24}, {11,21}, {11,25}, {12,20}, {12,26}, {13,20}, {13,26}, 
    {14,23}, {15,24}, {16,24}, {17,23}, {17,22}, {18,22}, {18,21}, {19,21}, {19,20}, {19,19}, {20,19}, {21,19}
};

const std::vector<std::pair<int, int>> PatternDetector::diehardOffsets = {
    {0,0}, {1,0}, {2,0}, {2,1}, {3,1}, {3,2}, {4,2}, {4,3}
};

const std::unordered_map<std::string, std::vector<std::pair<int, int>>> PatternDetector::patternOffsets = {
    {"block", PatternDetector::blockOffsets},
    {"beehive", PatternDetector::beehiveOffsets},
    {"blinker", PatternDetector::blinkerOffsets},
    {"toad", PatternDetector::toadOffsets},
    {"glider", PatternDetector::gliderOffsets},
    {"lwss", PatternDetector::lwssOffsets},
    {"pulsar", PatternDetector::pulsarOffsets},
    {"glider gun", PatternDetector::diehardOffsets}
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