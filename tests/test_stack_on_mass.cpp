//#include "pch.h"
#include <gtest/gtest.h>
#include "../lib_stack_on_mass/stack_on_mass.h"

TEST(ClassStack, def_constructor) {
	TStack<int> stack(5);
	EXPECT_EQ(stack.size(), 5);
}

TEST(ClassStack, copy_constructor) {
	TStack<int> stack1(5);
}