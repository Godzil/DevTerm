Arduino 1.8.13

http://dan.drown.org/stm32duino/package_STM32duino_index.json

STM32F1xx/GD32F1xx boards 
by stm32duino version 2021.2.22

  GENERIC STM32F103R series

  gd32f1_generic_boot20_pc13.bin
  generic_boot20_pc13.bin
  

Changes from official firmware:
- Fn + Trackball no longer trigger the "slow movement mote" but allow to use the mouse scroll wheel 
  (only up/down for now, need to find how to set for left/right)
- Now to set the trackball speed you use Fn + Left button for normal speed 
- Fn + Middle button for "slow" speed
- Fn + Right button is currently an unused third mode that do the same as the normal one.
- Cmd now send LEFT META by default (left command or left windows key)
- Fn + Cmd send the RIGHT META Key.
- Fn + "-" (the key just on the right of the trackball) do send a volume mute key.

Undocumented from the official firmware (and not displayed on the keyboard):
- Fn + < to send the brightness decrease key
- Fn + > to send the brightness increase key

For the brightness setting, as far as I can say, on the CM3 model at least, there is nothing to honour these key, 
a deamon must probably need to be added for it to work.
  