#pragma once

#include <cassert>

// An array that resizs as it grows past its capacity.
template <class T>
class DynamicArray
{
	T* m_array;
	int m_capacity;
	int m_size;

	typedef T* iterator;

public:

	DynamicArray(int capacity = 1)
	{
		assert(capacity > 0);

		m_array = new T[capacity];
		m_capacity = capacity;
		m_size = 0;
	}

	~DynamicArray()
	{
		delete[] m_array;
		m_array = nullptr;
	}

	// Add an element to the end of the array.
	// Time complexity: O(1) amortized. Worst case: O(N).
	void push(T value)
	{
		if (m_size >= m_capacity)
		{
			// Expand the array if it has reached its limit.
			expandArray();
		}

		m_array[m_size] = value;
		m_size++;
	}

	// Remove an element from the end of the array.
	void pop()
	{
		assert(!empty());
		m_size--;
	}

	// Add an element at a specific index, pushing back the existing element at that index.
	// Remakes the array if the insert is not at the end of the array.
	// Time complexity: O(N).
	void insert(T value, int index)
	{
		assert(validIndex(index));

		if (index == m_size)
		{
			// Push the value if the index is the end of the array.
			push(value);
			return;
		}

		// Resize the array if it has reached its limit.
		int bufferSize = m_capacity;
		if (m_size >= m_capacity)
		{
			bufferSize = m_capacity * 2;
		}

		T* buffer = new T[bufferSize];

		// Add all the elements before the index.
		for (int i = 0; i < index; ++i)
		{
			buffer[i] = m_array[i];
		}

		buffer[index] = value;

		// Add all the elements after the index.
		for (int i = index; i < m_size + 1; ++i)
		{
			buffer[i + 1] = m_array[i];
		}

		delete[] m_array;
		m_array = buffer;
		m_capacity = bufferSize;
		m_size++;
	}

	// Remove an element at a specific index.
	// Remakes the array to fill in the gap if the remove does not occur at the end of the array.
	// Time complexity: O(N).
	void remove(int index)
	{
		assert(validIndex(index));
		assert(!empty());

		if (index == m_size - 1)
		{
			// Pop if the index is at the end of the array.
			pop();
			return;
		}

		T* buffer = new T[m_capacity];

		for (int i = 0; i < index; ++i)
		{
			// Add the elements before the index.
			buffer[i] = m_array[i];
		}

		for (int i = index + 1; i < m_size; ++i)
		{
			// Add the elements before the index.
			buffer[i - 1] = m_array[i];
		}

		delete[] m_array;
		m_array = buffer;
		m_size--;
	}

	// Get the number of elements in the array.
	int size() const
	{
		return m_size;
	}

	// Get the allocated spaces in the array.
	int capacity() const
	{
		return m_capacity;
	}

	bool empty() const
	{
		return m_size == 0;
	}

	// Remove all elements from the array.
	void clear()
	{
		m_size = 0;
	}

	T& operator[](int index)
	{
		assert(validIndex(index));

		return m_array[index];
	}

	T& operator[](int index) const
	{
		assert(validIndex(index));

		return m_array[index];
	}

	// Assignment operator.
	// Time complexity: O(N);
	DynamicArray<T>& operator=(const DynamicArray<T>& other)
	{
		if (this != &other) // Not a self assignment.
		{
			if (m_capacity != other.capacity())
			{
				// Make sure capacity matches.
				delete[] m_array;
				m_array = new T[other.capacity()];
				m_capacity = other.capacity();
			}

			for (int i = 0; i < other.size(); ++i)
			{
				// Copy over data.
				m_array[i] = other[i];
			}

			m_size = other.size();

			return *this;
		}
	}

	iterator begin()
	{
		return &m_array[0];
	}

	iterator end()
	{
		return &m_array[m_size];
	}

private:

	// Creates a new array with double the capacity and copies the old array into the new array.
	void expandArray()
	{
		const int newCapacity = m_capacity * 2;

		T* buffer = new T[newCapacity];

		for (int i = 0; i < m_size; ++i)
		{
			buffer[i] = m_array[i];
		}

		delete[] m_array;
		m_array = buffer;
		m_capacity = newCapacity;
	}

	bool validIndex(int index) const
	{
		return index > -1 && index < m_size;
	}
};