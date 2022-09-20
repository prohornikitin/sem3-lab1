#pragma once
#include "ISort.h"
#include <cstddef>

template <class T>
class HeapSort : public ISort<T>
{
public:
	using Comparator = typename ISort<T>::Comparator;
	
	virtual Sequence<T>* Sort(
		const Sequence<T>* seq, 
		Comparator cmp = ISort<T>::cmpDefault
	) override
	{
		auto* b = seq->copy();
		if(b->GetLength() == 0) {
			return b;
		}
		Heapify(b, cmp);
		size_t end = b->GetLength() - 1;
		while (end > 0)
		{
			std::swap((*b)[end], (*b)[0]);
			end--;
			SiftDown(b, 0, end, cmp);
		}
		return b;
	}
	
	virtual std::string Name() override {
		return "HeapSort";
	}

private:
	inline size_t LeftChildI(size_t i)
	{
		return 2*i + 1;
	}
	
	inline size_t RightChildI(size_t i)
	{
		return 2*i + 2;
	}
	
	inline size_t ParentI(size_t i)
	{
		if(i == 0) 
		{
			return 0;
		}
		return (i-1) / 2;
	}
	
	void SiftDown(Sequence<T>* a, size_t start, size_t end, Comparator cmp)
	{
		size_t root = start;
		
		while (LeftChildI(root) <= end)
		{
			size_t child = LeftChildI(root);
			size_t swap = root;
			
			if (cmp((*a)[swap], (*a)[child]))
			{
				swap = child;
			}
			if (child+1 <= end && cmp((*a)[swap], (*a)[child+1]))
			{
				swap = child + 1;
			}
			if (swap == root)
			{
				return;
			} 
			else 
			{
				std::swap((*a)[root], (*a)[swap]);
				root = swap;
			}
		}
	}
	
	void Heapify(Sequence<T>* seq, Comparator cmp)
	{
		size_t start = ParentI(seq->GetLength() - 1);
		while (true)
		{
			SiftDown(seq, start, seq->GetLength() - 1, cmp);
			if(start == 0)
			{
				break;
			}
			start--;
		}
	}
};
