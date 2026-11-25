// Copyright 2026 Khaferl Pavel

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <utility>
#include "lib_list/list.h"

TEST(ListTest, Initialization) {
  List<int> list;
  EXPECT_EQ(list.get_size(), 0);
  EXPECT_TRUE(list.is_empty());
}

TEST(ListTest, PushFrontAndPopFront) {
  List<int> list;
  list.push_front(10);
  list.push_front(20);
  list.push_front(30);

  EXPECT_EQ(list.get_size(), 3);
  EXPECT_EQ(list.pop_front(), 30);
  EXPECT_EQ(list.pop_front(), 20);
  EXPECT_EQ(list.pop_front(), 10);
  EXPECT_TRUE(list.is_empty());
}

TEST(ListTest, PushBackAndPopBack) {
  List<int> list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);

  EXPECT_EQ(list.get_size(), 3);
  EXPECT_EQ(list.pop_back(), 30);
  EXPECT_EQ(list.pop_back(), 20);
  EXPECT_EQ(list.pop_back(), 10);
  EXPECT_TRUE(list.is_empty());
}

TEST(ListTest, SingleElementTransitions) {
  List<int> list;
  list.push_back(42);
  EXPECT_EQ(list.get_size(), 1);
  EXPECT_EQ(list.pop_back(), 42);
  EXPECT_TRUE(list.is_empty());

  list.push_front(99);
  EXPECT_EQ(list.pop_front(), 99);
  EXPECT_TRUE(list.is_empty());
}

TEST(ListTest, EmptyListExceptions) {
  List<int> list;
  EXPECT_THROW(list.pop_front(), std::invalid_argument);
  EXPECT_THROW(list.pop_back(), std::invalid_argument);
}

TEST(ListTest, FindElement) {
  List<std::string> list;
  list.push_back("apple");
  list.push_back("banana");
  list.push_back("orange");

  auto node = list.find("banana");
  ASSERT_NE(node, nullptr);
  EXPECT_EQ(node->data, "banana");

  EXPECT_EQ(list.find("grape"), nullptr);
}

TEST(ListTest, InsertByIndex) {
  List<int> list;
  list.insert(10, static_cast<size_t>(0));  // front (push_front)
  list.insert(30, 1);  // back (push_back)
  list.insert(20, 1);  // middle

  EXPECT_EQ(list.get_size(), 3);
  EXPECT_EQ(list.pop_front(), 10);
  EXPECT_EQ(list.pop_front(), 20);
  EXPECT_EQ(list.pop_front(), 30);

  EXPECT_THROW(list.insert(99, 10), std::out_of_range);
}

TEST(ListTest, InsertByNode) {
  List<int> list;
  list.push_back(1);
  list.push_back(3);

  auto target = list.find(3);
  list.insert(2, target);

  EXPECT_EQ(list.get_size(), 3);
  EXPECT_EQ(list.pop_front(), 1);
  EXPECT_EQ(list.pop_front(), 2);
  EXPECT_EQ(list.pop_front(), 3);

  EXPECT_THROW(list.insert(0, nullptr), std::invalid_argument);
}

TEST(ListTest, EraseByIndex) {
  List<int> list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);

  EXPECT_EQ(list.erase(1), 20);
  EXPECT_EQ(list.get_size(), 2);
  EXPECT_EQ(list.erase(static_cast<size_t>(0)), 10);
  EXPECT_EQ(list.erase(static_cast<size_t>(0)), 30);
  EXPECT_TRUE(list.is_empty());

  EXPECT_THROW(list.erase(static_cast<size_t>(0)), std::out_of_range);
}

TEST(ListTest, EraseByNode) {
  List<int> list;
  list.push_back(100);
  list.push_back(200);
  list.push_back(300);

  auto node = list.find(200);
  EXPECT_EQ(list.erase(node), 200);
  EXPECT_EQ(list.get_size(), 2);

  EXPECT_THROW(list.erase(nullptr), std::invalid_argument);
}

TEST(ListTest, CopyConstructorAndAssignment) {
  List<int> original;
  original.push_back(1);
  original.push_back(2);
  original.push_back(3);

  List<int> copy = original;
  EXPECT_EQ(copy.get_size(), 3);

  List<int> assigned;
  assigned = original;
  EXPECT_EQ(assigned.get_size(), 3);

  original.pop_front();
  EXPECT_EQ(original.get_size(), 2);
  EXPECT_EQ(copy.get_size(), 3);
  EXPECT_EQ(assigned.get_size(), 3);
  EXPECT_EQ(copy.pop_front(), 1);
}

TEST(ListTest, MoveSemantics) {
  List<int> source;
  source.push_back(10);
  source.push_back(20);

  List<int> moved(std::move(source));
  EXPECT_EQ(moved.get_size(), 2);
  EXPECT_EQ(source.get_size(), 0);
  EXPECT_TRUE(source.is_empty());

  List<int> another;
  another = std::move(moved);
  EXPECT_EQ(another.get_size(), 2);
  EXPECT_EQ(another.pop_front(), 10);
  EXPECT_EQ(another.pop_front(), 20);
}

TEST(ListTest, IteratorEmptyAndTraversal) {
  List<int> list;
  List<int>::iterator default_it;
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

TEST(ListTest, IteratorArrowAndConstIterator) {
  List<std::string> list;
  list.push_back("hello");
  list.push_back("world");

  auto it = list.begin();
  EXPECT_EQ(it->size(), 5);
  it->append("!");
  EXPECT_EQ(*it, "hello!");

  const List<std::string>& clist = list;
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

TEST(ListTest, IteratorArithmeticAndCopy) {
  List<int> list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);
  list.push_back(40);

  auto it = list.begin();
  EXPECT_EQ(*(it + 0), 10);
  EXPECT_EQ(*(it + 1), 20);
  EXPECT_EQ(*(it + 3), 40);
  EXPECT_EQ(it + 4, list.end());

  List<int>::iterator copy_it(it);
  EXPECT_TRUE(copy_it == it);
  copy_it += 2;
  EXPECT_EQ(*copy_it, 30);
  EXPECT_EQ(*it, 10);
  EXPECT_TRUE(copy_it != it);

  List<int>::iterator assigned_it;
  assigned_it = copy_it;
  EXPECT_EQ(*assigned_it, 30);
  assigned_it += 1;
  EXPECT_EQ(*assigned_it, 40);
}

TEST(ListTest, IteratorExceptionsAndFind) {
  List<int> empty_list;
  EXPECT_THROW(*empty_list.end(), std::logic_error);
  EXPECT_THROW(empty_list.end().operator->(), std::logic_error);
  EXPECT_THROW(*empty_list.cend(), std::logic_error);
  EXPECT_THROW(empty_list.cend().operator->(), std::logic_error);

  List<int> list;
  list.push_back(10);
  list.push_back(20);
  list.push_back(30);

  auto it = list.begin();
  EXPECT_THROW(it + (-1), std::logic_error);
  EXPECT_THROW(it += (-1), std::logic_error);
  EXPECT_THROW(it + 4, std::logic_error);
  EXPECT_THROW(it += 4, std::logic_error);
  EXPECT_THROW(list.end() + 1, std::logic_error);

  List<int>::iterator found_it(list.find(20));
  EXPECT_EQ(*found_it, 20);
  ++found_it;
  EXPECT_EQ(*found_it, 30);
}
