//#include "pch.h"

#include <gtest/gtest.h>
#include "../lib_stack_on_mass/stack_on_mass.h"

TEST(StackTest, Initialization) {
    TStack<int> stack(5);
    EXPECT_TRUE(stack.is_empty());
    EXPECT_FALSE(stack.is_full());
    EXPECT_EQ(stack.size(), 0);
}

TEST(StackTest, PushAndPop) {
    TStack<int> stack(3);
    stack.push(10);
    EXPECT_FALSE(stack.is_empty());
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.top(), 10);
    stack.push(20);
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), 20);
    EXPECT_EQ(stack.pop(), 20);
    EXPECT_EQ(stack.size(), 1);
    EXPECT_EQ(stack.pop(), 10);
    EXPECT_TRUE(stack.is_empty());
}

//Stack Overflow
TEST(StackTest, StackOverflow) {
    TStack<int> stack(2);
    stack.push(1);
    stack.push(2);
    EXPECT_TRUE(stack.is_full());
    EXPECT_EQ(stack.size(), 2);
    EXPECT_THROW(stack.push(3), const char*);
}

//Stack Underflow
TEST(StackTest, StackUnderflow) {
    TStack<int> stack(2);
    EXPECT_THROW(stack.pop(), const char*);
}

TEST(StackTest, CopyConstructor) {
    TStack<int> original(5);
    original.push(1);
    original.push(2);
    TStack<int> copy(original);
    EXPECT_EQ(copy.size(), 2);
    EXPECT_EQ(copy.top(), 2);
    original.push(3);
    EXPECT_EQ(original.size(), 3);
    EXPECT_EQ(copy.size(), 2);
}