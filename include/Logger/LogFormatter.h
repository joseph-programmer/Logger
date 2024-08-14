#ifndef LOG_FORMATTER_H
#define LOG_FORMATTER_H

#include "LoggerPCH.h"

namespace Core {

/**
 * @class LogFormatter
 * @brief Abstract base class for log message formatting.
 *
 * LogFormatter provides an interface for formatting log messages.
 * Derived classes should implement the format method to customize message output.
 */
class LOGGER_API LogFormatter {
public:
    /**
     * @brief Destructor for the LogFormatter class.
     */
    virtual ~LogFormatter() = default;

    /**
     * @brief Formats a log message.
     * @param level The log level of the message.
     * @param timestamp The timestamp when the log was created.
     * @param file The source file where the log was generated.
     * @param line The line number in the source file.
     * @param message The log message.
     * @return A formatted log message as a string.
     */
    virtual std::string format(LogLevel level, const std::chrono::system_clock::time_point& timestamp,
                               const std::string& file, int line, const std::string& message) const = 0;
};

/**
 * @class PatternFormatter
 * @brief Formats log messages based on a pattern.
 *
 * The PatternFormatter allows customization of the log output format
 * by specifying a pattern string, which can include timestamps, log levels, and other details.
 */
class LOGGER_API PatternFormatter : public LogFormatter {
public:
    /**
     * @brief Constructor for PatternFormatter with a specific pattern.
     * @param pattern The pattern string for formatting.
     */
    explicit PatternFormatter(const std::string& pattern);

    /**
     * @brief Formats a log message according to the specified pattern.
     * @param level The log level of the message.
     * @param timestamp The timestamp when the log was created.
     * @param file The source file where the log was generated.
     * @param line The line number in the source file.
     * @param message The log message.
     * @return A formatted log message as a string.
     */
    std::string format(LogLevel level, const std::chrono::system_clock::time_point& timestamp,
                       const std::string& file, int line, const std::string& message) const override;

private:
    std::string m_pattern; ///< The pattern string for formatting.

    /**
     * @brief Formats the timestamp.
     * @param timestamp The time point to format.
     * @param format The time format string.
     * @return A formatted time string.
     */
    std::string getFormattedTime(const std::chrono::system_clock::time_point& timestamp, const char* format) const;

    /**
     * @brief Gets the string representation of the log level.
     * @param level The log level.
     * @return A string representing the log level.
     */
    static const char* getLevelString(LogLevel level);
};

} // namespace Core

#endif // LOG_FORMATTER_H
