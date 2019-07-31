# HeapSort
Implementation using C++ for Heap Sort. Based on the lecture from MIT Algorithm 6.006 - 4



### 1. Create a `gm::Heap` class
   - a container holding all the elements in the heap
   - able to initialize the size of the container

### 2. Create following public member functions

`void Print()`
- Print all the elements in the heap

`void Generate()`
- Randomly generate all the elements in the heap

`void SortInHouse()`
- Implement heap sort mechanism

`void SortUseStd()`
- use std::heap_sort (you may use any std sort for comparision)

`void TestSort(const size_t n_trials)`
  - Compare the in-house heap sort and std heap sort
  - The same size of array will be used for both in-house and std sort
  - Elements values can be different
  - Run sort() for n_trials time and calculate the average time
  - Display the average time spent on sort()


### 3. In `main()`
 - Create a 20 elements heap and verify the correctness of sort()
 - Create a 10000 elements heap and test sort performance


### 4. Build your project in Debug and Release and analyze and explain the performance difference


### 5. Is there a way to Merge SortInHouse and SortUseStd into one unified interface for the user to use?

### Solution:
 - Use templated member function to implement Sort() for InHouse and StdSort `Heap-NoClassTemplate`
 - VC++ and g++ have different requirement and tolerance on the *explicit specilization in non-namespace scop* of a templated member function in a templated class
 - As an experiment, there are two implementation to show the workaround on g++ `Heap-ClassTemplate-g++`, `Heap-ClassTemplate-VC++`
 - The suggested implementation <a href="https://stackoverflow.com/questions/3052579/explicit-specialization-in-non-namespace-scope">here</a> also works.
 
