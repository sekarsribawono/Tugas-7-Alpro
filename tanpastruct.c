#include <stdio.h>

int main() {
  double time[] = {0.0, 1.0, 2.0, 3.0};
  double temperature[] = {25.0, 25.8, 26.6, 27.4};
  int n = sizeof(time) / sizeof(time[0]);
  for (int i = 0; i < n; i++) {
    printf("Time: %.1f s, Temperature: %.1f C\n", time[i], temperature[i]);
  }
  return 0;
}