
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "controller.h"
#include "fan.h"
#include "thermal.h"

static FanControllerCb* callbacks [32];
static int num_callbacks = 0;

void controller_register_callback (FanControllerCb* cb)
{
	callbacks [num_callbacks ++] = cb;
}

static int controller_get_level (const int *thermals, int thermal_size)
{
	int ret = 0, i;
	if (num_callbacks == 0) return FAN_SPEED_AUTO;
	for (i = 0; i < num_callbacks; i ++) {
		int cur = (*callbacks[i]) (thermals, thermal_size); 
		if (ret < cur) ret = cur;
	}
	return ret;
}

static void controller_poll_and_set ()
{
	int ar[20];
	int size = thermal_get_temps (ar, sizeof(ar)/sizeof(int));
	int level;

	if (size <= 0) {
		fan_set_level (FAN_SPEED_AUTO);
		printf ("Unable to get thermals!\n");
		exit (0);
	}

	level = controller_get_level (ar, size);
	fan_set_level (level);
}

void controller_loop (int delay /* in seconds! */)
{
	for (;;) {
		controller_poll_and_set ();
		sleep (delay);
	}
}
