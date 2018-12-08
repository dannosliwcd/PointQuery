#include "MaxHeap.h"
#include <catch.hpp>
#include <string>

TEST_CASE("single entry heap")
{
	MaxHeap<int, int> heap(1);
	REQUIRE(heap.IsEmpty());

	heap.Insert(1, 1);
	REQUIRE_FALSE(heap.IsEmpty());

	REQUIRE(heap.IsFull());
	REQUIRE_THROWS(heap.Insert(1, 1));

	REQUIRE(heap.GetMax().e == 1);
	REQUIRE_FALSE(heap.IsEmpty());

	heap.RemoveMax();
	REQUIRE(heap.IsEmpty());

	REQUIRE_THROWS(heap.RemoveMax());
}

TEST_CASE("heap order")
{
	MaxHeap<int, std::string> heap(5);
	REQUIRE(heap.GetSize() == 0);
	heap.Insert(5, "Five");
	REQUIRE(heap.GetSize() == 1);
	heap.Insert(3, "Three");
	heap.Insert(8, "Eight");
	heap.Insert(30, "Thirty");
	heap.Insert(1, "One");
	REQUIRE(heap.IsFull());
	REQUIRE(heap.GetSize() == 5);

	REQUIRE(heap.GetMax().e == "Thirty");
	heap.RemoveMax();
	REQUIRE(heap.GetSize() == 4);
	REQUIRE(heap.GetMax().e == "Eight");
	heap.RemoveMax();
	REQUIRE(heap.GetMax().e == "Five");
	heap.RemoveMax();
	REQUIRE(heap.GetMax().e == "Three");
	heap.RemoveMax();
	REQUIRE(heap.GetMax().e == "One");
	heap.RemoveMax();
	REQUIRE(heap.IsEmpty());
}
