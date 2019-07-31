#pragma once
/* Heap Sort Class Header */

#include <vector>
#include <functional>
#include <algorithm>

namespace gm
{
    using Container = std::vector<int>;
    using FuncType = std::function<void()>;

    struct InHouse {};
    struct StdSort {};

    class Heap
    {
    public:
        explicit Heap(const size_t size);
        virtual ~Heap() = default;

        void Print() const;
        void Generate();

        void Resize(const size_t size);

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
        void Heapify(const size_t size, const size_t root);
        long long TimedSort(FuncType func);

        Container m_container;
    };
}
