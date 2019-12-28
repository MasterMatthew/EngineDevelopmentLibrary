#ifndef LOGGER_H
#define LOGGER_H

//Simple c logger

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <thread>

#ifdef LOG_ACTIVE_LEVEL
#define SPDLOG_ACTIVE_LEVEL LOG_ACTIVE_LEVEL
#endif //LOG_ACTIVE_LEVEL
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

//Might need to be a bitfield
#define LOG_LEVEL_OFF	SPDLOG_LEVEL_OFF
#define LOG_LEVEL_TRACE SPDLOG_LEVEL_TRACE
#define LOG_LEVEL_DEBUG SPDLOG_LEVEL_DEBUG
#define LOG_LEVEL_INFO	SPDLOG_LEVEL_INFO
#define LOG_LEVEL_WARN	SPDLOG_LEVEL_WARN
#define LOG_LEVEL_ERROR SPDLOG_LEVEL_ERROR
#define LOG_LEVEL_CRIT	SPDLOG_LEVEL_CRITICAL

#define LOG_ENUM_TRACE	spdlog::level::level_enum::trace
#define LOG_ENUM_DEBUG	spdlog::level::level_enum::debug
#define LOG_ENUM_INFO	spdlog::level::level_enum::info
#define LOG_ENUM_WARN	spdlog::level::level_enum::warn
#define LOG_ENUM_ERROR	spdlog::level::level_enum::error
#define LOG_ENUM_CRIT	spdlog::level::level_enum::critical

#define LOG_TEXT_TRACE	"[TRACE]"
#define LOG_TEXT_DEBUG	"[DEBUG]"
#define LOG_TEXT_INFO	"[INFO] "
#define LOG_TEXT_WARN	"[WARN] "
#define LOG_TEXT_ERROR	"[ERROR]"
#define LOG_TEXT_CRIT	"[CRIT] "

inline char* log_level_text(uint32_t level) {
	switch (level) {
	case LOG_LEVEL_TRACE:	return LOG_TEXT_TRACE;
	case LOG_LEVEL_DEBUG:	return LOG_TEXT_DEBUG;
	case LOG_LEVEL_INFO:	return LOG_TEXT_INFO;
	case LOG_LEVEL_WARN:	return LOG_TEXT_WARN;
	case LOG_LEVEL_ERROR:	return LOG_TEXT_ERROR;
	case LOG_LEVEL_CRIT:	return LOG_TEXT_CRIT;
	default:				return "[ABCDE]";
	}
}

typedef spdlog::source_loc src_loc;
typedef spdlog::string_view_t str_view_t;
typedef std::shared_ptr<spdlog::logger> logger_t;

inline logger_t& default_logger_instance() {
	static logger_t logger = spdlog::default_logger();
	return logger;
}

inline void init_default_logger() {
	time_t t; time(&t);
	char* filename = (char*) malloc((sizeof(time_t) + 8) * sizeof(char));
	sprintf(filename, "%d-log.txt", t);

	logger_t& logger = default_logger_instance();
	logger = spdlog::basic_logger_mt("LOG", filename);
	spdlog::set_default_logger(logger);
}


//extern "C" inline void log();

//template<typename... Args>
//inline void log(logger_t src, uint32_t level, str_view_t fmt, ...) {spdlog::log(src, level, fmt, args);}

#define LOG(logger, level, ...)			SPDLOG_LOGGER_CALL(logger, level, __VA_ARGS__)

#define LOG_LOGGER_TRACE(logger, ...)	SPDLOG_LOGGER_TRACE(logger, __VA_ARGS__)
#define LOG_TRACE(...)					SPDLOG_TRACE(__VA_ARGS__)

#define LOG_LOGGER_DEBUG(logger, ...)	SPDLOG_LOGGER_DEBUG(logger, __VA_ARGS__)
#define LOG_DEBUG(...)					SPDLOG_DEBUG(__VA_ARGS__)

#define LOG_LOGGER_INFO(logger, ...)	SPDLOG_LOGGER_INFO(logger, __VA_ARGS__)
#define LOG_INFO(...)					SPDLOG_INFO(__VA_ARGS__)

#define LOG_LOGGER_WARN(logger, ...)	SPDLOG_LOGGER_WARN(logger, __VA_ARGS__)
#define LOG_WARN(...)					SPDLOG_WARN(__VA_ARGS__)

#define LOG_LOGGER_ERROR(logger, ...)	SPDLOG_LOGGER_ERROR(logger, __VA_ARGS__)
#define LOG_ERROR(...)					SPDLOG_ERROR(__VA_ARGS__)

#define LOG_LOGGER_CRIT(logger, ...)	SPDLOG_LOGGER_CRITICAL(logger, __VA_ARGS__)
#define LOG_CRIT(...)					SPDLOG_CRITICAL(__VA_ARGS__)



#endif // !LOGGER_H
