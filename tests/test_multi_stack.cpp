// Copyright 2026 Khaferl Pavel

#include <gtest/gtest.h>
#include <utility>
#include "lib_multi_stack/multi_stack.h"

TEST(MultiStackTest, Initialization) {
  Multi_Stack<int> ms(3, 9);
  EXPECT_EQ(ms.get_size(), 9);
  EXPECT_EQ(ms.get_stack_count(), 3);
  EXPECT_TRUE(ms.is_empty());
  EXPECT_FALSE(ms.is_full());

  for (size_t i = 0; i < 3; i++) {
    EXPECT_TRUE(ms.is_empty(i));
    EXPECT_FALSE(ms.is_full(i));
  }
}

TEST(MultiStackTest, PushAndPopIndependent) {
  Multi_Stack<int> ms(3, 9);  // 3 slots for every stack
  ms.push(0, 10);
  ms.push(0, 20);
  ms.push(1, 100);

  EXPECT_EQ(ms.get_top(0), 20);
  EXPECT_EQ(ms.get_top(1), 100);

  EXPECT_EQ(ms.pop(0), 20);
  EXPECT_EQ(ms.pop(0), 10);
  EXPECT_TRUE(ms.is_empty(0));

  EXPECT_EQ(ms.pop(1), 100);
  EXPECT_TRUE(ms.is_empty(1));
}

TEST(MultiStackTest, RepackWhenOneStackOverflows) {
  // 2 stacks mutual size 4 and 2 slots for every stack
  Multi_Stack<int> ms(2, 4);

  ms.push(0, 1);
  ms.push(0, 2);
  // stack 0 localy full but mutual stack is not
  EXPECT_TRUE(ms.is_full(0));
  EXPECT_FALSE(ms.is_full());

  // next push will use repack and will take slots from first stack
  EXPECT_NO_THROW(ms.push(0, 3));
  EXPECT_EQ(ms.get_top(0), 3);
  EXPECT_EQ(ms.get_count(), 3);

  ms.push(1, 99);
  EXPECT_TRUE(ms.is_full());  // now all 4 slots are taken

  // push in full stack
  EXPECT_THROW(ms.push(0, 4), std::out_of_range);
}

TEST(MultiStackTest, Exceptions) {
  Multi_Stack<int> ms(2, 4);
  EXPECT_THROW(ms.push(2, 10), std::out_of_range);
  EXPECT_THROW(ms.pop(2), std::out_of_range);
  EXPECT_THROW(ms.get_top(2), std::out_of_range);

  EXPECT_THROW(ms.pop(0), std::out_of_range);
  EXPECT_THROW(ms.get_top(0), std::out_of_range);
}

TEST(MultiStackTest, CopyAndMove) {
  Multi_Stack<int> ms(2, 4);
  ms.push(0, 1);
  ms.push(1, 2);

  Multi_Stack<int> copy = ms;
  EXPECT_EQ(copy.pop(0), 1);
  EXPECT_FALSE(ms.is_empty(0));  // original doesnt change

  Multi_Stack<int> moved = std::move(ms);
  EXPECT_EQ(moved.pop(1), 2);
  EXPECT_EQ(ms.get_count(), 0);
}
