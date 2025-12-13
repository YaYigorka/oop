#include <gtest/gtest.h>
#include "allocator.hpp"
#include "list.hpp"

TEST(AllocatorTest, DefaultConstructor) {
    Allocator<int, 1024> alloc;
    
    void* ptr = alloc.do_allocate(sizeof(int), alignof(int));
    ASSERT_NE(ptr, nullptr);
    alloc.do_deallocate(ptr, sizeof(int), alignof(int));
}

TEST(AllocatorTest, CopyConstructor) {
    Allocator<int, 1024> alloc1;
    void* ptr1 = alloc1.do_allocate(sizeof(int), alignof(int));
    *static_cast<int*>(ptr1) = 42;
    
    Allocator<int, 1024> alloc2(alloc1);
    
    ASSERT_FALSE(alloc1 == alloc2);
}

TEST(AllocatorTest, Allocation) {
    Allocator<int, 1024> alloc;
    
    void* ptr1 = alloc.do_allocate(sizeof(int), alignof(int));
    void* ptr2 = alloc.do_allocate(sizeof(int), alignof(int));
    void* ptr3 = alloc.do_allocate(sizeof(int), alignof(int));
    
    ASSERT_NE(ptr1, nullptr);
    ASSERT_NE(ptr2, nullptr);
    ASSERT_NE(ptr3, nullptr);
    
    ASSERT_NE(ptr1, ptr2);
    ASSERT_NE(ptr2, ptr3);
    
    alloc.do_deallocate(ptr1, sizeof(int), alignof(int));
    alloc.do_deallocate(ptr2, sizeof(int), alignof(int));
    alloc.do_deallocate(ptr3, sizeof(int), alignof(int));
}

TEST(AllocatorTest, DeallocationAndReuse) {
    Allocator<int, 1024> alloc;
    
    void* ptr1 = alloc.do_allocate(sizeof(int), alignof(int));
    void* ptr2 = alloc.do_allocate(sizeof(int), alignof(int));
    
    alloc.do_deallocate(ptr1, sizeof(int), alignof(int));
    
    void* ptr3 = alloc.do_allocate(sizeof(int), alignof(int));
    ASSERT_EQ(ptr1, ptr3);
    
    alloc.do_deallocate(ptr2, sizeof(int), alignof(int));
    alloc.do_deallocate(ptr3, sizeof(int), alignof(int));
}

TEST(AllocatorTest, OutOfMemory) {
    Allocator<int, 32> alloc;
    
    void* ptr1 = alloc.do_allocate(sizeof(int), alignof(int));
    void* ptr2 = alloc.do_allocate(sizeof(int), alignof(int));
    void* ptr3 = alloc.do_allocate(sizeof(int), alignof(int));
    void* ptr4 = alloc.do_allocate(sizeof(int), alignof(int));
    
    ASSERT_NE(ptr1, nullptr);
    ASSERT_NE(ptr2, nullptr);
    ASSERT_NE(ptr3, nullptr);
    ASSERT_NE(ptr4, nullptr);
    
    ASSERT_THROW(alloc.do_allocate(120, alignof(int)), std::bad_alloc);
    
    alloc.do_deallocate(ptr1, sizeof(int), alignof(int));
    alloc.do_deallocate(ptr2, sizeof(int), alignof(int));
    alloc.do_deallocate(ptr3, sizeof(int), alignof(int));
    alloc.do_deallocate(ptr4, sizeof(int), alignof(int));
}

TEST(ListTest, DefaultConstructor) {
    Allocator<int, 1024> alloc;
    List<int, 1024> list(alloc);
    
    ASSERT_EQ(list.get_size(), 0);
    ASSERT_TRUE(list.empty());
}

TEST(ListTest, PushBack) {
    Allocator<int, 1024> alloc;
    List<int, 1024> list(alloc);
    
    list.push_back(1);
    ASSERT_EQ(list.get_size(), 1);
    ASSERT_FALSE(list.empty());
    
    list.push_back(2);
    list.push_back(3);
    ASSERT_EQ(list.get_size(), 3);
}

TEST(ListTest, PushFront) {
    Allocator<int, 1024> alloc;
    List<int, 1024> list(alloc);
    
    list.push_front(1);
    ASSERT_EQ(list.get_size(), 1);
    
    list.push_front(2);
    list.push_front(3);
    ASSERT_EQ(list.get_size(), 3);
    
    auto it = list.begin();
    ASSERT_EQ(*it, 3);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 1);
}

TEST(ListTest, PopBack) {
    Allocator<int, 1024> alloc;
    List<int, 1024> list(alloc);
    
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    list.pop_back();
    ASSERT_EQ(list.get_size(), 2);
    
    list.pop_back();
    ASSERT_EQ(list.get_size(), 1);
    
    list.pop_back();
    ASSERT_EQ(list.get_size(), 0);
    ASSERT_TRUE(list.empty());
    
    ASSERT_THROW(list.pop_back(), std::out_of_range);
}

TEST(ListTest, PopFront) {
    Allocator<int, 1024> alloc;
    List<int, 1024> list(alloc);
    
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    list.pop_front();
    ASSERT_EQ(list.get_size(), 2);
    
    list.pop_front();
    ASSERT_EQ(list.get_size(), 1);
    
    list.pop_front();
    ASSERT_EQ(list.get_size(), 0);
    ASSERT_TRUE(list.empty());
    
    ASSERT_THROW(list.pop_front(), std::out_of_range);
}

TEST(ListTest, Insert) {
    Allocator<int, 1024> alloc;
    List<int, 1024> list(alloc);
    
    auto it = list.insert(list.end(), 1);
    ASSERT_EQ(*it, 1);
    ASSERT_EQ(list.get_size(), 1);
    
    it = list.insert(list.begin(), 2);
    ASSERT_EQ(*it, 2);
    ASSERT_EQ(list.get_size(), 2);
    
    it = list.begin();
    ++it;
    it = list.insert(it, 3);
    ASSERT_EQ(*it, 3);
    ASSERT_EQ(list.get_size(), 3);
    
    it = list.begin();
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 3);
    ++it;
    ASSERT_EQ(*it, 1);
}

TEST(ListTest, Erase) {
    Allocator<int, 1024> alloc;
    List<int, 1024> list(alloc);
    
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(4);
    
    auto it = list.begin();
    ++it;
    it = list.erase(it);
    ASSERT_EQ(*it, 3);
    ASSERT_EQ(list.get_size(), 3);
    
    it = list.erase(list.begin());
    ASSERT_EQ(*it, 3);
    ASSERT_EQ(list.get_size(), 2);
    
    it = list.begin();
    ++it;
    it = list.erase(it);
    ASSERT_EQ(it, list.end());
    ASSERT_EQ(list.get_size(), 1);
    
    list.erase(list.begin());
    ASSERT_EQ(list.get_size(), 0);
    ASSERT_TRUE(list.empty());
}

TEST(ListTest, CopyConstructor) {
    Allocator<int, 1024> alloc;
    List<int, 1024> list1(alloc);
    
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    
    List<int, 1024> list2(list1);
    
    ASSERT_EQ(list2.get_size(), 3);
    
    auto it = list2.begin();
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 3);
    
    list1.push_back(4);
    ASSERT_EQ(list1.get_size(), 4);
    ASSERT_EQ(list2.get_size(), 3);
}

TEST(ListTest, AssignmentOperator) {
    Allocator<int, 1024> alloc;
    List<int, 1024> list1(alloc);
    
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    
    List<int, 1024> list2(alloc);
    list2 = list1;
    
    ASSERT_EQ(list2.get_size(), 3);
    
    auto it = list2.begin();
    ASSERT_EQ(*it, 1);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 3);
    
    list1.clear();
    ASSERT_EQ(list1.get_size(), 0);
    ASSERT_EQ(list2.get_size(), 3);
}

TEST(ListTest, Clear) {
    Allocator<int, 1024> alloc;
    List<int, 1024> list(alloc);
    
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    ASSERT_EQ(list.get_size(), 3);
    
    list.clear();
    
    ASSERT_EQ(list.get_size(), 0);
    ASSERT_TRUE(list.empty());
}

TEST(ListTest, Iterator) {
    Allocator<int, 1024> alloc;
    List<int, 1024> list(alloc);
    
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    
    auto it = list.begin();
    int sum = 0;
    int count = 0;
    
    for (; it != list.end(); ++it) {
        sum += *it;
        ++count;
    }
    
    ASSERT_EQ(sum, 6);
    ASSERT_EQ(count, 3);
    
    auto it1 = list.begin();
    auto it2 = list.begin();
    ASSERT_EQ(it1, it2);
    
    ++it1;
    ASSERT_NE(it1, it2);
}

TEST(ListTest, ComplexTypes) {
    Allocator<std::string, 1024> alloc;
    List<std::string, 1024> list(alloc);
    
    list.push_back("Hello");
    list.push_back("World");
    list.push_back("!");
    
    ASSERT_EQ(list.get_size(), 3);
    
    auto it = list.begin();
    ASSERT_EQ(*it, "Hello");
    ++it;
    ASSERT_EQ(*it, "World");
    ++it;
    ASSERT_EQ(*it, "!");
    
    *list.begin() = "Hi";
    ASSERT_EQ(*list.begin(), "Hi");
}

TEST(ListTest, MemoryManagement) {
    Allocator<int, 1024> alloc;
    
    {
        List<int, 1024> list(alloc);
        for (int i = 0; i < 100; ++i) {
            list.push_back(i);
        }
        
        for (int i = 0; i < 50; ++i) {
            list.pop_front();
        }
        
        ASSERT_EQ(list.get_size(), 50);
    }
    
    void* ptr = alloc.allocate(sizeof(int));
    ASSERT_NE(ptr, nullptr);
    alloc.deallocate(ptr, sizeof(int));
}

TEST(ListAllocatorIntegrationTest, CustomAllocator) {
    Allocator<int, 64> alloc;
    
    List<int, 64> list(alloc);
    
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    
    ASSERT_EQ(list.get_size(), 5);
    
    list.clear();
    ASSERT_EQ(list.get_size(), 0);
    
    for (int i = 0; i < 5; ++i) {
        list.push_back(i * 2);
    }
    
    ASSERT_EQ(list.get_size(), 5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}