/*
 * clockworkpi devterm trackball 
 */
#include "keys_io_map.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <USBComposite.h>

#include "trackball.h"


int btn_state;
int btn_read_state;
unsigned long btn_current_action_time;
unsigned long btn_last_action_time;

// mouse move
int x_move, y_move;
Direction x_direction(LEFT_PIN, RIGHT_PIN);
Direction y_direction(UP_PIN, DOWN_PIN);

TrackSpeed Normal_ts;
TrackSpeed Detail_ts;
TrackSpeed *ts_ptr;

enum tbmode_t tb_mode = TB_NORMAL_MODE;

void trackball_set_mode(enum tbmode_t mode)
{
    tb_mode = mode;
}

void trackball_task(DEVTERM*dv) {

    switch(tb_mode)
    {
    default:
    case TB_NORMAL_MODE:
        ts_ptr = &Normal_ts;
        break;
    case TB_PRECISION_MODE:
        ts_ptr = &Detail_ts;
        break;
    }

  x_direction.ts = ts_ptr;
  y_direction.ts = ts_ptr;
  
  btn_read_state = digitalRead(BTN_PIN);
  
  if(btn_read_state != btn_state) {
    btn_current_action_time = millis();
    if(btn_current_action_time - btn_last_action_time > ts_ptr->bounce_interval ) {
      btn_state = btn_read_state;
      btn_last_action_time = btn_current_action_time;

      if(btn_state == HIGH) {
        dv->Mouse->release();
      } else {
        dv->Mouse->press();
      }
    }
  }

  x_move = x_direction.read_action();
  y_move = y_direction.read_action();

  if(x_move != 0 || y_move != 0)
  {
      if (dv->Keyboard_state.fn_on > 0)
      {
          /* If fn is pressed, send wheel change */
          dv->Mouse->move(0, 0, y_move);
      }
      else
      {
          /* Else, send mouse movement */
          dv->Mouse->move(x_move, y_move, 0);
      }
  }
  
}


void trackball_init(DEVTERM*)
{
  pinMode(BTN_PIN,INPUT);

  Normal_ts.bounce_interval = 30;
  Normal_ts.base_move_pixels = 5;
  Normal_ts.exponential_bound = 14;
  Normal_ts.exponential_base = 1.2;

  Detail_ts.bounce_interval = 100;
  Detail_ts.base_move_pixels = 3;
  Detail_ts.exponential_bound = 10;
  Detail_ts.exponential_base = 1.2;
}
