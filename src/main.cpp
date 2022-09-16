#include "collections/ArraySequence.h"
#include "collections/LinkedListSequence.h"
#include "config.h"
#include "sort/ISort.h"
#include <iostream>
#include <fstream>
#include <memory>
#include "a_load_of_rubish.h"


using namespace std;


int main(int argc, char * const argv[]) {
	Config config(Args(argc, argv));
	ofstream out(config.outputFile);
	auto isort = config.GetSort<int>();
	auto s = new ArraySequence<int>();
	for(size_t i = config.begin; i <= config.end; i += config.step)
	{
		RandomFill(s, i);
		auto f = [&](){isort->sort(s);};
		out << i << "\t" << MeasureExecTime(f) << "\n";
	}
	delete s;
	out.close();
	if(config.needGraph) {
		openPlot(config.outputFile);
	}
	
	//~ auto b = unique_ptr<Sequence<int>>(isort->sort(s.get()));
	//~ std::cout << *b << "\n";
	return 0;
}
