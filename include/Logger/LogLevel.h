#ifndef LOG_LEVEL_H
#define LOG_LEVEL_H

/**
 * @enum LogLevel
 * @brief Defines the various levels of logging severity.
 *
 * This enumeration provides different levels of logging severity, which can be used
 * to categorize log messages according to their importance and urgency.
 */
enum class LogLevel {
    DEBUG,   ///< Detailed information, typically of interest only when diagnosing problems.
    INFO,    ///< Informational messages that highlight the progress of the application.
    WARNING, ///< Indications that something unexpected happened, or indicative of some problem.
    ERROR,   ///< Error events that might still allow the application to continue running.
    FATAL    ///< Severe error events that lead the application to abort.
};

#endif // LOG_LEVEL_H

