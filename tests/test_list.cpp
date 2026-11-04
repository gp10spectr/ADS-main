#include <gtest/gtest.h>
#include "list.h"

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
    list.insert(10, size_t(0)); //front (push_front)
    list.insert(30, 1); //back (push_back)
    list.insert(20, 1); //middle

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
    EXPECT_EQ(list.erase(size_t(0)), 10);
    EXPECT_EQ(list.erase(size_t(0)), 30);
    EXPECT_TRUE(list.is_empty());

    EXPECT_THROW(list.erase(size_t(0)), std::out_of_range);
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