#pragma once

#include <memory>
#include <vector>


struct BlockInfo {
    size_t offset;
    size_t user_data_size;
    bool is_free;
};

template<typename T, size_t BLOCK_SIZE>
class Allocator : public std::pmr::memory_resource {
private:
    std::vector<char> memory_pool;
    std::vector<BlockInfo> block_info;

    
public:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void do_deallocate(void* p, size_t bytes, size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

    Allocator();
    ~Allocator() noexcept = default;

    Allocator(const Allocator& other);
    Allocator& operator=(const Allocator& other); 
};


#include "allocator.ipp"