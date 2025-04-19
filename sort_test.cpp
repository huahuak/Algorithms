#include <_stdlib.h>
#include <alloca.h>
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
    arr[i] = rand() % 100;
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
  if (arr[lhs] > arr[start]) {
    --lhs;
  }
  std::swap(arr[lhs], arr[start]);
  quickSort(arr, start, lhs);
  quickSort(arr, lhs + 1, end);
}

TEST(Sort, QuickSort) {
  testSortMethod([](std::vector<int> &arr) {
    // call quick sort
    quickSort(arr.data(), 0, arr.size());
  });
}

void mergeSort(int *arr, int start, int end) {
  if (end - start < 2) {
    return;
  }
  if (end - start == 2) {
    if (arr[start] > arr[end - 1]) {
      std::swap(arr[start], arr[end - 1]);
    }
    return;
  }
  int mid = (start + end) >> 1;
  mergeSort(arr, start, mid);
  mergeSort(arr, mid, end);
  int lhs = start;
  int rhs = mid;
  int *tmp = (int *)alloca(sizeof(int) * (end - start));
  for (int i = 0; i < end - start; ++i) {
    if (lhs < mid && rhs < end) {
      if (arr[lhs] < arr[rhs]) {
        tmp[i] = arr[lhs];
        ++lhs;
      } else {
        tmp[i] = arr[rhs];
        ++rhs;
      }
    } else if (lhs < mid) {
      tmp[i] = arr[lhs];
      ++lhs;
    } else if (rhs < end) {
      tmp[i] = arr[rhs];
      ++rhs;
    }
  }
  for (int i = 0; i < end - start; ++i) {
    arr[start + i] = tmp[i];
  }
}

TEST(Sort, MergeSort) {
  testSortMethod([](std::vector<int> &arr) {
    // call merge sort
    mergeSort(arr.data(), 0, arr.size());
  });
}

// selectSort
// using swap to implement selectSort, this leads to unsatable sort.
void selectSort(int *arr, int start, int end) {
  for (int i = start; i < end; ++i) {
    int idx = i;
    for (int j = i; j < end; ++j) {
      if (arr[j] < arr[idx]) {
        idx = j;
      }
    }
    std::swap(arr[i], arr[idx]);
  }
}

TEST(Sort, SelectSort) {
  testSortMethod([](std::vector<int> &arr) {
    // select sort
    selectSort(arr.data(), 0, arr.size());
  });
}