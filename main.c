
#include <stdio.h>
#include <stdlib.h>

#include "controller.h"
#include "fan.h"

int controller_default_cb (const int *thermals, int size) 
{
	int max = 0, i;
	for (i = 0; i < size; i ++) 
		max = (max > thermals[i] ? max : thermals[i]);
	
	printf ("got max: %d\n", max);
	if (max <= 45) return 0;
	if (max <= 50) return 1;
	if (max <= 56) return 2;
	if (max <= 60) return 3;
	return FAN_SPEED_AUTO;
}

int main (int argc, char **argv)
{
	if (!fan_is_supported ()) {
		fprintf (stderr, "Fan not available, or no permissions to "
			 "access the fan\n");
		exit (0);
	}

	controller_register_callback (controller_default_cb);

	controller_loop (1);
	return 0;
}
