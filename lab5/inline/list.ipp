#include "../include/list.hpp"


template<typename T, size_t BLOCK_SIZE>
List<T, BLOCK_SIZE>::List(const NodeAllocator& alloc) 
    : m_allocator{alloc}
    , HEAD{nullptr}
    , TAIL{nullptr}
    , m_size{0}
{
}


template<typename T, size_t BLOCK_SIZE>
List<T, BLOCK_SIZE>::List(const List& other)
    : m_allocator{other.m_allocator}
    , HEAD{nullptr}
    , TAIL{nullptr}
    , m_size{0}
{
    ListNode* current = other.HEAD;
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }
}


template<typename T, size_t BLOCK_SIZE>
void List<T, BLOCK_SIZE>::operator=(const List& other) {
    m_allocator = other.m_allocator;
    HEAD = TAIL = nullptr;
    m_size = 0;

    ListNode* current = other.HEAD;
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }
}


template<typename T, size_t BLOCK_SIZE>
List<T, BLOCK_SIZE>::~List() {
    ListNode* current = HEAD;
    while (current != nullptr) {
        ListNode* next = current->next;
        current->data.~T();
        m_allocator.do_deallocate(current->block_start, sizeof(ListNode), alignof(ListNode));
        current = next;
    }

    HEAD = TAIL = nullptr;
    m_size = 0;
}


template<typename T, size_t BLOCK_SIZE>
size_t List<T, BLOCK_SIZE>::get_size() const noexcept {
    return m_size;
}


template<typename T, size_t BLOCK_SIZE>
bool List<T, BLOCK_SIZE>::empty() const noexcept {
    return m_size == 0;
}


template<typename T, size_t BLOCK_SIZE>
void List<T, BLOCK_SIZE>::clear() noexcept {
    ListNode* current = HEAD;
    while (current != nullptr) {
        ListNode* next = current->next;
        pop_front();
        current = next;
    }
}


template<typename T, size_t BLOCK_SIZE>
void List<T, BLOCK_SIZE>::push_back(const T& value) {
    void* memory_block = m_allocator.do_allocate(sizeof(ListNode), alignof(ListNode));

    ListNode* new_node = static_cast<ListNode*>(memory_block);
    new (new_node) ListNode {
        .data = value,
        .next = nullptr,
        .prev = TAIL,
        .block_start = memory_block
    };

    if (TAIL != nullptr) {
        TAIL->next = new_node;
    } else {
        HEAD = new_node;
    }

    TAIL = new_node;
    ++m_size;
}


template<typename T, size_t BLOCK_SIZE>
void List<T, BLOCK_SIZE>::push_front(const T& value) {
    void* memory_block = m_allocator.do_allocate(sizeof(ListNode), alignof(ListNode));
    ListNode* new_node = static_cast<ListNode*>(memory_block);
    new (new_node) ListNode {
        .data = value,
        .next = HEAD,
        .prev = nullptr,
        .block_start = memory_block
    };

    if (HEAD != nullptr) {
        HEAD->prev = new_node;
    } else {
        TAIL = new_node;
    }

    HEAD = new_node;
    ++m_size;
}


template<typename T, size_t BLOCK_SIZE>
typename List<T, BLOCK_SIZE>::Iterator
List<T, BLOCK_SIZE>::insert(Iterator pos, const T& value) {
    ListNode* current_node = pos.node();
    ListNode* prev_node = (current_node != nullptr) ? current_node->prev : TAIL;
    
    void* memory_block = m_allocator.do_allocate(sizeof(ListNode), alignof(ListNode));
    ListNode* new_node = static_cast<ListNode*>(memory_block);
    
    new (new_node) ListNode {
        .data = value,
        .next = current_node,
        .prev = prev_node,
        .block_start = memory_block
    };
    
    if (prev_node != nullptr) {
        prev_node->next = new_node;
    } else {
        HEAD = new_node;
    }
    
    if (current_node != nullptr) {
        current_node->prev = new_node;
    } else {
        TAIL = new_node;
    }
    
    ++m_size;
    
    return Iterator(new_node);
}


template<typename T, size_t BLOCK_SIZE>
typename List<T, BLOCK_SIZE>::Iterator
List<T, BLOCK_SIZE>::erase(Iterator pos) {
    ListNode* node_to_delete = pos.node();
    ListNode* prev = node_to_delete->prev;
    ListNode* next = node_to_delete->next;

    Iterator next_pos = ++pos;

    if (prev != nullptr) {
        prev->next = next;
    } else {
        HEAD = next;
    }

    if (next != nullptr) {
        next->prev = prev;
    } else {
        TAIL = prev;
    }

    node_to_delete->data.~T();
    m_allocator.do_deallocate(node_to_delete->block_start, sizeof(ListNode), alignof(ListNode));
    --m_size;

    return next_pos;
}


template<typename T, size_t BLOCK_SIZE>
void List<T, BLOCK_SIZE>::pop_front() {
    if (HEAD == nullptr) {
        throw std::out_of_range("List is empty");
    }

    ListNode* node_to_delete = HEAD;
    HEAD = HEAD->next;
    if (HEAD != nullptr) {
        HEAD->prev = nullptr;
    } else {
        TAIL = nullptr;
    }

    node_to_delete->data.~T();
    m_allocator.do_deallocate(node_to_delete->block_start, sizeof(ListNode), alignof(ListNode));
    --m_size;
}


template<typename T, size_t BLOCK_SIZE>
void List<T, BLOCK_SIZE>::pop_back() {
      if (TAIL == nullptr) {
        throw std::out_of_range("List is empty");
    }

    ListNode* node_to_delete = TAIL;
    TAIL = TAIL->prev;
    if (TAIL != nullptr) {
        TAIL->next = nullptr;
    } else {
        HEAD = nullptr;
    }

    node_to_delete->data.~T();
    m_allocator.do_deallocate(node_to_delete->block_start, sizeof(ListNode), alignof(ListNode));
    --m_size;
}  