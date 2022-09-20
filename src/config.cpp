#include "config.h"
#include <stdexcept>
#include <iostream>

using namespace std;
using Sort = Config::Sort;
using SequenceType = Config::SequenceType;


Config::Config(Args args) : raw(args)
{
	Parse();
}

static Sort StrToSort(std::string str)
{
	if(str == "quick")
	{
		return Sort::Quick;
	}
	if(str == "shell")
	{
		return Sort::Shell;
	}
	if(str == "heap")
	{
		return Sort::Heap;
	}
	throw invalid_argument("Can't Parse sort algorithm. Can be 'heap', 'shell' or 'quick'");
}

static SequenceType StrToSequenceType(std::string str)
{
	if(str == "array")
	{
		return SequenceType::Array;
	}
	if(str == "list")
	{
		return SequenceType::List;
	}
	throw invalid_argument("Can't Parse sequence type. Can be 'list' or 'array'");
}

void Config::ParseSequenceType()
{
	auto sequenceTypeOpt = raw.ParseCustom<SequenceType>(
		StrToSequenceType, "sequence-type", 's'
	);
	
	if(sequenceTypeOpt.has_value()) 
	{
		sequenceType = sequenceTypeOpt.value();
	}
	else
	{
		cerr << "Error. No sequence type specified. Can be 'list' or 'array'\n";
		exit(1);
	}
}

void Config::ParseAlgorithms() 
{
	auto sorts_vec = raw.ParseCustoms<Sort>(StrToSort, "algorithm", 'a');
	sorts = std::set(sorts_vec.begin(), sorts_vec.end());
	if (sorts.empty())
	{
		cerr << "Error. No sort algorithm specified. Can be 'heap', 'shell' or 'quick'\n";
		exit(1);
	}
	
	if(sorts.contains(Sort::Shell))
	{
		gaps = raw.ParseCustomsWithStream<size_t>("gaps", 'g');
		std::sort(gaps.begin(), gaps.end(), greater<size_t>());
		if (gaps.size() == 0)
		{
			gaps = {701, 301, 132, 57, 23, 10, 4, 1};
		}
		if(gaps.back() != 1)
		{
			gaps.push_back(1);
		}
	}
}

void Config::ParseOutput()
{
	auto outputFileOpt = raw.ParseString("output", 'o');
	needGraph = !outputFileOpt.has_value();
	outputFile = outputFileOpt.value_or("/tmp/sem3-lab1-tmp");
}

void Config::ParseRange()
{
	auto range = raw.ParseCustomsWithStream<size_t>("range", 'r');
	if(range.size() == 0)
	{
		std::cerr << "Error. No size range specified.\n";
		exit(1);
	}
	if(range.size() != 3)
	{
		std::cerr << "Error. Range should have format 'begin, end, step'\n";
		exit(1);
	}
	
	begin = range[0];
	end = range[1];
	step = range[2];
}

void Config::ParseCheck() 
{
	auto values = raw.ParseInts("check", 'c');
	sequenceToCheck = CreateSequence<int>();
	for(auto & i : values) 
	{
		sequenceToCheck->Append(i);
	}
	check = (sequenceToCheck->GetLength() != 0);
}

void Config::Parse()
{
	help = raw.ParseBool("help", 'h');
	test = raw.ParseBool("test", 't');
	if(help || test)
	{
		return;
	}
	
	ParseSequenceType();
	ParseAlgorithms();
	
	ParseCheck();
	if(check) {
		return;
	}
	
	
	ParseOutput();
	ParseRange();
}



static void PrintOneArgHelp(const char* descr, const char* lname, char sname='\0')
{
	if(sname == '\0')
	{
		printf("   --%-20s %s\n", lname, descr);
	}
	else
	{
		printf("-%c, --%-20s %s\n", sname, lname, descr);
	}
}

void Config::PrintHelp()
{
	printf("Usage: exec [OPTIONS]\n");
	printf("This program tests sort algorithms on diffirent sequence sizes.\n");
	PrintOneArgHelp("print this help", "help", 'h');
	PrintOneArgHelp("run unit tests (located in ./src/test/**)", "test", 't');
	PrintOneArgHelp("type of sequence (list, array)", "sequence-type", 's');
	PrintOneArgHelp("tested sort algorithms (heap, shell, quick)", "algorithms", 'a');
	PrintOneArgHelp("sequence length range, as follows 'MIN MAX STEP'", "range", 'r');
	PrintOneArgHelp("output file(if unspecified plot will be built)", "output", 'o');
	PrintOneArgHelp("gaps for shell sort(default is '701 301 132 57 23 10 4 1')", "gaps", 'g');
	PrintOneArgHelp("checks sort correctness on a given sequence", "check", 'c');
}
