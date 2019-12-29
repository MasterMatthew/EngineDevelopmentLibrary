
#define SPDLOG_ACTIVE_LEVEL 0

#include <iostream>
#include <string>
#include <sstream>

#include "logger.h"
#include "spdlog/spdlog.h"
#include "spdlog/details/log_msg.h"
#include "spdlog/details/backtracer.h"

#define LOG_LEVEL_ENUM { \
spdlog::level::level_enum::trace, \
spdlog::level::level_enum::debug, \
spdlog::level::level_enum::info, \
spdlog::level::level_enum::warn, \
spdlog::level::level_enum::err, \
spdlog::level::level_enum::critical \
}
static spdlog::level::level_enum log_level_enum[6] = LOG_LEVEL_ENUM;

//A wrapper for spdlog to maintain C portability
void debug_log(void* logger, uint32_t level, char* fmt, ...) {
	spdlog::set_level(spdlog::level::level_enum::trace);
	spdlog::logger* logger_ptr = (spdlog::logger*) logger;
	spdlog::level::level_enum level_enum = log_level_enum[level];

	va_list args; va_start(args, fmt);
	int size = 1 + vsnprintf(NULL, 0, fmt, args);
	char* msg = (char*) malloc(size * sizeof(char));
	vsnprintf(msg, size, fmt, args);
	va_end(args);

	logger_ptr->log(level_enum, msg);
	free(msg);
}

void* default_logger_instance() { return spdlog::default_logger_raw(); }


/*
#define LOG_ACTIVE_LEVEL LOG_LEVEL_TRACE
#include "logger.h"

typedef struct arg_struct {
	spdlog::level::level_enum level;
	char* str;
} arg_struct;

void thread_log(void* arg) {
	LOG(default_logger_instance(), ((arg_struct*)arg)->level, ((arg_struct*)arg)->str);
}


int main() {
	spdlog::set_level(spdlog::level::level_enum::trace);
	init_default_logger();

	arg_struct* a0 = (arg_struct*) malloc(sizeof(arg_struct));
	arg_struct* a1 = (arg_struct*) malloc(sizeof(arg_struct));
	arg_struct* a2 = (arg_struct*) malloc(sizeof(arg_struct));
	arg_struct* a3 = (arg_struct*) malloc(sizeof(arg_struct));
	arg_struct* a4 = (arg_struct*) malloc(sizeof(arg_struct));
	arg_struct* a5 = (arg_struct*) malloc(sizeof(arg_struct));

	a0->level = LOG_ENUM_CRIT; a0->str = "Thread 0";
	a1->level = LOG_ENUM_INFO; a1->str = "Thread 1";
	a2->level = LOG_ENUM_WARN; a2->str = "Thread 2";
	a3->level = LOG_ENUM_DEBUG; a3->str = "Thread 3";
	a4->level = LOG_ENUM_CRIT; a4->str = "Thread 4";
	a5->level = LOG_ENUM_WARN; a5->str = "Thread 5";

	std::thread t0(thread_log, (void*)a0);
	std::thread t1(thread_log, (void*)a1);
	std::thread t2(thread_log, (void*)a2);
	std::thread t3(thread_log, (void*)a3);
	std::thread t4(thread_log, (void*)a4);
	std::thread t5(thread_log, (void*)a5);

	LOG_CRIT("Works");
	LOG_DEBUG("Debugging!");
	LOG_TRACE("Trace this!");

	t0.join();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
}
*/