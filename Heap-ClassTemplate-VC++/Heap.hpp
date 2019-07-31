#pragma once
/* Heap Sort Class Header */

#include <chrono>
#include <vector>
#include <functional>
#include <algorithm>

namespace gm
{
    using Container = std::vector<int>;
    using FuncType = std::function<void()>;

    struct InHouse {};
    struct StdSort {};

    template<class T>
    class Heap
    {
    public:
        explicit Heap(const size_t size) : m_container(size)
        {}

        virtual ~Heap() = default;

        void Print() const
        {
            std::cout << "Container[" << m_container.size() << "]: \n";
            for (auto v : m_container)
            {
                std::cout << v << " ";
            }
            std::cout << "\n\n";
        }

        void Generate()
        {
            // Generate Random values
            auto f = []() -> int { return std::rand() % 10000; };

            // Fill up the vector
            std::generate(m_container.begin(), m_container.end(), f);
        }

        void Resize(const size_t size)
        {
            m_container.resize(size);
        }

        template<class SortType>
        void Sort();

        template<>
        void Sort<InHouse>()
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
        void Sort<StdSort>()
        {
            std::make_heap(m_container.begin(), m_container.end());
            std::sort_heap(m_container.begin(), m_container.end());
        }

        template<class SortType>
        void TestSort(const size_t n_trials)
        {
            long long sum{ 0 };
            for (int i = 0; i < n_trials; i++)
            {
                // Randomly generate values in the vector
                Generate();

                // Find the duration for Sort()
                sum += TimedSort([this] { this->Sort<SortType>(); });
            }
            // Caldulate the average performance
            std::cout << "Time taken [Average]: " <<
                sum / n_trials << " microseconds\n\n";
        }

    private:
        void Heapify(const size_t size, const size_t root)
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

        long long TimedSort(FuncType func)
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

        Container m_container;
    };
}
