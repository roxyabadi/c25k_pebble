/*
Roxanna Aliabadi
roxannaaliabadi@gmail.com
This is a modified version of katherine's code in this project: github.com/Katharine/pebble-stopwatch/
*/
#include "pebble_os.h"

void open_stopwatch(int day);
void set_week(int week);
void do_timer(AppTimerHandle handle, uint32_t cookie);
void update_hello_layer(char* message);
