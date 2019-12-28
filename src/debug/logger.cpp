
#define LOG_ACTIVE_LEVEL LOG_LEVEL_TRACE
#include "logger.h"

typedef struct arg_struct {
	uint32_t level;
	char* str;
} arg_struct;

//void thread_log(void* arg) {
//	LOG(default_logger_instance(), ((arg_struct*)arg)->level, ((arg_struct*)arg)->str);
//}


int main() {
	spdlog::set_level(spdlog::level::level_enum::trace);
	init_default_logger();
	///thread_t t0, t1, t2, t3, t4, t5;

	arg_struct* a0 = (arg_struct*) malloc(sizeof(arg_struct));
	arg_struct* a1 = (arg_struct*) malloc(sizeof(arg_struct));
	arg_struct* a2 = (arg_struct*) malloc(sizeof(arg_struct));
	arg_struct* a3 = (arg_struct*) malloc(sizeof(arg_struct));
	arg_struct* a4 = (arg_struct*) malloc(sizeof(arg_struct));
	//arg_struct* a5 = (arg_struct*) malloc(sizeof(arg_struct));

	a0->level = LOG_LEVEL_CRIT; a0->str = "Thread 0";
	a1->level = LOG_LEVEL_INFO; a1->str = "Thread 1";
	a2->level = LOG_LEVEL_WARN; a2->str = "Thread 2";
	a3->level = LOG_LEVEL_DEBUG; a3->str = "Thread 3";
	a4->level = LOG_LEVEL_CRIT; a4->str = "Thread 4";
	//a5->level = LOG_LEVEL_WARN; a5->str = "Thread 5";

	//arg_struct a5 = { LOG_LEVEL_WARN, "Thread 5" };

	//thread_create(&t0, thread_log, (void*)a0);
	//thread_create(&t1, thread_log, (void*)a1);
	//thread_create(&t2, thread_log, (void*)a2);
	//thread_create(&t3, thread_log, (void*)a3);
	//thread_create(&t4, thread_log, (void*)a4);
	//thread_create(&t5, thread_log, (void*)&a5);

	LOG_CRIT("Works");
	LOG_DEBUG("Debugging!");
	LOG_TRACE("Trace this!");


	//thread_join(t0, NULL);
	//thread_join(t1, NULL);
	//thread_join(t2, NULL);
	//thread_join(t3, NULL);
	//thread_join(t4, NULL);
	//thread_join(t5, NULL);
}