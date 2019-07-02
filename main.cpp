/* Main Application */

/*==================================================
1. Create a gm::Heap class
2. Including following public member functions
    void SortInHouse()
        - Implement heap sort mechanism

    void SortUseStd()
        - use std::heap_sort
        (you may use any std sort for comparision)

    void TestSort(const size_t retries)
        - Compare different sort as well as sort
          in std library
        - Run sort on a fixed and same size of array
        - Display the average time spent on sort()

    void Print()
        - Print the elements in an array

    void Resize(const size_t size)
        - Resize the array

    void Generate()
        - use rand() to generate values for array

3. Having a Macro PRINT_ENABLE to turn on and off print
4. Build your project in Debug and Release and analyze
   and explain the performance difference
5. Is there a way to Merge SortInHouse and SortUseStd
   in one unified interface for the user to use (template)
==================================================== */

//#define PRINT_ENABLE

// header files
#include <iostream>
#include "Heap.h"

#ifdef PRINT_ENABLE
    #define PRINT Print
#else
    #define PRINT
#endif

void Print(const gm::Heap& my_heap)
{
    my_heap.Print();
}

void Print(const std::string& text)
{
    std::cout << text.c_str();
}

void main()
{
    std::cout<< "Heap Sort - Qingqing Zhou\n\n";

    gm::Heap my_heap{ 10000 };

    PRINT("Heap Sort using InHouse implementation\n");
    my_heap.Generate();
    PRINT(my_heap);

    my_heap.Sort<gm::InHouse>();
    PRINT(my_heap);

    PRINT("Heap Sort using std::sort_heap implementation\n");
    my_heap.Generate();
    PRINT(my_heap);

    my_heap.Sort<gm::StdSort>();
    PRINT(my_heap);

    std::cout << "Performance Test\n";
    my_heap.TestSort(10);
}
