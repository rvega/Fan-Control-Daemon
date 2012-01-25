/*
 *  mbpfan.c - automatically control fan for MacBook Pro
 *  Copyright (C) 2010  Allan McRae <allan@archlinux.org>
 *  Modifications by Rafael Vega <rvega@elsoftwarehamuerto.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  20110811 - v1.1
 * 
 *  Notes: 
 *    Uses only the temperatures from the processors as input.
 *    Assumes two processors and one fan.
 *    Requires coretemp and applesmc kernel modules to be loaded.
 *
 *  Tested models:
 *    MacBook Pro 8.1 13"  (Intel i7 - Linux 3.2)
 */


#include <math.h>
#include <stdio.h>
#include <unistd.h>

/* lazy min/max... */
#define min(a,b) a < b ? a : b
#define max(a,b) a > b ? a : b

/* basic fan speed parameters */
unsigned short min_fan_speed=2000;
unsigned short max_fan_speed=6200;

/* temperature thresholds 
 * low_temp - temperature below which fan speed will be at minimum
 * high_temp - fan will increase speed when higher than this temperature
 * max_temp - fan will run at full speed above this temperature */
unsigned short low_temp=63;
unsigned short high_temp=66;
unsigned short max_temp=86;
/* unsigned short low_temp=55; */
/* unsigned short high_temp=65; */
/* unsigned short max_temp=80; */

/* temperature polling interval */
unsigned short polling_interval=10;


/* Controls the speed of the fan */
void set_fan_speed(unsigned short speed)
{
  FILE *file;

  file=fopen("/sys/devices/platform/applesmc.768/fan1_min", "w");
  fprintf(file, "%d", speed);
  fclose(file);
}


/* Takes "manual" control of fan */
/* void prepare_fan() */
/* { */
/*   FILE *file; */
/*  */
/*   file=fopen("/sys/devices/platform/applesmc.768/fan1_manual", "w"); */
/*   fprintf(file, "%d", 1); */
/*   fclose(file); */
/* } */


/* Returns average CPU temp in degrees (ceiling) */
unsigned short get_temp()
{
  FILE *file;
  unsigned short temp; 
  unsigned int t0, t1;
  
  file=fopen("/sys/devices/platform/coretemp.0/temp2_input", "r");
  fscanf(file, "%d", &t0);
  fclose(file);
  
  file=fopen("/sys/devices/platform/coretemp.0/temp3_input", "r");
  fscanf(file, "%d", &t1);
  fclose(file);
  
  temp = (unsigned short)(ceil((float)(t0 + t1) / 2000.));
  return temp;
}


int main()
{
  unsigned short old_temp, new_temp, fan_speed, steps;
  short temp_change;
  float step_up, step_down;
  
  /* prepare_fan(); */
  
  /* assume running on boot so set fan speed to minimum */
  new_temp = get_temp();
  fan_speed = 2000;
  set_fan_speed(fan_speed);
  sleep(polling_interval);

  step_up = (float)(max_fan_speed - min_fan_speed) / 
            (float)((max_temp - high_temp) * (max_temp - high_temp + 1) / 2);
  
  step_down = (float)(max_fan_speed - min_fan_speed) / 
              (float)((max_temp - low_temp) * (max_temp - low_temp + 1) / 2);
     
  while(1)
  {
    old_temp = new_temp;
    new_temp = get_temp();
    
    if(new_temp >= max_temp && fan_speed != max_fan_speed) {
      fan_speed = max_fan_speed;
    }
    
    if(new_temp <= low_temp && fan_speed != min_fan_speed) {
      fan_speed = min_fan_speed;
    }
    
    temp_change = new_temp - old_temp;
    
    if(temp_change > 0 && new_temp > high_temp && new_temp < max_temp) {
      steps = (new_temp - high_temp) * (new_temp - high_temp + 1) / 2;
      fan_speed = max(fan_speed, ceil(min_fan_speed + steps * step_up));
    }

    if(temp_change < 0 && new_temp > low_temp && new_temp < max_temp) {
      steps = (max_temp - new_temp) * (max_temp - new_temp + 1) / 2;
      fan_speed = min(fan_speed, floor(max_fan_speed - steps * step_down));
    }

    set_fan_speed(fan_speed);
    sleep(polling_interval);    
  }
  
  return 0;
}
