// Copyright 2026 Khaferl Pavel

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <utility>
#include "lib_double_list/double_list.h"

TEST(DoubleListTest, Initialization) {
  Double_List<int> list;
  EXPECT_EQ(list.get_size(), 0);
  EXPECT_TRUE(list.is_empty());
}

TEST(DoubleListTest, PushFrontAndPopFront) {
  Double_List<int> list;
  list.push_front(10);
  list.push_front(20);
  list.push_front(30);

  EXPECT_EQ(list.get_size(), 3);
  EXPECT_EQ(list.pop_front(), 30);
  EXPECT_EQ(list.pop_front(), 20);
  EXPECT_EQ(list.pop_front(), 10);
  EXPECT_TRUE(list.is_empty());
}

TEST(DoubleListTest, PushBackAndPopBack) {
  Double_List<int> list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);

  EXPECT_EQ(list.get_size(), 3);
  EXPECT_EQ(list.pop_back(), 30);
  EXPECT_EQ(list.pop_back(), 20);
  EXPECT_EQ(list.pop_back(), 10);
  EXPECT_TRUE(list.is_empty());
}

TEST(DoubleListTest, SingleElementTransitions) {
  Double_List<int> list;
  list.push_back(42);
  EXPECT_EQ(list.get_size(), 1);
  EXPECT_EQ(list.pop_back(), 42);
  EXPECT_TRUE(list.is_empty());

  list.push_front(99);
  EXPECT_EQ(list.pop_front(), 99);
  EXPECT_TRUE(list.is_empty());

  list.push_back(77);
  EXPECT_EQ(list.pop_front(), 77);
  EXPECT_TRUE(list.is_empty());

  list.push_front(88);
  EXPECT_EQ(list.pop_back(), 88);
  EXPECT_TRUE(list.is_empty());
}

TEST(DoubleListTest, EmptyListExceptions) {
  Double_List<int> list;
  EXPECT_THROW(list.pop_front(), std::logic_error);
  EXPECT_THROW(list.pop_back(), std::logic_error);
}

TEST(DoubleListTest, FindElement) {
  Double_List<std::string> list;
  list.push_back("apple");
  list.push_back("banana");
  list.push_back("orange");

  auto node = list.find("banana");
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->data, "banana");

  EXPECT_EQ(list.find("grape"), nullptr);
}

TEST(DoubleListTest, InsertByIndex) {
  Double_List<int> list;
  list.insert(10, static_cast<size_t>(0));  // front (push_front)
  list.insert(40, 1);  // back (push_back)
  list.insert(50, 2);  // back
  list.insert(20, 1);  // >= size / 2
  list.insert(30, 2);  // >= size / 2
  list.insert(15, 1);  // < size / 2

  EXPECT_EQ(list.get_size(), 6);
  EXPECT_EQ(list.pop_front(), 10);
  EXPECT_EQ(list.pop_front(), 15);
  EXPECT_EQ(list.pop_front(), 20);
  EXPECT_EQ(list.pop_front(), 30);
  EXPECT_EQ(list.pop_front(), 40);
  EXPECT_EQ(list.pop_front(), 50);
  EXPECT_TRUE(list.is_empty());

  EXPECT_THROW(list.insert(99, 10), std::out_of_range);
}

TEST(DoubleListTest, InsertByNode) {
  Double_List<int> list;
  list.push_back(1);
  list.push_back(3);

  auto target = list.find(3);
  list.insert(2, target);
  list.insert(0, list.find(1));

  EXPECT_EQ(list.get_size(), 4);
  EXPECT_EQ(list.pop_front(), 0);
  EXPECT_EQ(list.pop_front(), 1);
  EXPECT_EQ(list.pop_front(), 2);
  EXPECT_EQ(list.pop_front(), 3);

  EXPECT_THROW(list.insert(0, nullptr), std::invalid_argument);
}

TEST(DoubleListTest, EraseByIndex) {
  Double_List<int> list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);
  list.push_back(40);
  list.push_back(50);

  EXPECT_EQ(list.erase(1), 20);  // < size / 2
  EXPECT_EQ(list.erase(2), 40);  // >= size / 2
  EXPECT_EQ(list.erase(2), 50);  // tail
  EXPECT_EQ(list.erase(static_cast<size_t>(0)), 10);  // head
  EXPECT_EQ(list.erase(static_cast<size_t>(0)), 30);
  EXPECT_TRUE(list.is_empty());

  EXPECT_THROW(list.erase(static_cast<size_t>(0)), std::out_of_range);
  list.push_back(1);
  EXPECT_THROW(list.erase(1), std::out_of_range);
}

TEST(DoubleListTest, EraseByNode) {
  Double_List<int> list;
  list.push_back(100);
  list.push_back(200);
  list.push_back(300);
  list.push_back(400);

  EXPECT_EQ(list.erase(list.find(200)), 200);
  EXPECT_EQ(list.erase(list.find(100)), 100);
  EXPECT_EQ(list.erase(list.find(400)), 400);
  EXPECT_EQ(list.get_size(), 1);
  EXPECT_EQ(list.erase(list.find(300)), 300);
  EXPECT_TRUE(list.is_empty());

  EXPECT_THROW(list.erase(nullptr), std::invalid_argument);
}

TEST(DoubleListTest, CopyConstructorAndAssignment) {
  Double_List<int> empty;
  Double_List<int> empty_copy(empty);
  EXPECT_TRUE(empty_copy.is_empty());

  Double_List<int> original;
  original.push_back(1);
  original.push_back(2);
  original.push_back(3);

  Double_List<int> copy = original;
  EXPECT_EQ(copy.get_size(), 3);

  Double_List<int> assigned;
  assigned = original;
  Double_List<int>& ref = assigned;
  assigned = ref;
  EXPECT_EQ(assigned.get_size(), 3);

  original.pop_front();
  EXPECT_EQ(original.get_size(), 2);
  EXPECT_EQ(copy.get_size(), 3);
  EXPECT_EQ(assigned.get_size(), 3);

  EXPECT_EQ(copy.pop_back(), 3);
  EXPECT_EQ(copy.pop_back(), 2);
  EXPECT_EQ(copy.pop_back(), 1);
  EXPECT_EQ(assigned.pop_front(), 1);
}

TEST(DoubleListTest, MoveSemantics) {
  Double_List<int> source;
  source.push_back(10);
  source.push_back(20);
  source.push_back(30);

  Double_List<int> moved(std::move(source));
  EXPECT_EQ(moved.get_size(), 3);
  EXPECT_EQ(source.get_size(), 0);
  EXPECT_TRUE(source.is_empty());

  Double_List<int> another;
  another = std::move(moved);
  EXPECT_EQ(another.get_size(), 3);
  EXPECT_EQ(another.pop_back(), 30);
  EXPECT_EQ(another.pop_front(), 10);
  EXPECT_EQ(another.pop_front(), 20);
  EXPECT_TRUE(another.is_empty());
}

TEST(DoubleListTest, IteratorEmptyAndForwardTraversal) {
  Double_List<int> list;
  Double_List<int>::iterator default_it;
  EXPECT_EQ(default_it, list.end());
  EXPECT_EQ(list.begin(), list.end());
  EXPECT_EQ(list.cbegin(), list.cend());

  list.push_back(10);
  list.push_back(20);
  list.push_back(30);

  int expected[] = {10, 20, 30};
  size_t idx = 0;
  for (auto it = list.begin(); it != list.end(); ++it) {
    EXPECT_EQ(*it, expected[idx]);
    *it += 1;
    ++idx;
  }
  EXPECT_EQ(idx, 3);

  auto it = list.begin();
  auto prev = it++;
  EXPECT_EQ(*prev, 11);
  EXPECT_EQ(*it, 21);

  int sum = 0;
  for (int val : list) {
    sum += val;
  }
  EXPECT_EQ(sum, 63);

  auto end_it = list.end();
  ++end_it;
  EXPECT_EQ(end_it, list.end());
}

TEST(DoubleListTest, IteratorBackwardTraversal) {
  Double_List<int> list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);
  list.push_back(40);

  auto it = list.begin() + 3;
  EXPECT_EQ(*it, 40);
  --it;
  EXPECT_EQ(*it, 30);
  auto prev = it--;
  EXPECT_EQ(*prev, 30);
  EXPECT_EQ(*it, 20);
  --it;
  EXPECT_EQ(*it, 10);
  --it;
  EXPECT_EQ(it, list.end());

  --it;
  EXPECT_EQ(it, list.end());

  const Double_List<int>& clist = list;
  auto cit = clist.begin() + 3;
  EXPECT_EQ(*cit, 40);
  --cit;
  EXPECT_EQ(*cit, 30);
  cit--;
  EXPECT_EQ(*cit, 20);
  --cit;
  EXPECT_EQ(*cit, 10);
  --cit;
  EXPECT_EQ(cit, clist.end());
}

TEST(DoubleListTest, IteratorArrowAndConstIterator) {
  Double_List<std::string> list;
  list.push_back("hello");
  list.push_back("world");

  auto it = list.begin();
  EXPECT_EQ(it->size(), 5);
  it->append("!");
  EXPECT_EQ(*it, "hello!");

  const Double_List<std::string>& clist = list;
  auto cit = clist.begin();
  ASSERT_NE(cit, clist.end());
  EXPECT_EQ(*cit, "hello!");
  EXPECT_EQ(cit->size(), 6);

  auto cprev = cit++;
  EXPECT_EQ(*cprev, "hello!");
  EXPECT_EQ(*cit, "world");
  ++cit;
  EXPECT_EQ(cit, clist.end());

  size_t total_len = 0;
  for (const auto& s : clist) {
    total_len += s.size();
  }
  EXPECT_EQ(total_len, 11);
}

TEST(DoubleListTest, IteratorArithmeticAndComparisons) {
  Double_List<int> list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);
  list.push_back(40);

  auto it = list.begin();
  EXPECT_EQ(*(it + 0), 10);
  EXPECT_EQ(*(it + 2), 30);
  EXPECT_EQ(it + 4, list.end());

  Double_List<int>::iterator copy_it(it);
  EXPECT_TRUE(copy_it == it);
  copy_it += 3;
  EXPECT_EQ(*copy_it, 40);
  EXPECT_TRUE(copy_it != it);

  EXPECT_EQ(*(copy_it - 0), 40);
  EXPECT_EQ(*(copy_it - 1), 30);
  EXPECT_EQ(*(copy_it - 3), 10);
  EXPECT_EQ(copy_it - 4, list.end());

  Double_List<int>::iterator assigned_it;
  assigned_it = copy_it;
  assigned_it -= 2;
  EXPECT_EQ(*assigned_it, 20);
  assigned_it += 1;
  EXPECT_EQ(*assigned_it, 30);
}

TEST(DoubleListTest, IteratorExceptions) {
  Double_List<int> empty_list;
  EXPECT_THROW(*empty_list.end(), std::logic_error);
  EXPECT_THROW(empty_list.end().operator->(), std::logic_error);
  EXPECT_THROW(*empty_list.cend(), std::logic_error);
  EXPECT_THROW(empty_list.cend().operator->(), std::logic_error);

  Double_List<int> list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);

  auto it = list.begin();
  EXPECT_THROW(it + (-1), std::logic_error);
  EXPECT_THROW(it += (-1), std::logic_error);
  EXPECT_THROW(it + 4, std::logic_error);
  EXPECT_THROW(it += 4, std::logic_error);
  EXPECT_THROW(list.end() + 1, std::logic_error);

  auto tail_it = list.begin() + 2;
  EXPECT_THROW(tail_it - (-1), std::logic_error);
  EXPECT_THROW(tail_it -= (-1), std::logic_error);
  EXPECT_THROW(tail_it - 4, std::logic_error);
  EXPECT_THROW(tail_it -= 4, std::logic_error);
  EXPECT_THROW(list.end() - 1, std::logic_error);
}

TEST(DoubleListTest, IteratorFromFind) {
  Double_List<int> list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);

  Double_List<int>::iterator it(list.find(20));
  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 30);
  --it;
  EXPECT_EQ(*it, 20);
  --it;
  EXPECT_EQ(*it, 10);
}
