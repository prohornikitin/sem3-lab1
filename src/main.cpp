#include "collections/ArraySequence.h"
#include "collections/LinkedListSequence.h"
#include "config.h"
#include <iostream>
#include "sort/QuickSort.h"

using namespace std;


int main(int argc, char * const argv[]) {
	Config config(Args(argc, argv));
	auto* s = new ArraySequence<int>({11, 2, 3, 5, 7});
	auto* isort = config.GetSort<int>();
	auto* b = isort->sort(s);
	delete s;
	delete isort;
	std::cout << *b << "\n";
	delete b;
	return 0;
}
