#include "a_load_of_rubish.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int normal_main(Config & config) {
	if(config.check) {
		check(config);
		return 0;
	}
	
	auto sortAlgorithms = config.GetSorts<int>();
	auto seq = config.CreateSequence<int>();
	ofstream out(config.outputFile);
	for(size_t i = config.begin; i <= config.end; i += config.step)
	{
		out << i;
		for(auto& algo : sortAlgorithms) {
			RandomFill(seq.get(), i);
			Sequence<int> * result = nullptr;
			auto f = [&](){result = algo->Sort(seq.get());};
			out << "\t" << MeasureExecTime(f);
			delete result;
		}
		out << "\n";
	}
	out.close();
	
	if(config.needGraph)
	{
		vector<string> names;
		for(auto& algo : sortAlgorithms) {
			names.push_back(algo->Name());
		}
		openPlot(config.outputFile, names);
	}
	return 0;
}

void check(Config & config) {
	auto sortAlgorithms = config.GetSorts<int>();
	auto seq = config.sequenceToCheck.get();
	for(auto& algo : sortAlgorithms) {
		Sequence<int> * result = nullptr;
		auto f = [&](){result = algo->Sort(seq);};
		double elapsedTime = MeasureExecTime(f);
		cout << algo->Name() << "\t";
		cout << *seq << " -> " << *result << "\t";
		cout << elapsedTime << "ms" << "\n";
		delete result;
	}
}


static bool srand_init = false;

void RandomFill(Sequence<int>* s, size_t size)
{
	if(size == 0)
	{
		return;
	}
	
	if(!srand_init)
	{
		srand(time(nullptr));
		srand_init = true;
	}
	
	s->InsertAt(rand() % size, size-1);
	for(size_t i = 0; i < (size-1); ++i)
	{
		(*s)[i] = rand() % size;
	}
}

double MeasureExecTime(std::function<void()> f)
{
	using std::chrono::high_resolution_clock;
    using std::chrono::duration;
	
	auto t1 = high_resolution_clock::now();
	f();
	auto t2 = high_resolution_clock::now();
	duration<double, std::milli> ms = t2 - t1;
	return ms.count();
}

void openPlot(std::string filePath, std::vector<std::string> lineNames)
{
	stringstream cmd;
	cmd << "set xlabel 'items';";
	cmd << "set ylabel 'time, ms';";
	cmd << "plot";
	for(size_t i = 0; i < lineNames.size(); ++i)
	{
		cmd << " '" << filePath << "' using 1:" << std::to_string(i+2);
		cmd << " title '" << lineNames[i] << "' with lines,";
	}
	cmd << ";";
	cmd << "pause -1";
	execlp("gnuplot", "gnuplot", "-e", cmd.str().c_str(), NULL);
}


