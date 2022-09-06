#include "args.h"
#include <string>
#include <optional>
#include <list>
#include <cstring>
#include <vector>

using namespace std;


Args::Args() {
	
}

Args::Args(int argc, char * const argv[])
{
	args.reserve(argc-1);
	for(size_t i = 1; i < (size_t)argc; ++i)
	{
		args.push_back(argv[i]);
	}
}

bool Args::ParseBool(string longName, char shortName)
{
	string longArg = string("--") + longName;
	
	for(size_t i = 0; i < args.size(); i++)
	{
		if ((args[i][0] == '-' && args[i][1] != '-' &&
			args[i].find(shortName) != string::npos) ||
			longArg == args[i])
		{
			return true;
		}
	}
	return false;
}

optional<string> Args::ParseString(string longName, char shortName)
{
	size_t valuesStart = getValuesStart(longName, shortName);
	if (valuesStart == 0 || valuesStart >= args.size())
	{
		return {};
	}
	
	return args[valuesStart];
}

vector<string> Args::ParseStrings(string longName, char shortName)
{
	size_t valuesStart = getValuesStart(longName, shortName);
	if (valuesStart == 0)
	{
		return {};
	}
	
	vector<string> values;
	for(size_t i = valuesStart; i < args.size(); i++)
	{
		if (args[i][0] == '-')
		{
			break;
		}
		values.push_back(args[i]);
	}
	return values;
}

optional<long long> Args::ParseLL(string longName, char shortName)
{
	auto f = [](string s){return stoll(s);};
	return ParseCustom<long long>(f, longName, shortName);
}

vector<long long> Args::ParseLLs(string longName, char shortName)
{
	auto f = [](string s){return stoll(s);};
	return ParseCustoms<long long>(f, longName, shortName);
}

optional<unsigned long long> Args::ParseULL(string longName, char shortName)
{
	auto f = [](string s){return stoull(s);};
	return ParseCustom<unsigned long long>(f, longName, shortName);
}

vector<unsigned long long> Args::ParseULLs(string longName, char shortName)
{
	auto f = [](string s){return stoull(s);};
	return ParseCustoms<unsigned long long>(f, longName, shortName);
}

size_t Args::getValuesStart(string longName, char shortName)
{
	string shortArg = string("-") + shortName;
	string longArg = string("--") + longName;
	
	for(size_t i = 0; i < args.size(); i++)
	{
		if (shortArg == args[i] || longArg == args[i])
		{
			return i + 1;
		}
	}
	return 0;
}


Args::~Args()
{
	
}
