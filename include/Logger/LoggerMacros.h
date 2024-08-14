#ifndef LOGGER_MACROS_H
#define LOGGER_MACROS_H

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include <atomic>
#include <thread>
#include <queue>
#include <condition_variable>
#include "LogLevel.h"
#include "Logger.h"
#include "LoggerManager.h"

#ifdef LOGGER_COMPILED_LIB
    #if defined(LOGGER_SHARED_LIB)
        #if defined(_WIN32)
            #ifdef LOGGER_EXPORTS
                #define LOGGER_API __declspec(dllexport)
            #else  // !LOGGER_EXPORTS
                #define LOGGER_API __declspec(dllimport)
            #endif
        #else  // !defined(_WIN32)
            #define LOGGER_API __attribute__((visibility("default")))
        #endif
    #else  // !defined(LOGGER_SHARED_LIB)
        #define LOGGER_API
    #endif
#else  // !defined(LOGGER_COMPILED_LIB)
    #define LOGGER_API
#endif  // #ifdef LOGGER_COMPILED_LIB

/**
 * @brief Logs a debug message using the specified logger.
 * @param logger The logger instance to use.
 * @param ... The message format and arguments.
 */
#define LOG_DEBUG(logger, ...) do { \
    logger->log(LogLevel::DEBUG, __FILE__, __LINE__, __VA_ARGS__); \
} while(0)

/**
 * @brief Logs an informational message using the specified logger.
 * @param logger The logger instance to use.
 * @param ... The message format and arguments.
 */
#define LOG_INFO(logger, ...) do { \
    logger->log(LogLevel::INFO, __FILE__, __LINE__, __VA_ARGS__); \
} while(0)

/**
 * @brief Logs a warning message using the specified logger.
 * @param logger The logger instance to use.
 * @param ... The message format and arguments.
 */
#define LOG_WARNING(logger, ...) do { \
    logger->log(LogLevel::WARNING, __FILE__, __LINE__, __VA_ARGS__); \
} while(0)

/**
 * @brief Logs an error message using the specified logger.
 * @param logger The logger instance to use.
 * @param ... The message format and arguments.
 */
#define LOG_ERROR(logger, ...) do { \
    logger->log(LogLevel::ERROR, __FILE__, __LINE__, __VA_ARGS__); \
} while(0)

/**
 * @brief Logs a fatal error message and aborts the program.
 * @param logger The logger instance to use.
 * @param ... The message format and arguments.
 */
#define LOG_FATAL(logger, ...) do { \
    logger->log(LogLevel::FATAL, __FILE__, __LINE__, __VA_ARGS__); \
    abort(); \
} while(0)

/**
 * @brief Asserts that a condition is true; logs a fatal error and aborts if false.
 * @param condition The condition to check.
 * @param message The message to log if the assertion fails.
 */
#define ASSERT(condition, message) \
    do { \
        if (!(condition)) { \
            LOG_FATAL(LoggerManager::getLogger("default"), "Assertion failed: " #condition ". " message); \
        } \
    } while (0)

/**
 * @brief Asserts that two values are equal; logs a fatal error and aborts if not.
 * @param expected The expected value.
 * @param actual The actual value.
 * @param message The message to log if the assertion fails.
 */
#define ASSERT_EQ(expected, actual, message) \
    do { \
        if ((expected) != (actual)) { \
            LOG_FATAL(LoggerManager::getLogger("default"), "Assertion failed: expected " #expected " == " #actual ". " \
            "Expected: " + std::to_string(expected) + ", Actual: " + std::to_string(actual) + ". " message); \
        } \
    } while (0)

/**
 * @brief Asserts that two values are not equal; logs a fatal error and aborts if they are.
 * @param expected The expected value.
 * @param actual The actual value.
 * @param message The message to log if the assertion fails.
 */
#define ASSERT_NE(expected, actual, message) \
    do { \
        if ((expected) == (actual)) { \
            LOG_FATAL(LoggerManager::getLogger("default"), "Assertion failed: expected " #expected " != " #actual ". " \
            "Both were: " + std::to_string(actual) + ". " message); \
        } \
    } while (0)

/**
 * @brief Asserts that one value is greater than another; logs a fatal error and aborts if not.
 * @param val1 The first value.
 * @param val2 The second value.
 * @param message The message to log if the assertion fails.
 */
#define ASSERT_GT(val1, val2, message) \
    do { \
        if (!((val1) > (val2))) { \
            LOG_FATAL(LoggerManager::getLogger("default"), "Assertion failed: " #val1 " > " #val2 ". " \
            #val1 ": " + std::to_string(val1) + ", " #val2 ": " + std::to_string(val2) + ". " message); \
        } \
    } while (0)

#endif // LOGGER_MACROS_H
