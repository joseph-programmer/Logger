#ifndef LOG_DESTINATION_H
#define LOG_DESTINATION_H

#include "LoggerPCH.h"

namespace Core {

/**
 * @class LogDestination
 * @brief Abstract base class for log destinations.
 *
 * LogDestination defines an interface for output destinations of log messages,
 * such as files or console. Derived classes should implement the write and flush methods.
 */
class LogDestination {
public:
    /**
     * @brief Destructor for the LogDestination class.
     */
    virtual ~LogDestination() = default;

    /**
     * @brief Writes a log message to the destination.
     * @param message The message to write.
     */
    virtual void write(const std::string& message) = 0;

    /**
     * @brief Flushes any buffered messages to the destination.
     */
    virtual void flush() = 0;
};

/**
 * @class ConsoleDestination
 * @brief Outputs log messages to the console.
 *
 * The ConsoleDestination class handles writing log messages to the console,
 * optionally supporting colored output.
 */
class ConsoleDestination : public LogDestination {
public:
    /**
     * @brief Constructor for ConsoleDestination.
     * @param useColor Whether to use colored output.
     */
    ConsoleDestination(bool useColor = true);

    /**
     * @brief Writes a log message to the console.
     * @param message The message to write.
     */
    void write(const std::string& message) override;

    /**
     * @brief Flushes the console output.
     */
    void flush() override;

private:
    bool m_useColor; ///< Indicates if color should be used in console output.
};

/**
 * @class FileDestination
 * @brief Outputs log messages to a file with rotation.
 *
 * The FileDestination class handles writing log messages to a file,
 * with support for rotating log files based on size and number of files.
 */
class FileDestination : public LogDestination {
public:
    /**
     * @brief Constructor for FileDestination.
     * @param filename The base filename for the log files.
     * @param maxFileSize The maximum size of a single log file in bytes.
     * @param maxFiles The maximum number of log files to keep.
     */
    FileDestination(const std::string& filename, size_t maxFileSize, int maxFiles);

    /**
     * @brief Destructor for FileDestination.
     */
    ~FileDestination();

    /**
     * @brief Writes a log message to the file.
     * @param message The message to write.
     */
    void write(const std::string& message) override;

    /**
     * @brief Flushes the file output.
     */
    void flush() override;

private:
    /**
     * @brief Opens the log file for writing.
     */
    void openLogFile();

    /**
     * @brief Rotates the log files.
     */
    void rotateLogFiles();

    std::string m_filename; ///< The base filename for log files.
    size_t m_maxFileSize; ///< Maximum size for a single log file.
    int m_maxFiles; ///< Maximum number of log files to keep.
    std::ofstream m_logFile; ///< Output file stream for logging.
};

} // namespace Core

#endif // LOG_DESTINATION_H
