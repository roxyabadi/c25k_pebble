/*
8/11/2013
Roxy Aliabadi 
roxannaaliabadi@gmail.com
Menu to select which week of C25K you are on
*/
#include "pebble_os.h"
#include "stopwatch.h"
#include "days_menu.h"

static void select_week(int index, void* context);

//from stopwatch.h
void open_stopwatch(int day);
void set_week(int week);

//from days_menu.h
void open_days_menu();

static SimpleMenuItem main_menu_items[] = {
  {
    .title = "Week 1",
    .callback = select_week,
  },
  {
    .title = "Week 2",
    .callback = select_week,
  },
  {
    .title = "Week 3",
    .callback = select_week,
  },
  {
    .title = "Week 4",
    .callback = select_week,
  },
  {
    .title = "Week 5",
    .callback = select_week,
  },
  {
    .title = "Week 6",
    .callback = select_week,
  },
  {
    .title = "Week 7",
    .callback = select_week,
  }, 
  {
    .title = "Week 8",
    .callback = select_week,
  },
  {
    .title = "Week 9",
    .callback = select_week,
  },
};

static SimpleMenuSection section = {
  .items = main_menu_items,
  .num_items = ARRAY_LENGTH(main_menu_items),
};

static SimpleMenuLayer main_menu_layer;


void main_menu_init(Window* window) {
  simple_menu_layer_init(&main_menu_layer, GRect(0, 0, 144, 152), window, &section, 1, NULL);
  layer_add_child(window_get_root_layer(window), simple_menu_layer_get_layer(&main_menu_layer));
}

static void select_week(int index, void* context) {
  set_week(index+1);
  open_days_menu();
}
