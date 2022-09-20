#pragma once
#include <collections/Sequence.h>

template <class T>
class ISort
{
public:
	using Comparator = std::function<int(const T&, const T&)>;
	
	virtual Sequence<T>* Sort(const Sequence<T>*, Comparator cmp = cmpDefault) = 0;
	
	virtual ~ISort() = default;
	
	virtual std::string Name() {
		return "undefined";
	}
private:
	static Comparator cmpDefault;
};

template<class T>
typename ISort<T>::Comparator ISort<T>::cmpDefault = [](const T& a, const T& b){return a < b;};
