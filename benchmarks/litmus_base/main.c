#include "io.h"
#include "log.h"
#include "platform.h"
#include "arch.h"
#include "rand.h"
#include "test.h"
#include "testcase.h"
#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void thread_entry(int cid, int nc)
{
  // Processes not being used spin here
  if (cid >= NUM_PROCESSES) while (1);

  // static allocates data in the binary, which is visible to both threads, for head start, hash and share variable LOC
  static char allocated_ram[TOTAL_DATA_SIZE];
  // printf("RAM data address of thread %u is 0x%x\n!",cid,&allocated_ram);

  if (cid == 0) {
    printf("the static ram size is %u \n", sizeof(allocated_ram));
    log_init(allocated_ram);
  }
  barrier(nc);
  // Random seed
  uint32_t seed = 0;

  for (int i = 0; i < NUM_ITERATIONS; i++) {
    printf("TEST RUN %d of litmus. \n", i);
    if (cid == 0) test_init(&seed, allocated_ram);
    barrier(nc);
    printf("TEST RUN %d of litmus test body. \n", i);
    test_body(cid);
    barrier(nc);
    if (cid == 0) log_update();
    barrier(nc);
  }

  if (cid == 0) {
    put_string("Observed outcomes:\n");
    log_display();
  }

  barrier(nc);
  // printf("\n \\\\\\\\\\\\\\\\EXIT THREAD_ENTRY from Hart %u\\\\\\\\\\ \n", cid);
  exit(0);

}
