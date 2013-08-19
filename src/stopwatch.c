/*
Roxanna Aliabadi
roxannaaliabadi@gmail.com
This is a modified version of katherine's code in this project: github.com/Katharine/pebble-stopwatch/
*/
#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "common.h"
#include "c25k_pebble.h"
#include "c25k_logic.h"

//fonts
#define FONT_BIG_TIME RESOURCE_ID_FONT_DEJAVU_SANS_BOLD_SUBSET_30
#define FONT_SECONDS RESOURCE_ID_FONT_DEJAVU_SANS_SUBSET_18

//buttons
#define BUTTON_RUN BUTTON_ID_SELECT
#define BUTTON_RESET BUTTON_ID_UP

#define TIMER_UPDATE 1

//Global Variables
int c25k_week = 0;
int c25k_day = 0;
static Window window;
int seconds_elapsed = 0;

// Actually keeping track of time
static time_t elapsed_time = 0;
static bool started = false;
static AppTimerHandle update_timer = APP_TIMER_INVALID_HANDLE;
static time_t start_time = 0;
static time_t last_pebble_time = 0;

// Main display
static TextLayer big_time_layer;
static TextLayer seconds_time_layer;
static Layer line_layer;
static BmpContainer button_labels;
TextLayer hello_layer;


//functions
void start_stopwatch();
void stop_stopwatch();
void open_stopwatch(int day);
void stopwatch_init();
void sw_window_init();
char* get_welcome_text();
void draw_line(Layer *me, GContext* ctx);
void setupLayers();
void toggle_stopwatch_handler(ClickRecognizerRef recognizer, Window *window);
void reset_stopwatch_handler(ClickRecognizerRef recognizer, Window *window);
void config_provider(ClickConfig **config, Window *window);
enum status get_status();
void set_week(int week);
void update_stopwatch();
void do_timer(AppTimerHandle handle, uint32_t cookie);
void update_hello_layer(char* message);


//Initialize the stopwatch window
void stopwatch_init(){
  //Setup resources and inputs
  resource_init_current_app(&APP_RESOURCES);

  //Setup Displays
  sw_window_init();
  setupLayers();
  window_set_click_config_provider(&window, (ClickConfigProvider) config_provider);
  
  
  //Add Layers
  Layer *root_layer = window_get_root_layer(&window);
  layer_add_child(root_layer, &big_time_layer.layer);
  layer_add_child(root_layer, &seconds_time_layer.layer);
  layer_add_child(root_layer, &line_layer);
  layer_add_child(&window.layer, &hello_layer.layer);
  layer_add_child(root_layer, &button_labels.layer.layer);
  
}

//sets the global week variable
void set_week(int week){
  c25k_week = week;
}

//sets the global day variable and calls the stopwatch init function
void open_stopwatch(int day){
  c25k_day = day;
  stopwatch_init(app);
  set_times(c25k_week, c25k_day);
}

//button configuring
void config_provider(ClickConfig **config, Window *window) {
  config[BUTTON_ID_SELECT]->click.handler = (ClickHandler)toggle_stopwatch_handler;
  config[BUTTON_ID_UP]->click.handler = (ClickHandler)reset_stopwatch_handler;
  (void)window;
}

void toggle_stopwatch_handler(ClickRecognizerRef recognizer, Window *window){
  if(started){
    stop_stopwatch();
  }
  else{
    start_stopwatch();
  }
}

void start_stopwatch(){
  started = true;
  last_pebble_time = 0;
  start_time = 0;
  update_timer = app_timer_send_event(app, 100, TIMER_UPDATE);
}

void stop_stopwatch(){
  started = false;
}

void reset_stopwatch_handler(ClickRecognizerRef recognizer, Window *window){
  started = false;
  bool is_running = started;
  stop_stopwatch();
  elapsed_time = 0;
  start_time = 0;
  last_pebble_time = 0;
  if(is_running) start_stopwatch();
  update_stopwatch();
  text_layer_set_text(&hello_layer, get_welcome_text());
}

// Set up the main display layers
void setupLayers(){
  //setup
  resource_init_current_app(&APP_RESOURCES);
  GFont big_font = fonts_load_custom_font(resource_get_handle(FONT_BIG_TIME));
  GFont seconds_font = fonts_load_custom_font(resource_get_handle(FONT_SECONDS));
  
  //big time
  text_layer_init(&big_time_layer, GRect(0, 5, 96, 35));
  text_layer_set_background_color(&big_time_layer, GColorBlack);
  text_layer_set_font(&big_time_layer, big_font);
  text_layer_set_text_color(&big_time_layer, GColorWhite);
  text_layer_set_text(&big_time_layer, "00:00");
  text_layer_set_text_alignment(&big_time_layer, GTextAlignmentRight);
  
  //Seconds
  text_layer_init(&seconds_time_layer, GRect(96, 17, 49, 35));
  text_layer_set_background_color(&seconds_time_layer, GColorBlack);
  text_layer_set_font(&seconds_time_layer, seconds_font);
  text_layer_set_text_color(&seconds_time_layer, GColorWhite);
  text_layer_set_text(&seconds_time_layer, ".0");
  
  //line
  layer_init(&line_layer, GRect(0, 45, 144, 2));
  line_layer.update_proc = &draw_line;
  
  //hello week layer
  text_layer_init(&hello_layer, GRect(0, 65, 144, 30));
  text_layer_set_background_color(&hello_layer, GColorBlack);
  text_layer_set_font(&hello_layer, big_font);
  text_layer_set_text_color(&hello_layer, GColorWhite);
  text_layer_set_text_alignment(&hello_layer, GTextAlignmentCenter);
  text_layer_set_text(&hello_layer, get_welcome_text());
  text_layer_set_font(&hello_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  
  //buttons
  bmp_init_container(RESOURCE_ID_IMAGE_BUTTON_LABELS, &button_labels);
  layer_set_frame(&button_labels.layer.layer, GRect(130, 10, 14, 136));
    
}


void draw_line(Layer *me, GContext* ctx) {
  graphics_context_set_stroke_color(ctx, GColorWhite);
  graphics_draw_line(ctx, GPoint(0, 0), GPoint(140, 0));
  graphics_draw_line(ctx, GPoint(0, 1), GPoint(140, 1));
}

char* get_welcome_text(){
  if(c25k_week == 1){
    return "Week 1!";
  }
  else if(c25k_week == 2){
    return "Week 2!";
  }
  else if(c25k_week == 3){
    return "Week 3!";
  }
  else if(c25k_week == 4){
    return "Week 4!";
  }
  else if(c25k_week == 5){
    return "Week 5!";
  }
  else if(c25k_week == 6){
    return "Week 6!";
  }
  else if(c25k_week == 7){
    return "Week 7!";
  }
  else if(c25k_week == 8){
    return "Week 8!";
  }
  else if(c25k_week == 9){
    return "Week 9!";
  }
  else{
    return "Week 0?";
  }
}

void sw_window_init(){
  window_init(&window, "Stopwatch");
  window_stack_push(&window, true /* Animated */);
  window_set_background_color(&window, GColorBlack);
  window_set_fullscreen(&window, false);
}
void do_timer(AppTimerHandle handle, uint32_t cookie){
  
  if(cookie == TIMER_UPDATE) {
    if(started) {
      elapsed_time += 100;
      // Every tick of the pebble clock, force our time back to it.
      time_t pebble_time = get_pebble_time();
      if(!last_pebble_time) last_pebble_time = pebble_time;
      if(pebble_time > last_pebble_time) {
	// If it's the first tick, instead of changing our time we calculate the correct time.
	if(!start_time) {
	  start_time = pebble_time - elapsed_time;
	} else {
	  elapsed_time = pebble_time - start_time;
	}
	last_pebble_time = pebble_time;
      }
      update_timer = app_timer_send_event(app, elapsed_time <= 3600000 ? 100 : 1000, TIMER_UPDATE);
    }
    update_stopwatch();
  }
}


void update_stopwatch() {
  static char big_time[] = "00:00";
  static char deciseconds_time[] = ".0";
  static char seconds_time[] = ":00";

  elapsed_time += 20;
  // Now convert to hours/minutes/seconds.
  int tenths = (elapsed_time / 100) % 10;
  int seconds = (elapsed_time / 1000) % 60;
  int minutes = (elapsed_time / 60000) % 60;
  int hours = elapsed_time / 3600000;
  //update_hello_layer("1");
  //if(seconds == 0 || seconds ==30){
  check_alerts(seconds, minutes);
  //}
  //update_hello_layer("3");

  // We can't fit three digit hours, so stop timing here.
  if(hours > 99) {
    stop_stopwatch();
    return;
  }
  if(hours < 1)
    {
      itoa2(minutes, &big_time[0]);
      itoa2(seconds, &big_time[3]);
      itoa1(tenths, &deciseconds_time[1]);
    }
  else
    {
      itoa2(hours, &big_time[0]);
      itoa2(minutes, &big_time[3]);
      itoa2(seconds, &seconds_time[1]);
    }
  // Now draw the strings.
  text_layer_set_text(&big_time_layer, big_time);
  text_layer_set_text(&seconds_time_layer, hours < 1 ? deciseconds_time : seconds_time);
}
void update_hello_layer(char* message){
  text_layer_set_text(&hello_layer, message);
}
