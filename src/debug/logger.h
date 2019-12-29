#ifndef LOGGER_H
#define LOGGER_H

#define LOG_ACTIVE_LEVEL 0
#ifdef LOG_ACTIVE_LEVEL
#define SPDLOG_ACTIVE_LEVEL LOG_ACTIVE_LEVEL
#endif //LOG_ACTIVE_LEVEL


//Simple c logger

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>


#ifdef __cplusplus
extern "C" {
#endif  

#define LOG_LEVEL_TRACE 0
#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_INFO	2
#define LOG_LEVEL_WARN	3
#define LOG_LEVEL_ERROR 4
#define LOG_LEVEL_CRIT	5
#define LOG_LEVEL_OFF	6


void debug_log(void* logger, uint32_t level, char* fmt, ...);

void* default_logger_instance();



#define LOG_LOGGER(logger, level, ...)	debug_log(logger, level, __VA_ARGS__)
#define LOG(level, ...)					LOG_LOGGER(default_logger_instance(), level, __VA_ARGS__)

#define LOG_LOGGER_TRACE(logger, ...)	LOG_LOGGER(logger, LOG_LEVEL_TRACE, __VA_ARGS__)
#define LOG_TRACE(...)					LOG(LOG_LEVEL_TRACE, __VA_ARGS__)

#define LOG_LOGGER_DEBUG(logger, ...)	LOG_LOGGER(logger, LOG_LEVEL_DEBUG, __VA_ARGS__)
#define LOG_DEBUG(...)					LOG(LOG_LEVEL_DEBUG, __VA_ARGS__)

#define LOG_LOGGER_INFO(logger, ...)	LOG_LOGGER(logger, LOG_LEVEL_INFO, __VA_ARGS__)
#define LOG_INFO(...)					LOG(LOG_LEVEL_INFO, __VA_ARGS__)

#define LOG_LOGGER_WARN(logger, ...)	LOG_LOGGER(logger, LOG_LEVEL_WARN, __VA_ARGS__)
#define LOG_WARN(...)					LOG(LOG_LEVEL_WARN, __VA_ARGS__)

#define LOG_LOGGER_ERROR(logger, ...)	LOG_LOGGER(logger, LOG_LEVEL_ERROR, __VA_ARGS__)
#define LOG_ERROR(...)					LOG(LOG_LEVEL_ERROR, __VA_ARGS__)

#define LOG_LOGGER_CRIT(logger, ...)	LOG_LOGGER(logger, LOG_LEVEL_CRIT, __VA_ARGS__)
#define LOG_CRIT(...)					LOG(LOG_LEVEL_CRIT, __VA_ARGS__)


#ifdef __cplusplus
}
#endif
#endif // !LOGGER_H
/*

inline void init_default_logger() {
	time_t t; time(&t);
	char* filename = (char*) malloc((sizeof(time_t) + 8) * sizeof(char));
	sprintf(filename, "%d-log.txt", t);

	logger_t& logger = default_logger_instance();
	logger = spdlog::basic_logger_mt("LOG", filename);
	spdlog::set_default_logger(logger);
}
*/


