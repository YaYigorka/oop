#include "allocator.hpp"


template<typename T, size_t BLOCK_SIZE>
Allocator<T, BLOCK_SIZE>::Allocator()
    : memory_pool(BLOCK_SIZE * sizeof(T))
{
    block_info.push_back({
        .offset = 0,
        .user_data_size = memory_pool.size(),
        .is_free = true
    });
}


template<typename T, size_t BLOCK_SIZE>
Allocator<T, BLOCK_SIZE>::Allocator(const Allocator& other)
    : memory_pool{other.memory_pool}
    , block_info{other.block_info}
{
}


template<typename T, size_t BLOCK_SIZE>
Allocator<T, BLOCK_SIZE>& Allocator<T, BLOCK_SIZE>::operator=(const Allocator& other) {
    memory_pool = other.memory_pool;
    block_info = other.block_info;
    return *this;
}


template<typename T, size_t BLOCK_SIZE>
void* Allocator<T, BLOCK_SIZE>::do_allocate(size_t bytes, size_t alignment) {
    for (auto it = block_info.begin(); it != block_info.end(); ++it) {
        if (it->is_free && it->user_data_size >= bytes) {
            void* ptr = &memory_pool[it->offset];

            if (it->user_data_size > bytes) {
                BlockInfo new_block = {
                    .offset = it->offset + bytes,
                    .user_data_size = it->user_data_size - bytes,
                    .is_free = true
                };
                
                it->user_data_size = bytes;
                it->is_free = false;

                block_info.insert(std::next(it), new_block);
            } else {
                it->is_free = false;
            }

            return ptr;
        }
    }

    throw std::bad_alloc();
}


template<typename T, size_t BLOCK_SIZE>
void Allocator<T, BLOCK_SIZE>::do_deallocate(void* p, size_t bytes, size_t alignment) {
    char* char_ptr = static_cast<char*>(p);
    char* start_ptr = memory_pool.data();
    size_t offset = char_ptr - start_ptr;

    for (auto it = block_info.begin(); it != block_info.end(); ++it) {
        if (it->offset == offset) {
            it->is_free = true;
            return;
        }
    }
}


template<typename T, size_t BLOCK_SIZE>
bool Allocator<T, BLOCK_SIZE>::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}