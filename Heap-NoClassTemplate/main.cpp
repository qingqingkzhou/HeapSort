/* Main Application */

/*==================================================
1. Create a gm::Heap class
   - a container holding all the elements in the heap
   - able to initialize the size of the container

2. Create following public member functions
    void Print()
        - Print all the elements in the heap

    void Generate()
        - Randomly generate all the elements in the heap

    void SortInHouse()
        - Implement heap sort mechanism

    void SortUseStd()
        - use std::heap_sort
        (you may use any std sort for comparision)

    void TestSort(const size_t n_trials)
        - Compare the in-house heap sort and std heap sort
        - The same size of array will be used for both in-house and std sort
        - Elements values can be different
        - Run sort() for n_trials time and calculate the average time
        - Display the average time spent on sort()

3. In main()
    - Create a 20 elements heap and verify the correctness of sort()
    - Create a 10000 elements heap and test sort performance

4. Build your project in Debug and Release and analyze
   and explain the performance difference

5. Is there a way to Merge SortInHouse and SortUseStd
   into one unified interface for the user to use?

==================================================== */

#define PRINT_ENABLE

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

    gm::Heap my_heap{ 20 };

    my_heap.Sort<gm::InHouse>();

    PRINT("1. Heap Sort using InHouse implementation\n");
    my_heap.Generate();
    PRINT("\nBefore:\n");
    PRINT(my_heap);

    my_heap.Sort<gm::InHouse>();
    PRINT("After:\n");
    PRINT(my_heap);

    PRINT("2. Heap Sort using std::sort_heap implementation\n");
    PRINT("\nBefore:\n");
    my_heap.Generate();
    PRINT(my_heap);

    my_heap.Sort<gm::StdSort>();
    PRINT("After:\n");
    PRINT(my_heap);

    std::cout << "\n3. Performance Test\n";
    my_heap.Resize(10000);
    std::cout << "\n--- STD Heap Sort ---\n";
    my_heap.TestSort<gm::StdSort>(10);
    std::cout << "--- InHouse Heap Sort ---\n";
    my_heap.TestSort<gm::InHouse>(10);
}
