#include <stdio.h>

int main()
{
  float ttf = 16777216;   // 2^24
  float delta = 1.0/ttf;  // 0.000000059604645
  float sum = 0.0f; 

  // check inputs
  printf("Starting with sum=%1.18f, delta=%1.18f:\n\n", sum, delta);

  // should add to one
  for (int i=0; i<ttf; i++) sum += delta;
  printf("sum=%1.18f\n", sum);
  
  // what happens if we keep adding?
  for (int i=0; i<ttf; i++) sum += delta;
  printf("sum=%1.18f\n", sum);
}
