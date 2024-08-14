#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include "Logger.h"

void testBasicLogging() {
    auto logger = LoggerManager().createLogger("TestLogger");
    logger->setLogLevel(LogLevel::DEBUG);
    logger->addDestination(std::make_unique<ConsoleDestination>());
    logger->start();

    LOG_DEBUG(logger, "This is a debug message");
    LOG_INFO(logger, "This is an info message");
    LOG_WARNING(logger, "This is a warning message");
    LOG_ERROR(logger, "This is an error message");

    logger->stop();
}

void testFileLogging() {
    auto logger = LoggerManager().createLogger("FileLogger");
    logger->setLogLevel(LogLevel::INFO);
    logger->addDestination(std::make_unique<FileDestination>("test.log", 1024 * 1024, 5));
    logger->start();

    for (int i = 0; i < 100; ++i) {
        LOG_INFO(logger, "File log message %d", i);
    }

    logger->stop();
}

void testCustomFormatter() {
    auto logger = LoggerManager().createLogger("CustomLogger");
    logger->setLogLevel(LogLevel::DEBUG);
    logger->addDestination(std::make_unique<ConsoleDestination>());
    logger->setFormatter(std::make_unique<PatternFormatter>("[%Y-%m-%d %H:%M:%S] [%l] (%v)"));
    logger->start();

    LOG_DEBUG(logger, "Custom formatted debug message");
    LOG_INFO(logger, "Custom formatted info message");

    logger->stop();
}

void testMultiThreadedLogging() {
    auto logger = LoggerManager().createLogger("MultiThreadLogger");
    logger->setLogLevel(LogLevel::INFO);
    logger->addDestination(std::make_unique<ConsoleDestination>());
    logger->start();

    auto logFunc = [&logger](int threadId) {
        for (int i = 0; i < 10; ++i) {
            LOG_INFO(logger, "Thread %d: Log message %d", threadId, i);
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    };

    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back(logFunc, i);
    }

    for (auto& thread : threads) {
        thread.join();
    }

    logger->stop();
}

void testAssertions() {
    auto logger = LoggerManager().createLogger("AssertLogger");
    logger->setLogLevel(LogLevel::FATAL);
    logger->addDestination(std::make_unique<ConsoleDestination>());
    logger->start();

    int x = 5, y = 10;
    ASSERT(x < y, "x should be less than y");
    ASSERT_EQ(x, 5, "x should equal 5");
    ASSERT_NE(x, y, "x should not equal y");
    ASSERT_GT(y, x, "y should be greater than x");

    // This assertion will fail and terminate the program
    // Uncomment to test
    // ASSERT_EQ(x, y, "This assertion will fail");

    logger->stop();
}

int main() {
    std::cout << "Testing Basic Logging:" << std::endl;
    testBasicLogging();

    std::cout << "\nTesting File Logging:" << std::endl;
    testFileLogging();

    std::cout << "\nTesting Custom Formatter:" << std::endl;
    testCustomFormatter();

    std::cout << "\nTesting Multi-threaded Logging:" << std::endl;
    testMultiThreadedLogging();

    std::cout << "\nTesting Assertions:" << std::endl;
    testAssertions();

    return 0;
}