#include <algorithm>
#include <cstdlib>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

void testSearch(std::function<int(std::vector<int>, int)> searchFn) {
  int N = 10000;
  std::vector<int> arr(N, 0);
  for (int i = 0; i < arr.size(); ++i) {
    arr[i] = rand();
  }
  std::sort(arr.begin(), arr.end());

  const int testN = 100;
  for (int i = 0; i < testN; ++i) {
    int idx = rand() % arr.size();
    int ans = searchFn(arr, arr[idx]);
    EXPECT_EQ(ans, idx);
  }
}

int binaraySearch(std::vector<int> arr, int target) {
  int lhs = 0;
  int rhs = arr.size();
  while (lhs <= rhs) {
    int mid = (lhs + rhs) >> 1;
    if (arr[mid] == target) {
      return mid;
    }
    if (arr[mid] < target) {
      lhs = mid + 1;
    } else {
      rhs = mid - 1;
    }
  }
  return -1;
};

TEST(Search, BinaraySearch) { testSearch(binaraySearch); }