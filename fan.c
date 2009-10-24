
#include <assert.h>
#include <stdio.h>

#include "fan.h"

/* the fan controller file */
static const char* fan_file = "/proc/acpi/ibm/fan";
static const int watchdog_timeout = 10;

static int
fan_run_raw (const char* cmd)
{
	FILE *f = fopen (fan_file, "w");
	if (!f) return 0;
	fprintf (f, "%s\n", cmd);
	fflush (f);
	fclose (f);
	return 1;
}

static void
fan_set_watchdog ()
{
	char cmd[20];
	sprintf (cmd, "watchdog %d", watchdog_timeout);
	fan_run_raw (cmd);
}

int fan_is_supported ()
{
	return fan_run_raw ("level auto");
}

void fan_set_level (int level)
{
	char cmd [20];
	if (level == FAN_SPEED_AUTO) /* hardware control */
	{
		fan_run_raw ("level auto");
		return;
	} else if (level == 0) {

	}

	sprintf (cmd, "level %d", level);
	fan_run_raw (cmd);
	fan_set_watchdog ();
}

#ifdef SELF_TEST
int main ()
{
	int ret;
	ret = fan_is_supported ();
	
	printf ("fan_is_supported: %d\n", ret); 
	assert (ret); /* you're not running as root! */

	/* system calls, yes, I suck :( */
	system ("cat /proc/acpi/ibm/fan");
	printf ("-\n");
	fan_set_level (2);
	system ("cat /proc/acpi/ibm/fan");
	printf ("-\n");

	sleep (10);
	system ("cat /proc/acpi/ibm/fan");
	printf ("-\n");
	fan_set_level (0);
	sleep (10);
	system ("cat /proc/acpi/ibm/fan");
	printf ("-\n");
	fan_set_level (FAN_SPEED_AUTO);
	sleep (10);
	system ("cat /proc/acpi/ibm/fan");
	printf ("-\n");
}
#endif

