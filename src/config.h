#pragma once

#include <vector>
#include <string>
#include "args/args.h"
#include <collections/Sequence.h>
#include <functional>
#include "sort/ISort.h"
#include "sort/QuickSort.h"
#include "sort/HeapSort.h"
#include "sort/ShellSort.h"


class Config {
public:
	Config();
	Config(Args raw);
	
	enum class Sort {
		Quick,
		Shell,
		Heap,
	};
	
	
	
	template <class T>
	ISort<T>* GetSort() {
		switch(sort) {
		case Sort::Heap:
			return new HeapSort<T>();
		case Sort::Quick:
			return new QuickSort<T>();
		case Sort::Shell:
			return new ShellSort<T>(gaps);
		default:
			return nullptr; //unreachable
		};
	}
	
private:
	Sort sort;
	
	
	
	std::vector<size_t> gaps;
	std::string outputFile;
	bool needGraph = false;
	
	
	void Parse(Args raw);
	
	
};
