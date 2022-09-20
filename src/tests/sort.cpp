#include <sort/ISort.h>
#include <sort/QuickSort.h>
#include <sort/HeapSort.h>
#include <sort/ShellSort.h>
#include <collections/ArraySequence.h>
#include <memory>
#include <gtest/gtest.h>

using std::unique_ptr;
using std::make_unique;


static void TestSorted(ISort<int> * s) {
	ArraySequence<int> seq = {0,1,2,3,4,5,6,7,8,9};
	auto sorted = unique_ptr<Sequence<int>>(s->Sort(&seq));
	ASSERT_EQ(*sorted, seq);
}

static void TestUnsorted(ISort<int> * s) {
	ArraySequence<int> seq = {9,8,7,1,5,3,4,2,6,0};
	auto sorted = unique_ptr<Sequence<int>>(s->Sort(&seq));
	ArraySequence<int> expected = {0,1,2,3,4,5,6,7,8,9};
	ASSERT_EQ(*sorted, expected);
}

TEST(HeapSort, Unsorted) {
	TestUnsorted(make_unique<HeapSort<int>>().get());
}
TEST(HeapSort, Sorted) {
	TestSorted(make_unique<HeapSort<int>>().get());
}
TEST(QuickSort, Unsorted) {
	TestUnsorted(make_unique<QuickSort<int>>().get());
}
TEST(QuickSort, Sorted) {
	TestSorted(make_unique<QuickSort<int>>().get());
}
TEST(ShellSort, Unsorted) {
	TestUnsorted(make_unique<ShellSort<int>>().get());
}
TEST(ShellSort, Sorted) {
	TestSorted(make_unique<ShellSort<int>>().get());
}
