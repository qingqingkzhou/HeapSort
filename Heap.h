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

        template<class Type>
        void Sort();

        void TestSort(const size_t retries);

        /* function to print array of size n */
        void Print() const;

        void Resize(const size_t size);
        void Generate();

    private:
        long long TimedSort(FuncType func);
        void Heapify(const size_t size, const size_t root);

        Container m_container;
    };
}
