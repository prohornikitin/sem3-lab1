#pragma once
#include <string>
#include <optional>
#include <list>
#include <cstring>
#include <vector>
#include <functional>
#include <sstream>


class Args
{
public:
	Args();
	Args(int argc, char * const argv[]);
	~Args();
	bool ParseBool(std::string longName, char shortName = '\0');
	std::optional<std::string> ParseString(std::string longName, char shortName = '\0');
	std::vector<std::string> ParseStrings(std::string longName, char shortName = '\0');
	
	/**
	 * strToT() should throw std::invalid_argument on failure
	 */
	template <class T>
	std::optional<T> ParseCustom(std::function<T(std::string)> strToT, std::string longName, char shortName = '\0')
	{
		auto strOpt = ParseString(longName, shortName);
		if(!strOpt.has_value())
		{
			return {};
		}
		return strToT(strOpt.value());
	}
	
	
	/**
	 * strToT() should throw std::invalid_argument on failure
	 */
	template <class T>
	std::vector<T> ParseCustoms(std::function<T(std::string)> strToT, std::string longName, char shortName = '\0')
	{
		auto strings = ParseStrings(longName, shortName);
		std::vector<T> values(strings.size());
		for(size_t i = 0; i < strings.size(); i++)
		{
			values[i] = strToT(strings[i]);
		}
		return values;
	}
	
	template <class T>
	std::optional<T> ParseCustomWithStream(std::string longName, char shortName)
	{
		auto f = [](std::string s)
		{
			std::stringstream ss;
			ss << s;
			T val;
			ss >> val;
			return val;
		};
		return ParseCustom<T>(f, longName, shortName);
	}
	
	template <class T>
	std::vector<T> ParseCustomsWithStream(std::string longName, char shortName)
	{
		auto f = [](std::string s)
		{
			std::stringstream ss;
			ss << s;
			T val;
			ss >> val;
			return val;
		};
		return ParseCustoms<T>(f, longName, shortName);
	}

	std::optional<int> ParseInt(std::string longName, char shortName);
	std::vector<int> ParseInts(std::string longName, char shortName);

private:
	std::vector<std::string> args;
	
	size_t getValuesStart(std::string longName, char shortName);
};
