#pragma once

#include <collections/Sequence.h>
#include <chrono>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <config.h>


void RandomFill(Sequence<int>* s, size_t size);

double MeasureExecTime(std::function<void()> f);

void openPlot(std::string filePath, std::vector<std::string> lineNames);

int normal_main(Config & config);

void check(Config & config);
