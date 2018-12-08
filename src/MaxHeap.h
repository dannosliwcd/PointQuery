#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <stdexcept>
#include <memory>
#include <cstddef>
#include <utility>

// Max heap.
// Stores elements of type Element in an order that ensures they are extracted
// by decreasing value of Priority.
template<typename Priority, typename Element>
class MaxHeap final
{
public:
	struct Entry
	{
		Element e;
		Priority p;
	};

	// Create a MaxHeap of a given size
	MaxHeap(size_t maxEntries)
		: m_heap(new Entry[maxEntries]), m_maxHeapSize(maxEntries), m_heapSize(0)
	{
	}

	// Build a heap from an unordered array of entries.
	MaxHeap(std::unique_ptr<Entry[]>&& h, size_t count)
		: m_heap(std::move(h)), m_maxHeapSize(count), m_heapSize(count)
	{
		for (int i = count / 2; i >= 0; --i) {
			DownHeap(i);
		}
	}

	MaxHeap(MaxHeap&) = delete;
	MaxHeap& operator=(MaxHeap&) = delete;
	~MaxHeap() = default;

	// Get the entry in the heap with the greatest priority
	Entry GetMax() const
	{
		if (m_heapSize == 0) {
			throw std::out_of_range("Attempted to remove from empty MaxHeap");
		}
		return m_heap[0];
	}

	// Remove the heap entry that has the greatest priority
	void RemoveMax()
	{
		if (m_heapSize == 0) {
			throw std::out_of_range("Attempted to remove from empty MaxHeap");
		}
		std::swap(m_heap[0], m_heap[--m_heapSize]);
		DownHeap(0);
	}

	// Insert an entry to the heap with a given priority
	void Insert(Priority priority, Element item)
	{
		if (m_heapSize >= m_maxHeapSize)
		{
			throw std::length_error("inserting into full heap");
		}
		
		m_heap[m_heapSize] = Entry{item, priority};
		UpHeap(m_heapSize++);
	}

	// Check whether the heap is empty
	bool IsEmpty() const
	{
		return (m_heapSize == 0);
	}

	// Check whether the heap is full
	bool IsFull() const
	{
		return (m_heapSize == m_maxHeapSize);
	}

	// Return the count of elements in the heap
	size_t GetSize() const
	{
		return m_heapSize;
	}

private:
	// Move a heap entry closer to the root, if possible
	void UpHeap(int fromIndex)
	{
		while (m_heap[fromIndex].p > m_heap[GetParentIndex(fromIndex)].p)
		{
			auto parentIndex = GetParentIndex(fromIndex);
			std::swap(m_heap[fromIndex], m_heap[parentIndex]);
			fromIndex = parentIndex;
		}
	}

	// Move a heap entry further from the root, if possible
	void DownHeap(size_t root)
	{
		size_t greaterChild;
		while (root < m_heapSize
				&& (greaterChild = GetGreaterChildIndex(root)) < m_heapSize
				&& (m_heap[greaterChild].p > m_heap[root].p)) {
			std::swap(m_heap[greaterChild], m_heap[root]);
			root = greaterChild;
		}
	}

	// Return the index of greater-prioritized child of the given parent
	size_t GetGreaterChildIndex(size_t parent) const
	{
		auto greaterChild = GetLeftIndex(parent);
		auto rightChild = GetNextSiblingIndex(greaterChild);
		if (rightChild < m_heapSize) {
			if (m_heap[rightChild].p > m_heap[greaterChild].p) {
				greaterChild = rightChild;
			}
		}
		return greaterChild;
	}

	// Return the index of the left child of the given node
	size_t GetLeftIndex(size_t x) const
	{
		return 2 * x + 1;
	}

	// Return the index of the next node after the given node
	size_t GetNextSiblingIndex(size_t x) const
	{
		return x + 1;
	}

	// Return the index of the given node's parent
	size_t GetParentIndex(size_t x) const
	{
		return (x == 0) ? 0 : (x - 1) / 2;
	}

	std::unique_ptr<Entry[]> m_heap;
	std::size_t m_maxHeapSize;
	std::size_t m_heapSize;
};

#endif //MAXHEAP_H
