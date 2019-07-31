/* Heap Sort Class implementation */


#include <chrono>
#include <iostream>
#include "Heap.h"

namespace gm
{
    Heap::Heap(const size_t size) :
        m_container(size)
    {
    }

    void Heap::Print() const
    {
        std::cout << "Container["<< m_container.size() <<"]: \n";
        for (auto v : m_container)
        {
            std::cout << v << " ";
        }
        std::cout << "\n\n";
    }

    void Heap::Resize(const size_t size)
    {
        m_container.resize(size);
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

        std::cout << "Time taken: " << duration.count() << " microseconds\n";

        return duration.count();
    }
}
