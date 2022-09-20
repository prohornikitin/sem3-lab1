#pragma once
#include <cstddef>
#include "ISort.h"


template <class T>
class QuickSort : public ISort<T>
{
public:
	using Comparator = typename ISort<T>::Comparator;
	
	virtual Sequence<T>* Sort(
		const Sequence<T>* seq,
		Comparator cmp = ISort<T>::cmpDefault
	) override
	{
		Sequence<T>* a = seq->copy();
		if(a->GetLength() == 0) {
			return a;
		}
		Recursive(a, 0, seq->GetLength()-1, cmp);
		return a;
	}
	
	virtual std::string Name() override {
		return "QuickSort";
	}

private:
	size_t Partition(Sequence<T>* seq, size_t first, size_t last, Comparator cmp)
	{
		auto pivot = (*seq)[(first + last)/2];
		size_t i = first;
		size_t j = last;
		while (true)
		{
			while (cmp((*seq)[i], pivot))
			{
				i++;
			}
			while (cmp(pivot, (*seq)[j]))
			{
				j--;
			}
			
			if (i >= j)
			{
				return j;
			}
			
			std::swap((*seq)[i], (*seq)[j]);
			i++;
			j--;
		}
	}

	void Recursive(Sequence<T>* a, size_t first, size_t last, Comparator cmp)
	{
		if (first < last)
		{
			auto pivot = Partition(a, first, last, cmp);
			Recursive(a, first, pivot, cmp);
			Recursive(a, pivot + 1, last, cmp);
		}
	}
};
