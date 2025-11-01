#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// given constraints - 16KB, 4-way associative set cache
#define BLOCK_BYTES 64
#define NUM_CACHE_LINES 256
#define NUM_WAYS_PER_SET 4

// calculate the number of sets and step size across memroy
// num_sets = num_cache_lines / num_ways_per_set = 64
#define NUM_SETS 64
// step size = block_bytes * num_sets = 4096
#define STEP_SIZE 4096