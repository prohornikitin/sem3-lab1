#pragma once
#include <cstddef>
#include "ISort.h"

template <class T>
class ShellSort : public ISort<T> {
public:
	using Comparator = typename ISort<T>::Comparator;
	
	ShellSort(const std::vector<size_t> & gaps)
	{
		this->gaps = gaps;
	}
	
	virtual Sequence<T>* sort(
		const Sequence<T>* seq, 
		Comparator cmp = ISort<T>::cmpDefault
	) override
	{
		Sequence<T>* a = seq->copy();
		for(size_t gap : gaps)
		{
			for (size_t i = gap; i < a->GetLength(); i++)
			{
				T temp = (*a)[i];
				size_t j = i;
				while(j >= gap && cmp(temp, (*a)[j - gap]))
				{
					(*a)[j] = (*a)[j - gap];
					j -= gap;
				}
				(*a)[j] = temp;
			}
		}
		return a;
	}

private:
	std::vector<size_t> gaps;
};
