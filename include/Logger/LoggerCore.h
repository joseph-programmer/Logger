#ifndef LOGGERCORE_H
#define LOGGERCORE_H

#include "LoggerPCH.h"

/**
 * @class Logger
 * @brief A class for logging messages with various levels of severity.
 *
 * The Logger class manages the logging system, allowing users to set log levels,
 * add destinations, and format messages. It includes a thread-safe queue for
 * handling log messages asynchronously.
 */
class Logger {
public:
    /**
     * @brief Constructor for the Logger class.
     */
    Logger();

    /**
     * @brief Destructor for the Logger class.
     */
    ~Logger();

    /**
     * @brief Sets the logging level.
     * @param level The logging level to set.
     */
    void setLogLevel(LogLevel level);

    /**
     * @brief Adds a destination for log messages.
     * @param destination A unique pointer to a LogDestination object.
     */
    void addDestination(std::unique_ptr<LogDestination> destination);

    /**
     * @brief Sets the formatter for log messages.
     * @param formatter A unique pointer to a LogFormatter object.
     */
    void setFormatter(std::unique_ptr<LogFormatter> formatter);

    /**
     * @brief Logs a message with the given level.
     * @param level The severity level of the log message.
     * @param file The file where the log was generated.
     * @param line The line number where the log was generated.
     * @param format The format string for the message.
     * @param args The arguments for the format string.
     */
    template<typename... Args>
    void log(LogLevel level, const char* file, int line, const char* format, Args... args);

    /**
     * @brief Starts the logging process.
     */
    void start();

    /**
     * @brief Stops the logging process.
     */
    void stop();

private:
    // Member variables and helper methods
};

#endif // LOGGERCORE_H
