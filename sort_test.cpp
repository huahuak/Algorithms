#include <gtest/gtest.h>

#include <algorithm>
#include <cstdlib>
#include <random>
#include <utility>
#include <vector>

class Heap {
 public:
  Heap(int *arr, int n) { this->arr = std::vector<int>(arr, arr + n); }

  std::vector<int> sort() {
    std::vector<int> ans;
    while (!arr.empty()) {
      std::swap(arr[0], arr.back());
      ans.push_back(arr.back());
      arr.pop_back();
      sink(0);
    }
    return ans;
  }

  void heapify() {
    for (int i = (arr.size() - 1) / 2; i >= 0; --i) {
      sink(i);
    }
  }

 private:
  void sink(int pos) {
    while (pos < arr.size()) {
      int child = pos * 2 + 1;
      if (child >= arr.size()) {
        return;
      }
      if ((child + 1) < arr.size() && arr[child + 1] < arr[child]) {
        child += 1;
      }
      if (arr[child] < arr[pos]) {
        std::swap(arr[pos], arr[child]);
      } else {
        break;
      }
      pos = child;
    }
    std::vector<int> arr;
  }

  void swim(int pos) {
    while (pos > 0) {
      int parent = pos / 2;
      if (arr[parent] > arr[pos]) {
        std::swap(arr[parent], arr[pos]);
      } else {
        return;
      }
    }
  }

  std::vector<int> arr;
};

// Demonstrate some basic assertions.
TEST(Sort, HeapSort) {
  int N = 10000;
  std::vector<int> arr(N, 0);
  for (int i = 0; i < N; ++i) {
    arr[i] = std::rand();
  }

  Heap hp(arr.data(), arr.size());
  hp.heapify();
  auto ans = hp.sort();
  std::sort(arr.begin(), arr.end());
  EXPECT_EQ(arr, ans);
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
  int N = 10000;
  std::vector<int> arr(N, 0);
  for (int i = 0; i < N; ++i) {
    arr[i] = std::rand();
  }
  std::vector<int> cpy(N, 0);
  std::copy(arr.begin(), arr.end(), cpy.begin());

  quickSort(arr.data(), 0, arr.size());
  std::sort(cpy.begin(), cpy.end());
  EXPECT_EQ(cpy, arr);
}