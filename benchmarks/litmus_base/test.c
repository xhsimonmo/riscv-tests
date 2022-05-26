#include "io.h"
#include "test.h"
#include "arch.h"
#include "rand.h"
#include "heap.h"


// ================
// Global variables
// ================

test_t test;

// =========
// Functions
// =========

void test_init(uint32_t* seed, const char* allocated_ram)
{
  // Randomize variable locations
  uint32_t rs[NUM_VARS];
  // LOCS region starts after headstart and hash
  const char* LOCS_BASE = allocated_ram + NUM_HEADSTARTS*sizeof(headstart_t) + HASH_TABLE_SIZE*sizeof(log_entry_t);
  for (int i = 0; i < NUM_VARS; i++) {
    retry:
      rs[i] = rand_k(seed, NUM_LOCS - 1);
      for (int j = 0; j < i; j++)
        if (rs[i] == rs[j]) goto retry;
  }
  //printf("TEST INIT: LOCS_BASE is 0x%x \n", LOCS_BASE);
  // Intialise variables
  test.locs = (var_t*) LOCS_BASE;
  for (int i = 0; i < NUM_VARS; i++) {
    test.vars[i] = &test.locs[rs[i]*LOC_GRAIN];
    // printf("TEST INIT: randomly generated shared location: 0x%x\n", test.vars[i]);
    *test.vars[i] = 0;
  }

  // for (int i = 0; i < NUM_PROCESSES; i++)
  //   printf("TEST INIT: test start time[%u]: %u\n",i, test.start_times[i]);

  // Set random start delays
  uint32_t max = 0;
  for (int i = 0; i < NUM_PROCESSES; i++)
    if (test.start_times[i] > max) max = test.start_times[i];

  for (int i = 0; i < NUM_PROCESSES; i++){
    test.delays[i] = rand_k(seed, test.start_times[i] < max ? 6 : 2);
    // printf("TEST INIT: test delay of hart %u is set to be %u\n",i, test.delays[i]);
    }
}

inline void delay(int n)
{
  for (int i = 0; i < n; i++)
    asm volatile ("nop\n");
}

// Include the automatically-generated litmus test 
#include "testcase.c"
