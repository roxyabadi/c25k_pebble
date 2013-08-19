//Couch 2 5K logic
#include "pebble_os.h"
#include "pebble_app.h"
#include "stopwatch.h"

struct ttime{
  int minutes;
  int seconds;
  char* action;
};
int next_time;
int max_time;

void check_alerts(int seconds, int minutes);
void set_times(int week, int day);
void alert(char* message);
struct ttime get_ttime(int min, int sec, char* act);
struct ttime trig_times[19];



void check_alerts(int seconds, int minutes){
  if(next_time<= max_time){
    if(minutes == trig_times[next_time].minutes && seconds == trig_times[next_time].seconds){
      alert(trig_times[next_time].action);
      next_time++;
    }
  }
}

void alert(char* message){
  vibes_long_pulse();
  update_hello_layer(message);
}

void set_times(int week, int day){
  next_time = 0;
  
  //fix times here
  trig_times[0] = get_ttime(0,0, "WARM UP");
  trig_times[1] = get_ttime(5,0, "RUN");
  if(week == 1){
    //week 1
    trig_times[2] = get_ttime(6,0, "WALK");
    trig_times[3] = get_ttime(7,30, "RUN");
    trig_times[4] = get_ttime(8,30, "WALK");
    trig_times[5] = get_ttime(10,0, "RUN");
    trig_times[6] = get_ttime(11,0, "WALK");
    trig_times[7] = get_ttime(10,0, "RUN");
    trig_times[8] = get_ttime(13,30, "WALK");
    trig_times[9] = get_ttime(15,0, "RUN");
    trig_times[10] = get_ttime(16,0, "WALK");
    trig_times[11] = get_ttime(17,30, "RUN");
    trig_times[12] = get_ttime(18,30, "WALK");
    trig_times[13] = get_ttime(20,0, "RUN");
    trig_times[14] = get_ttime(21,0, "WALK");
    trig_times[15] = get_ttime(22,30, "RUN");
    trig_times[16] = get_ttime(23,30, "WALK");
    trig_times[17] = get_ttime(25,0, "COOL DOWN");
    trig_times[18] = get_ttime(30,0, "END");
    max_time = 18;
  }else if(week ==2){
    //week 2
    trig_times[2] = get_ttime(6,30, "WALK");
    trig_times[3] = get_ttime(8,30, "RUN");
    trig_times[4] = get_ttime(10,0, "WALK");
    trig_times[5] = get_ttime(12,0, "RUN");
    trig_times[6] = get_ttime(13,30, "WALK");
    trig_times[7] = get_ttime(15,0, "RUN");
    trig_times[8] = get_ttime(17,0, "WALK");
    trig_times[9] = get_ttime(19,0, "RUN");
    trig_times[10] = get_ttime(20,30, "WALK");
    trig_times[11] = get_ttime(22,30, "RUN");
    trig_times[12] = get_ttime(24,0, "WALK");
    trig_times[13] = get_ttime(26,0, "COOL DOWN");
    trig_times[14] = get_ttime(31,0, "END");
    max_time = 14;
  }else if(week == 3){
    //week 3
    trig_times[2] = get_ttime(6,30, "WALK");
    trig_times[3] = get_ttime(8,00, "RUN");
    trig_times[4] = get_ttime(11,0, "WALK");
    trig_times[5] = get_ttime(14,00, "RUN");
    trig_times[6] = get_ttime(15,30, "WALK");
    trig_times[7] = get_ttime(17,00, "RUN");
    trig_times[8] = get_ttime(20,0, "WALK");
    trig_times[9] = get_ttime(23,0, "RUN");
    trig_times[10] = get_ttime(24,30, "WALK");
    trig_times[13] = get_ttime(26,0, "COOL DOWN");
    trig_times[14] = get_ttime(31,0, "END");
    max_time = 14;
  }else if(week == 4){
    //week 4
    trig_times[2] = get_ttime(8,0, "WALK");
    trig_times[3] = get_ttime(9,30, "RUN");
    trig_times[4] = get_ttime(14,30, "WALK");
    trig_times[5] = get_ttime(17,00, "RUN");
    trig_times[6] = get_ttime(20,0, "WALK");
    trig_times[7] = get_ttime(25,0, "RUN");
    trig_times[8] = get_ttime(30,0, "COOL DOWN");
    trig_times[9] = get_ttime(35,0, "END");
    max_time = 9;
  }else if(week == 5){
    if(day == 1){
      //week 5 day 1
      trig_times[2] = get_ttime(10,0, "WALK");
      trig_times[3] = get_ttime(13,0, "RUN");
      trig_times[4] = get_ttime(18,0, "WALK");
      trig_times[5] = get_ttime(21,00, "RUN");
      trig_times[6] = get_ttime(26,0, "COOL DOWN");
      trig_times[7] = get_ttime(31,0, "END");
      max_time = 7;
    }else if(day == 2){
      //week 5 day 2
      trig_times[2] = get_ttime(13,0, "WALK");
      trig_times[3] = get_ttime(18,0, "RUN");
      trig_times[4] = get_ttime(26,0, "COOL DOWN");
      trig_times[5] = get_ttime(31,00, "END");
      max_time = 5;
    }else if(day ==3){
      //week 5 day 3
      trig_times[2] = get_ttime(25,0, "COOL DOWN");
      trig_times[3] = get_ttime(30,00, "END");
      max_time = 3;
    }
  }else if(week == 6){
    if(day ==1){
      //week 6 day 1
      trig_times[2] = get_ttime(10,0, "WALK");
      trig_times[3] = get_ttime(13,0, "RUN");
      trig_times[4] = get_ttime(21,0, "WALK");
      trig_times[5] = get_ttime(24,00, "RUN");
      trig_times[6] = get_ttime(29,0, "COOL DOWN");
      trig_times[7] = get_ttime(34,0, "END");
      max_time = 7;
    }else if(day==2){
      //week 6 day 2
      trig_times[2] = get_ttime(15,0, "WALK");
      trig_times[3] = get_ttime(18,0, "RUN");
      trig_times[4] = get_ttime(28,0, "COOL DOWN");
      trig_times[5] = get_ttime(33,00, "END");
      max_time = 5;
    }else if(day==3){
      //week 6 day 3
      trig_times[2] = get_ttime(25,0, "COOL DOWN");
      trig_times[3] = get_ttime(30,00, "END");
      max_time = 3;
    }
  }else if(week ==7){
    //week 7
    trig_times[2] = get_ttime(30,0, "COOL DOWN");
    trig_times[3] = get_ttime(35,00, "END");
    max_time = 3;
  }else if(week == 8){
    //week 8
    trig_times[2] = get_ttime(33,0, "COOL DOWN");
    trig_times[3] = get_ttime(38,00, "END");
    max_time = 3;
  }else if(week == 9){
    //week 9
    trig_times[2] = get_ttime(35,0, "COOL DOWN");
    trig_times[3] = get_ttime(40,00, "END");
    max_time = 3;
  }
}

struct ttime get_ttime(int min, int sec, char* act){
  struct ttime this_ttime;
  this_ttime.minutes = min;
  this_ttime.seconds = sec;
  this_ttime.action = act;
  return this_ttime;
}
