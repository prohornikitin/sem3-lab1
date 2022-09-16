#include "config.h"
#include <stdexcept>
#include <iostream>

using namespace std;
using Sort = Config::Sort;


Config::Config() {
	
}

Config::Config(Args raw) {
	Parse(raw);
}

static Sort strToSort(std::string str) {
	if(str == "quick") {
		return Sort::Quick;
	}
	if(str == "shell") {
		return Sort::Shell;
	}
	if(str == "heap") {
		return Sort::Heap;
	}
	throw invalid_argument("Can't Parse sort algorithm. Can be 'heap', 'shell' or 'quick'");
}

void Config::Parse(Args raw) {
	auto outputFileOpt = raw.ParseString("output", 'o');
	if(outputFileOpt.has_value()) {
		outputFile = outputFileOpt.value();
	} else {
		outputFile = "/tmp/sem3-lab1-tmp";
		needGraph = true;
	}
	
	
	auto sortOpt = raw.ParseCustom<Sort>(strToSort, "algorithm", 'a');
	if (!sortOpt.has_value()) {
		std::cerr << "Error. No sort algorithm specified. Can be 'heap', 'shell' or 'quick'\n";
		exit(1);
	}
	sort = sortOpt.value();
	
	if(sort == Sort::Shell) {
		gaps = raw.ParseCustomsWithStream<size_t>("gaps", 'g');
		std::sort(gaps.begin(), gaps.end(), greater<unsigned long long>());
		if (gaps.size() == 0) {
			gaps = {701, 301, 132, 57, 23, 10, 4, 1};
		}
		if(gaps.back() != 1) {
			gaps.push_back(1);
		}
	}
	
	auto range = raw.ParseCustomsWithStream<size_t>("range", 'r');
	if(range.size() == 0) {
		std::cerr << "Error. No size range specified.\n";
		exit(1);
	}
	if(range.size() != 3) {
		std::cerr << "Error. Range should have format 'begin, end, step'\n";
		exit(1);
	}
	begin = range[0];
	end = range[1];
	step = range[2];
}
