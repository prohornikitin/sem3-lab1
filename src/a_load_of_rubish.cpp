#include "a_load_of_rubish.h"
#include <cstdlib>
#include <ctime>

static bool srand_init = false;

void RandomFill(Sequence<int>* s, size_t size) {
	if(!srand_init) {
		std::srand(std::time(nullptr));
		srand_init = true;
	}
	
	s->InsertAt(rand(), size-1);
	for(size_t i = 0; i < (size-1); ++i) {
		(*s)[i] = rand();
	}
}

double MeasureExecTime(std::function<void()> f) {
	using std::chrono::high_resolution_clock;
    using std::chrono::duration;
	
	auto t1 = high_resolution_clock::now();
	f();
	auto t2 = high_resolution_clock::now();
	duration<double, std::milli> ms = t2 - t1;
	return ms.count();
}

void openPlot(std::string filePath) {
	auto plot_cmd = "set xlabel 'elements'; set ylabel 'time';plot '" + filePath;
	execlp("gnuplot", "gnuplot", "-p", "-e", plot_cmd.c_str(), NULL);
}
