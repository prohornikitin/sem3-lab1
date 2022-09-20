#pragma once

#include <vector>
#include <string>
#include <args/args.h>
#include <collections/Sequence.h>
#include <collections/LinkedListSequence.h>
#include <collections/ArraySequence.h>
#include <functional>
#include <sort/ISort.h>
#include <sort/QuickSort.h>
#include <sort/HeapSort.h>
#include <sort/ShellSort.h>
#include <memory>
#include <set>


class Config
{
public:
	Config(Args raw);
	
	enum class Sort
	{
		Quick,
		Shell,
		Heap,
	};
	
	enum class SequenceType
	{
		List,
		Array
	};
	
	/**
	 *  returned set is guarteed not to be-empty;
	 */
	template <class T>
	std::set<std::unique_ptr<ISort<T>>> GetSorts() 
	{
		std::set<std::unique_ptr<ISort<T>>> result;
		for(auto sort : sorts) {
			switch(sort)
			{
			case Sort::Heap:
				result.insert(std::make_unique<HeapSort<T>>()); 
				break;
			case Sort::Quick:
				result.insert(std::make_unique<QuickSort<T>>());
				break;
			case Sort::Shell:
				result.insert(std::make_unique<ShellSort<T>>(gaps));
				break;
			};
		}
		return result;
	}
	
	template <class T>
	std::unique_ptr<Sequence<int>> CreateSequence()
	{
		switch(sequenceType)
		{
		case SequenceType::Array:
			return std::make_unique<ArraySequence<T>>();
		case SequenceType::List:
			return std::make_unique<LinkedListSequence<T>>();
		default:
			return nullptr; //unreachable
		}
	}
	
	size_t begin;
	size_t end;
	size_t step;
	
	std::string outputFile;
	bool needGraph = false;
	
	bool help = false;
	bool test = false;
	bool check = false;
	
	std::unique_ptr<Sequence<int>> sequenceToCheck;
	
	void PrintHelp();
private:
	Args raw;

	std::set<Sort> sorts;
	SequenceType sequenceType;
	
	std::vector<size_t> gaps;
	
	void Parse();
	void ParseSequenceType();
	void ParseAlgorithms();
	void ParseOutput();
	void ParseRange();
	void ParseCheck();
};
