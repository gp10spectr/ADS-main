// Copyright 2026 Khaferl Pavel

#include <gtest/gtest.h>
#include "lib_queue/queue.h"

TEST(QueueTest, Initialization) {
  Queue<int> q(5);
  EXPECT_EQ(q.get_size(), 5);
  EXPECT_TRUE(q.is_empty());
  EXPECT_FALSE(q.is_full());
}

TEST(QueueTest, PushAndGetFront) {
  Queue<int> q(3);
  q.push(10);
  EXPECT_FALSE(q.is_empty());
  EXPECT_EQ(q.get_front(), 10);

  q.push(20);
  EXPECT_EQ(q.get_front(), 10);
}

TEST(QueueTest, PopFIFO) {
  Queue<int> q(3);
  q.push(1);
  q.push(2);
  q.push(3);

  EXPECT_TRUE(q.is_full());
  EXPECT_EQ(q.pop(), 1);
  EXPECT_EQ(q.pop(), 2);
  EXPECT_FALSE(q.is_empty());
  EXPECT_EQ(q.pop(), 3);
  EXPECT_TRUE(q.is_empty());
}

TEST(QueueTest, CircularBufferWrapAround) {
  Queue<int> q(2);
  q.push(1);
  q.push(2);
  EXPECT_EQ(q.pop(), 1);

  // back shall move to pos 0
  q.push(3);
  EXPECT_TRUE(q.is_full());
  EXPECT_EQ(q.pop(), 2);
  EXPECT_EQ(q.pop(), 3);
  EXPECT_TRUE(q.is_empty());
}

TEST(QueueTest, OverflowException) {
  Queue<int> q(2);
  q.push(100);
  q.push(200);
  EXPECT_THROW(q.push(300), std::out_of_range);
}

TEST(QueueTest, EmptyQueueExceptions) {
  Queue<int> q(2);
  EXPECT_THROW(q.get_front(), std::out_of_range);
  EXPECT_THROW(q.pop(), std::out_of_range);
}

TEST(QueueTest, CopyConstructor) {
  Queue<int> q1(3);
  q1.push(1);
  q1.push(2);

  Queue<int> q2 = q1;  // copy
  EXPECT_EQ(q2.get_size(), q1.get_size());
  EXPECT_EQ(q2.pop(), 1);
  EXPECT_EQ(q2.pop(), 2);

  // check independency of q1 and q2
  EXPECT_FALSE(q1.is_empty());
  EXPECT_TRUE(q2.is_empty());
}
