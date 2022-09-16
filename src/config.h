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
#include <memory>


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
	std::unique_ptr<ISort<T>> GetSort() {
		switch(sort) {
		case Sort::Heap:
			return std::make_unique<HeapSort<T>>();
		case Sort::Quick:
			return std::make_unique<QuickSort<T>>();
		case Sort::Shell:
			return std::make_unique<ShellSort<T>>(gaps);
		default:
			return nullptr; //unreachable
		};
	}
	
	size_t begin;
	size_t end;
	size_t step;
	
	std::string outputFile;
	bool needGraph = false;
	
private:
	Sort sort;
	
	std::vector<size_t> gaps;
	
	
	
	void Parse(Args raw);
	
	
};
