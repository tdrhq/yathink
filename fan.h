
#define FAN_SPEED_AUTO 255
#define FAN_SPEED_FULL_SPEED 256

/**
 * Set's the fan level, 0 - disabled, 1-6 normal speeds, 
 * and 7 is full-speed. In addition, the constants FAN_SPEED_AUTO
 * may be used to reset to hardware control.
 * 
 * On my X200, setting a level works for a few seconds (unless level
 * is 0), after which it goes back to auto. You shouldn't rely on this
 * behavior and manually set back to auto once you're done with it.
 */
void fan_set_level (int level);

/**
 * Determines is you have permissions to change the fan speed.
 */
int fan_is_supported (void);
