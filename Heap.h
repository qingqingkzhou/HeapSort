#pragma once
/* Heap Sort Class Header */

#include <vector>
#include <functional>

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
