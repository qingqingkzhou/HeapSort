/* Heap Sort Class implementation */

#include <algorithm>
#include <chrono>
#include <iostream>
#include "Heap.h"

namespace gm
{
    Heap::Heap(size_t size) :
        m_container(size)
    {
    }

    void Heap::Resize(const size_t size)
    {
        m_container.resize(size);
    }

    void Heap::Print() const
    {
        std::cout << "Values in the container: \n";
        for (auto v : m_container)
        {
            std::cout << v << " ";
        }
        std::cout << "\n\n";
    }

    void Heap::Generate()
    {
        // Generate Random values
        auto f = []() -> int { return std::rand() % 10000; };

        // Fill up the vector
        std::generate(m_container.begin(), m_container.end(), f);
    }

    void Heap::Heapify(size_t size, size_t root)
    {
        size_t largest{ root };
        size_t left{ 2 * root + 1 };
        size_t right{ 2 * root + 2 };

        // if left child is larger than root
        if (left < size && m_container.at(left) > m_container.at(largest))
            largest = left;

        // if right child is larger than largest so far
        if (right < size && m_container.at(right) > m_container.at(largest))
            largest = right;

        // if largest is not root
        if (largest != root)
        {
            std::swap(m_container.at(root), m_container.at(largest));

            // recursively heapify the affected sub-tree
            Heapify(size, largest);
        }
    }

    template<>
    void Heap::Sort<InHouse>()
    {
        // vector size
        size_t n{ m_container.size() };

        // build max heap
        for (int i = n / 2 - 1; i >= 0; i--)
            Heapify(n, i);

        // one by one extract an element from heap
        for (int i = n - 1; i >= 0; i--)
        {
            // move current root(largest element) to end
            std::swap(m_container[0], m_container[i]);

            // call max heapify on the reduced heap
            Heapify(i, 0);
        }
    }

    template<>
    void Heap::Sort<StdSort>()
    {
        std::make_heap(m_container.begin(), m_container.end());
        std::sort_heap(m_container.begin(), m_container.end());
    }

    void Heap::TestSort(size_t retries)
    {
        int count{ 2 };
        while ( (count--) > 0)
        {
            std::cout << (count ? "Time taken by InHouse\n" :
                                 "Time taken by StdSort\n");

            long long sum{ 0 };
            for (int i = 0; i < retries; i++)
            {
                // Randomly generate values in the vector
                Generate();

                // Find the duration for Sort()
                auto duration{ count ?
                    TimedSort([this] { this->Sort<InHouse>(); }) :
                    TimedSort([this] { this->Sort<StdSort>(); }) };

                std::cout << "Time taken [" << i << "]: "
                          << duration << " microseconds\n";

                sum += duration;
            }
            // Caldulate the average performance
            std::cout << "Time taken [Average]: " <<
                sum / retries << " microseconds\n\n";
        }
    }

    long long Heap::TimedSort(FuncType func)
    {
        using namespace std::chrono;

        // Get starting timepoint
        auto start = high_resolution_clock::now();

        // Call the function
        func();

        // Get ending timepoint
        auto stop = high_resolution_clock::now();

        // Get duration. Substart timepoints to
        // get durarion. To cast it to proper unit
        // use duration cast method
        auto duration = duration_cast<microseconds>(stop - start);

        return duration.count();
    }
}