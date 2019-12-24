#ifndef LOGGER_H
#define LOGGER_H

//Simpler c logger

#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#ifdef __cplusplus
//extern "C" {
#endif // __cplusplus

typedef struct logger {
	char* filename;
} logger;

inline logger* default_logger_instance() {
	static logger* instance;
	//I hate this so much but we can't use functions in static initializers

	if (instance == NULL) {
		time_t t; time(&t);

		instance = malloc(sizeof(logger));
		instance->filename = malloc((sizeof(time_t) + 8) * sizeof(char));
		
		sprintf(instance->filename, "%d-log.txt", t);
	}
	return instance;
}

//Level is unchecked, don't call with a value greater than 5
inline char* log_level_text(uint32_t level) {
	static char* level_text[] = { "[TRACE]", "[DEBUG]", "[INFO] ", "[WARN] ", "[ERROR]", "[CRIT] " };
	return level_text[level];
}

//TODO: Use ... style args
inline void log(logger* logger, uint32_t level, const char* str) {
	time_t t;
	time(&t);
	struct tm* t_info = localtime(&t);

	FILE* stream = fopen(logger->filename, "a");

	fprintf(stream, "[%02d:%02d:%02d] %s : %s\n", t_info->tm_hour, t_info->tm_min, t_info->tm_sec, log_level_text(level), str);

	fclose(stream);
}

//Might need to be a bitfield
#define LOG_LEVEL_OFF	-1
#define LOG_LEVEL_TRACE 0
#define LOG_LEVEL_DEBUG 1
#define LOG_LEVEL_INFO	2
#define LOG_LEVEL_WARN	3
#define LOG_LEVEL_ERROR 4
#define LOG_LEVEL_CRIT	5

#define LOG(logger, level, ...)			log(logger, level, __VA_ARGS__)

#define LOG_LOGGER_TRACE(logger, ...)	LOG(logger,						LOG_LEVEL_TRACE,	__VA_ARGS__)
#define LOG_TRACE(...)					LOG(default_logger_instance(),	LOG_LEVEL_TRACE,	__VA_ARGS__)

#define LOG_LOGGER_DEBUG(logger, ...)	LOG(logger,						LOG_LEVEL_DEBUG,	__VA_ARGS__)
#define LOG_DEBUG(...)					LOG(default_logger_instance(),	LOG_LEVEL_DEBUG,	__VA_ARGS__)

#define LOG_LOGGER_INFO(logger, ...)	LOG(logger,						LOG_LEVEL_INFO,		__VA_ARGS__)
#define LOG_INFO(...)					LOG(default_logger_instance(),	LOG_LEVEL_INFO,		__VA_ARGS__)

#define LOG_LOGGER_WARN(logger, ...)	LOG(logger,						LOG_LEVEL_WARN,		__VA_ARGS__)
#define LOG_WARN(...)					LOG(default_logger_instance(),	LOG_LEVEL_WARN,		__VA_ARGS__)

#define LOG_LOGGER_ERROR(logger, ...)	LOG(logger,						LOG_LEVEL_ERROR,	__VA_ARGS__)
#define LOG_ERROR(...)					LOG(default_logger_instance(),	LOG_LEVEL_ERROR,	__VA_ARGS__)

#define LOG_LOGGER_CRIT(logger, ...)	LOG(logger,						LOG_LEVEL_CRIT,		__VA_ARGS__)
#define LOG_CRIT(...)					LOG(default_logger_instance(),	LOG_LEVEL_CRIT,		__VA_ARGS__)



#ifdef __cplusplus
//}
#endif // __cplusplus
#endif // !LOGGER_H
