#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// given constraints - 16KB, 4-way associative set cache
#define BLOCK_BYTES 64
#define NUM_CACHE_LINES 256
#define NUM_WAYS_PER_SET 4

// as a note, the constraints mean we have 32 bit instruction where:
// 31:12 = tag, 11:6 = index (64 sets), 5:0 = offset (64 bytes per block)

// calculate the number of sets and step size across memroy
// num_sets = num_cache_lines / num_ways_per_set = 64
#define NUM_SETS 64
// step size = block_bytes * num_sets = 4096
#define STEP_SIZE 4096

// helper to traverse the physical cache memory with clever memory address access
int evict(void) {
    // calculate the number of safe memory we need, -1 comes because we iterate from 0
    size_t max_addr = ((NUM_WAYS_PER_SET - 1) * STEP_SIZE + (NUM_SETS - 1) * BLOCK_BYTES);

    // allocate some memory to make sure we can dereference real memory safely
    uint8_t *cache_mem = (uint8_t *)malloc(max_addr + BLOCK_BYTES); // add block bytes for buffer
    if (cache_mem == NULL) {
        printf("malloc failed");
        return 1;
    }

    for (int set = 0; set < NUM_SETS; set++) {
        size_t index_base = set * BLOCK_BYTES; // shifts the set index value in the 11:6 bits position, given 32 bit addr.

        for (int way = 0; way < NUM_WAYS_PER_SET; way++) {
            size_t addr = index_base + way * STEP_SIZE;
            // put in a dummy value at this address, to force a value into the corresponding cache.
            // doing this repeatedly for 4 times with different tag values (given by incrementing by way * step size) guarantees eviction for all 4 cache lines per set
            cache_mem[addr] = 1;
        }
    }
    // free dummy memory after eviction is complete
    free(cache_mem);
    return 0;
}

// a main to call evict() for testing
int main(void) {
    evict();
    return 0;
}