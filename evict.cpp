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
    return 0;
}
// a main to call evict() for testing
int main(void) {
    evict();
    return 0;
}