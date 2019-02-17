#ifndef _UNICORNSIMPLEHEAP
#define _UNICORNSIMPLEHEAP

#include <unicorn/unicorn.h>
#include <iostream>
#include <vector>

#define UNICORN_PAGE_SIZE 0x1000

#define DEBUG(fmt,...) do { \
  if (debug_trace) { printf(fmt, ##__VA_ARGS__); putchar('\n'); } \
} while (0)

inline uint64_t ALIGN_PAGE_DOWN(uint64_t x) { return x & ~(UNICORN_PAGE_SIZE - 1); }
inline uint64_t ALIGN_PAGE_UP(uint64_t x) { return (x + UNICORN_PAGE_SIZE - 1) & ~(UNICORN_PAGE_SIZE-1); }


struct HeapChunk{
    uint32_t addr;
    uint32_t size;
};

class UnicornSimpleHeap{
private:
    uc_engine *uc;
    bool debug_trace;
    std::vector<HeapChunk> chunks;
        
    enum{
        HEAP_MIN_ADDR = 0x40002000,
        HEAP_MAX_ADDR = 0xFFFFFFFF
    };
public:
    UnicornSimpleHeap(uc_engine* _uc, bool _debug_trace);
    uint32_t malloc(uint32_t size);
};

#endif