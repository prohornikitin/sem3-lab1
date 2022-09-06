#pragma once
#include <string>
#include <optional>
#include <list>
#include <cstring>
#include <vector>
#include <functional>


class Args {
public:
	Args();
	Args(int argc, char * const argv[]);
	~Args();
	bool ParseBool(std::string longName, char shortName = '\0');
	std::optional<std::string> ParseString(std::string longName, char shortName = '\0');
	std::vector<std::string> ParseStrings(std::string longName, char shortName = '\0');
	std::optional<long long> ParseLL(std::string longName, char shortName = '\0');
	std::vector<long long> ParseLLs(std::string longName, char shortName = '\0');
	std::optional<unsigned long long> ParseULL(std::string longName, char shortName = '\0');
	std::vector<unsigned long long> ParseULLs(std::string longName, char shortName = '\0');
	
	/**
	 * strToT() should throw std::invalid_argument on failure
	 */
	template <class T>
	std::optional<T> ParseCustom(std::function<T(std::string)> strToT, std::string longName, char shortName = '\0') {
		auto strOpt = ParseString(longName, shortName);
		if(!strOpt.has_value()) {
			return {};
		}
		return strToT(strOpt.value());
	}
	
	
	/**
	 * strToT() should throw std::invalid_argument on failure
	 */
	template <class T>
	std::vector<T> ParseCustoms(std::function<T(std::string)> strToT, std::string longName, char shortName = '\0') {
		auto strings = ParseStrings(longName, shortName);
		std::vector<T> values(strings.size());
		for(size_t i = 0; i < strings.size(); i++) {
			values[i] = strToT(strings[i]);
		}
		return values;
	}

private:
	std::vector<std::string> args;
	
	size_t getValuesStart(std::string longName, char shortName);
};
