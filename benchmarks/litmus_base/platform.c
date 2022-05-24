// Code specific to the rocket-chip platform

#include "platform.h"
#include "util.h"
#include "io.h"
#include "log.h"
#include "arch.h"
#include "rand.h"
#include "test.h"
#include "testcase.h"
#include "heap.h"
#include <stdio.h>


// ==============
// Console output
// ==============

// Character buffer
// static char consoleBuffer[64] __attribute__((aligned(64)));
// static uint64_t consoleBufferLen = 0;

// void flush()
// {

//   printstr(consoleBuffer);

//   consoleBufferLen = 0;
// }

void put_char(char c)
{
  // consoleBuffer[consoleBufferLen++] = c;
  // if (c == '\n' || consoleBufferLen == sizeof(consoleBuffer)-1) {
  //   flush();
  //   consoleBufferLen = 0;
  // }
  putchar(c);

}
