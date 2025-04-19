#include <_stdlib.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <utility>
#include <vector>

void testSortMethod(std::function<void(std::vector<int> &)> sortFn) {
  const int N = 10000;
  std::vector<int> arr(N, 0);
  for (int i = 0; i < arr.size(); ++i) {
    arr[i] = rand();
  }
  std::vector<int> cpy(arr);
  sortFn(cpy);
  std::sort(arr.begin(), arr.end());
  EXPECT_EQ(arr, cpy);
}

class Heap {
 public:
  explicit Heap(std::vector<int> &arr) {
    this->arr = arr.data();
    this->size = arr.size();
    heapify();
  }

  static void sort(std::vector<int> &arr) {
    Heap h(arr);
    for (int i = arr.size() - 1; i >= 0; --i) {
      std::swap(arr[0], arr[i]);
      h.sink(0, 0, i);
    }
    int lhs = 0;
    int rhs = arr.size() - 1;
    while (lhs < rhs) {
      std::swap(arr[lhs], arr[rhs]);
      ++lhs;
      --rhs;
    }
  };

  void heapify() {
    for (int i = (size - 1) / 2; i >= 0; --i) {
      sink(i, 0, size);
    }
  }

 private:
  void sink(int pos, int start, int end) {
    while (pos < end) {
      int child = pos * 2 + 1;
      if (child >= end) {
        return;
      }
      if ((child + 1) < end && arr[child + 1] < arr[child]) {
        child += 1;
      }
      if (arr[child] < arr[pos]) {
        std::swap(arr[pos], arr[child]);
      } else {
        break;
      }
      pos = child;
    }
  }

  void swim(int pos, int start, int end) {
    while (pos > start) {
      int parent = pos / 2;
      if (parent < start) {
        break;
      }
      if (arr[parent] > arr[pos]) {
        std::swap(arr[parent], arr[pos]);
      } else {
        break;
      }
      pos = parent;
    }
  }

  int *arr;
  int size;
};

// Demonstrate some basic assertions.
TEST(Sort, HeapSort) {
  testSortMethod([](std::vector<int> &arr) {
    // heap sort
    Heap::sort(arr);
  });
}

// arr is [start, end)
void quickSort(int *arr, int start, int end) {
  if (end - start < 2) {
    return;
  }
  int pivot = arr[start];
  int lhs = start;
  int rhs = end - 1;
  while (lhs < rhs) {
    while (lhs < rhs && arr[lhs] <= pivot) {
      lhs++;
    }
    while (rhs > lhs && arr[rhs] > pivot) {
      rhs--;
    }
    std::swap(arr[lhs], arr[rhs]);
  }
  if (arr[lhs] < arr[start]) {
    std::swap(arr[lhs], arr[start]);
  } else {
    --lhs;
    std::swap(arr[lhs], arr[start]);
  }
  quickSort(arr, start, lhs);
  quickSort(arr, lhs + 1, end);
}

TEST(Sort, QuickSort) {
  testSortMethod([](std::vector<int> &arr) {
    // call quick sort
    quickSort(arr.data(), 0, arr.size());
  });
}

void mergeSort(int *arr, int start, int end) {}
