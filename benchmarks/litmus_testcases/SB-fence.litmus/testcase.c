/* Automatically generated by litmus */

void test_body(int pid) {
  switch(pid) {
    case 0: {
      var_t out0;
      arch_barrier_up();
      delay(test.delays[0]*12);
      test.start_times[0] = arch_get_counter();
      asm volatile (
        // "fence         \n"
        // " li a0,2      \n"
        // " sw a0,0( %2) \n"
        //
        " li a0,1      \n"
        " sw a0,0( %1) \n"
        "fence         \n"
        " lw %0,0( %2) \n"
        // "fence         \n"
      : /* output operands */
        "=&r"(out0)
      : /* input operands */
        "r"(test.vars[0]),"r"(test.vars[1])
      : /* clobbered registers */
        "a0"
      );
      test.outcome[0] = out0;
      arch_barrier_down();
      break;
    }
    case 1: {
      var_t out0;
      arch_barrier_up();
      delay(test.delays[1]*12);
      test.start_times[1] = arch_get_counter();
      asm volatile (
        // "fence         \n"
        // " li a0,0      \n"
        // " sw a0,0( %2) \n"
        
        " li a0,1      \n"
        " sw a0,0( %1) \n"
        "fence         \n"
        " lw %0,0( %2) \n"
        // "fence         \n"
      : /* output operands */
        "=&r"(out0)
      : /* input operands */
        "r"(test.vars[1]),"r"(test.vars[0])
      : /* clobbered registers */
        "a0"
      );
      test.outcome[1] = out0;
      arch_barrier_down();
      break;
    }
  }
}
