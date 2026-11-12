// Copyright 2026 Khaferl Pavel

#include <gtest/gtest.h>
#include <algorithm>
#include "lib_stack_on_mass/stack_on_mass.h"

TEST(StackTest, Initialization) {
  TStack<int> stack(5);
  EXPECT_TRUE(stack.is_empty());
  EXPECT_FALSE(stack.is_full());
  EXPECT_EQ(stack.size(), 5);
  EXPECT_EQ(stack.count(), 0);
}

TEST(StackTest, PushAndPop) {
  TStack<int> stack(3);
  stack.push(10);
  EXPECT_FALSE(stack.is_empty());
  EXPECT_EQ(stack.count(), 1);
  EXPECT_EQ(stack.top(), 10);
  stack.push(20);
  EXPECT_EQ(stack.count(), 2);
  EXPECT_EQ(stack.top(), 20);
  int popped = stack.pop();
  EXPECT_EQ(popped, 20);
  EXPECT_EQ(stack.count(), 1);
  popped = stack.pop();
  EXPECT_EQ(popped, 10);
  EXPECT_TRUE(stack.is_empty());
}

// Stack Overflow
TEST(StackTest, StackOverflow) {
  TStack<int> stack(2);
  stack.push(1);
  stack.push(2);
  EXPECT_TRUE(stack.is_full());
  EXPECT_EQ(stack.count(), 2);
  EXPECT_THROW(stack.push(3), std::logic_error);
}

// Stack Underflow
TEST(StackTest, StackUnderflow) {
  TStack<int> stack(2);
  EXPECT_THROW(stack.pop(), std::logic_error);
}

TEST(StackTest, CopyConstructor) {
  TStack<int> original(5);
  original.push(1);
  original.push(2);
  TStack<int> copy(original);
  EXPECT_EQ(copy.count(), 2);
  EXPECT_EQ(copy.top(), 2);
  original.push(3);
  EXPECT_EQ(original.count(), 3);
  EXPECT_EQ(copy.count(), 2);
}
