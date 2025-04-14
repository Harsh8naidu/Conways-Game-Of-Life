#pragma once
#include <vector>
#include <string>
#include <unordered_map>

namespace PatternDetector {
    bool ContainsPattern(const std::vector<std::vector<bool>>& grid, std::string pattern);

    extern const std::unordered_map<std::string, std::vector<std::pair<int, int>>> patternOffsets;

    const std::vector<std::string> GetAvailablePatterns();

    extern const std::vector<std::pair<int, int>> blockOffsets;
    extern const std::vector<std::pair<int, int>> beehiveOffsets;
    extern const std::vector<std::pair<int, int>> blinkerOffsets;
    extern const std::vector<std::pair<int, int>> toadOffsets;
    extern const std::vector<std::pair<int, int>> gliderOffsets;
    extern const std::vector<std::pair<int, int>> lwssOffsets;
}
