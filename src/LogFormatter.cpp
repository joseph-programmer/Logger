#include "LogFormatter.h"
#include <sstream>
#include <iomanip>
#include <array>

namespace Core {
	
PatternFormatter::PatternFormatter(const std::string& pattern) : m_pattern(pattern) {}

std::string PatternFormatter::format(LogLevel level, const std::chrono::system_clock::time_point& timestamp,
                                     const std::string& file, int line, const std::string& message) const {
    std::stringstream ss;
    for (size_t i = 0; i < m_pattern.size(); ++i) {
        if (m_pattern[i] == '%' && i + 1 < m_pattern.size()) {
            char fmtChar = m_pattern[i + 1];
            switch (fmtChar) {
                case 'Y': ss << getFormattedTime(timestamp, "%Y"); break;
                case 'm': ss << getFormattedTime(timestamp, "%m"); break;
                case 'd': ss << getFormattedTime(timestamp, "%d"); break;
                case 'H': ss << getFormattedTime(timestamp, "%H"); break;
                case 'M': ss << getFormattedTime(timestamp, "%M"); break;
                case 'S': ss << getFormattedTime(timestamp, "%S"); break;
                case 'l': ss << getLevelString(level); break;
                case 'v': ss << message; break;
                default: ss << fmtChar; break;
            }
            ++i;
        } else {
            ss << m_pattern[i];
        }
    }
    return ss.str();
}

std::string PatternFormatter::getFormattedTime(const std::chrono::system_clock::time_point& timestamp, const char* format) const {
    auto tt = std::chrono::system_clock::to_time_t(timestamp);
    std::tm tm;
    localtime_r(&tt, &tm);
    std::stringstream ss;
    ss << std::put_time(&tm, format);
    return ss.str();
}

const char* PatternFormatter::getLevelString(LogLevel level) {
    static const std::array<const char*, 5> levelStrings = {
        "DEBUG", "INFO", "WARNING", "ERROR", "FATAL"
    };
    return levelStrings[static_cast<size_t>(level)];
}

}