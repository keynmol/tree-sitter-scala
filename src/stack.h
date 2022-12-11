
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define LOG(args...) fprintf(stderr, args);

typedef struct ScannerStack {
  unsigned int stack[256];
  int top;
} ScannerStack;

ScannerStack* createStack() {
  ScannerStack* ptr = (ScannerStack*) malloc(sizeof(ScannerStack));

  ptr -> top = 0;
  memset(ptr -> stack, 256, (0));

  return ptr;
}

bool isEmptyStack(ScannerStack *stack) { return stack->top == 0; }

int peekStack(ScannerStack *stack) {
  return isEmptyStack(stack) ? -1 : stack->stack[stack->top - 1];
}

void pushStack(ScannerStack *stack, unsigned int value) {
  stack->top++;
  stack->stack[stack->top - 1] = value;
}

int popStack(ScannerStack *stack) {
  if (isEmptyStack(stack))
    return -1;
  else {
    int result = peekStack(stack);
    stack->top--;

    return result;
  }
}

void printStack(ScannerStack *stack, char *msg) {
  LOG("%s Stack[top = %d; ", msg, stack->top);
  for (int i = 0; i < stack->top; i++) {
    LOG("%d | ", stack->stack[i]);
  }
  LOG("]\n");
}

unsigned serialiseStack(ScannerStack *stack, char *buf) {
  unsigned elements = isEmptyStack(stack) ? 0 : stack->top;
  unsigned result_length = elements * sizeof(int);
  int *placement = (int *)buf;

  for (int i = 0; i < elements; i++) {
    placement[i] = stack->stack[i];
  }

  return result_length;
}

void deserialiseStack(ScannerStack* stack, const char* buf, unsigned n) {
  if (n != 0) {
    int *intBuf = (int *)buf;

    int elements = n / sizeof(int);
    stack->top = elements;
    for (int i = 0; i < elements; i++) {
      stack->stack[i] = intBuf[i];
    }
  }
}

void resetStack(ScannerStack *p) { p->top = 0; }
