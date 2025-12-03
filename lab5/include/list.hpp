#pragma once

#include "allocator.hpp"

template <typename T, size_t BLOCK_SIZE>
class List {
private:
    struct ListNode {
        T data;
        ListNode* next;
        ListNode* prev;
        void* block_start;
    };

    using NodeAllocator = Allocator<T, BLOCK_SIZE>;

    NodeAllocator m_allocator;
    ListNode* HEAD;
    ListNode* TAIL;
    size_t m_size;

public:
    class Iterator {
    private:
        ListNode* m_node;
    public:
        Iterator(ListNode* node = nullptr) : m_node{node} {}
        T& operator*() { return m_node->data; }
        T* operator->() { return &m_node->data; }
        Iterator& operator++() {m_node = m_node->next; return *this; }
        bool operator==(const Iterator& other) const { return m_node == other.m_node; }
        bool operator!=(const Iterator& other) const { return m_node != other.m_node; }
        ListNode* node() { return m_node; }

        friend class List;
    };

    Iterator begin() { return Iterator(HEAD); }
    Iterator end() { return Iterator(nullptr); }

    List(const NodeAllocator& alloc);
    List(const List& other);
    void operator=(const List& other);
    ~List();

    size_t get_size() const noexcept;
    bool empty() const noexcept;
    void clear() noexcept;
    void push_front(const T& value);
    void push_back(const T& value);

    typename List<T, BLOCK_SIZE>::Iterator
    insert(Iterator pos, const T& value);

    typename List<T, BLOCK_SIZE>::Iterator
    erase(Iterator pos);
    void pop_front();
    void pop_back();

};


#include "../inline/list.ipp"