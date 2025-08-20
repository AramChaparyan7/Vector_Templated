#include "../includes/Vector.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(VectorTest, PushBack) {
    Vector<int> vec;
    vec.push_back(10);
    EXPECT_EQ(vec.size(), 1);
    vec.push_back(20);
    EXPECT_EQ(vec.size(), 2);
    Vector<char> c;
    c.push_back('a');
    EXPECT_EQ(c.size(), 1);
}

TEST(VectorTest, Indexing) {
    Vector<std::string> vec;
    vec.push_back("hello");
    vec.push_back("world");
    EXPECT_EQ(vec[0], "hello");
    EXPECT_EQ(vec[1], "world");
}

TEST(VectorTest, Throws_Exception) {
    Vector<int> vec;
    vec.push_back(42);
    EXPECT_THROW(vec.at(1), std::out_of_range);
}

TEST(VectorTest, Front_Back) {
    Vector<int> vec = {1, 2, 3, 4};
    EXPECT_EQ(vec.front(), 1);
    EXPECT_EQ(vec.back(), 4);
    EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, Size_Capacity) {
    Vector<int> vec = {1, 2, 3, 4};
    vec.resize(10);
    EXPECT_EQ(vec.capacity(), 10);
    vec.clear();
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.empty(), true);
    Vector<int> vec1 = {1, 2, 3, 4};
    vec1.reserve(50);
    EXPECT_EQ(vec1.capacity(), 50);
    
}

TEST(VectorTest, Insert_Erase) {
    Vector<int> vec = {1, 2, 3, 4};
    vec.insert(4,2);
    EXPECT_EQ(vec.size(), 5);
    vec.erase(2);
    EXPECT_EQ(vec.size(), 4);
}

TEST(VectorTest, Swap) {
    Vector<int> vec1 = {1, 2, 3, 4};
    Vector<int> vec2 = {8};
    swap(vec1, vec2);
    EXPECT_EQ(vec1.size(), 1);
    EXPECT_EQ(vec2.size(), 4);
}

TEST(VectorTest, Operators) {
    Vector<int> vec1 = {1, 2, 3, 4};
    Vector<int> vec2 = {8};
    EXPECT_EQ(true, vec1 < vec2);
    EXPECT_EQ(true, vec1 != vec2);
    EXPECT_EQ(false, vec1 >= vec2);
}
