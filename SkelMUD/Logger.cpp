#include "Logger.h"
#include "Utils.h"
#include <iostream>

Logger::Log_Level Logger::m_level = L_DEBUG;

void Logger::Debug(std::string message) {
    if (m_level == L_DEBUG) {
        logMessage("DEBUG", message);
    }
}

void Logger::Info(std::string message) {
    if (m_level == L_DEBUG || m_level == L_INFO) {
        logMessage("INFO", message);
    }
}

void Logger::Error(std::string message) {
    if (m_level == L_DEBUG || m_level == L_INFO || m_level == L_ERROR) {
        logMessage("ERROR", message);
    }
}

std::string Logger::TimeStamp() {
    time_t rawtime;
    struct tm timeinfo;

    time(&rawtime);
#ifdef _WIN32
	localtime_s(&timeinfo, &rawtime);
	char timebuf[26];
	#else
    timeinfo = *localtime(&rawtime);
    char* timebuf;
#endif
#ifdef _WIN32
	asctime_s(timebuf, 26, &timeinfo);
	#else
    timebuf = asctime(&timeinfo);
#endif
    std::string output = std::string(timebuf);
    Utils::RemoveEndline(output);
    return output;
}

void Logger::SetOutputLevel(Logger::Log_Level level) {
    m_level = level;
}

void Logger::logMessage(std::string log_type, std::string message) {
    Utils::RemoveEndline(message);
    std::cout << TimeStamp() << " " << log_type << " " << message << std::endl;
}
