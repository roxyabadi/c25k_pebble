#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "weeks_menu.h"
#include "stopwatch.h"


#define MY_UUID { 0x41, 0xD1, 0xDE, 0x3A, 0x83, 0xFD, 0x4B, 0x89, 0xB1, 0xD4, 0x1E, 0x2E, 0x9E, 0xC2, 0x71, 0x34 }
#define TIMER_UPDATE 1
PBL_APP_INFO(MY_UUID,
             "C25K", "roxyabadi",
             1, 0, 
             DEFAULT_MENU_ICON,
             APP_INFO_STANDARD_APP);

Window window;
AppContextRef app;



void handle_init(AppContextRef app_ctx) {
  app = app_ctx;

  window_init(&window, "C25K for Pebble");
  window_stack_push(&window, true );
  main_menu_init(&window);
}
void handle_timer(AppContextRef app_ctx, AppTimerHandle handle, uint32_t cookie) {
  app = app_ctx;
  (void)handle;

  do_timer(handle, cookie);
    
}


void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
    .timer_handler = &handle_timer
  };
  app_event_loop(params, &handlers);
}
