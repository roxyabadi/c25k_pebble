/*
8/13/2013
Roxy Aliabadi 
roxannaaliabadi@gmail.com
Menu to select which day of C25K you are on
*/
#include "pebble_os.h"
#include "stopwatch.h"

static void select_day(int index, void* context);
void day_menu_init();
static Window window;

//from stopwatch.h
void open_stopwatch(int day);

static SimpleMenuItem day_menu_items[] = {
  {
    .title = "Day 1",
    .callback = select_day,
  },
  {
    .title = "Day 2",
    .callback = select_day,
  },
  {
    .title = "Day 3",
    .callback = select_day,
  },
};

static SimpleMenuSection section = {
  .items = day_menu_items,
  .num_items = ARRAY_LENGTH(day_menu_items),
};

static SimpleMenuLayer day_menu_layer;

void open_days_menu(){
  day_menu_init();
}

void day_menu_init() {
  window_init(&window, "Select Day");
  window_stack_push(&window, true /* Animated */);
  simple_menu_layer_init(&day_menu_layer, GRect(0, 0, 144, 152), &window, &section, 1, NULL);
  layer_add_child(window_get_root_layer(&window), simple_menu_layer_get_layer(&day_menu_layer));
}

static void select_day(int index, void* context) {
  open_stopwatch(index+1);
}
