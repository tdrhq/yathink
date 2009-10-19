
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "thermal.h"

static const char* thermal_file = "/proc/acpi/ibm/thermal";

int thermal_get_temps (int *ar, int size)
{
	FILE *f = fopen (thermal_file, "r");
	char bogus [100];
	int i;

	if (!f) return 0;

	fscanf (f, "%s", bogus);
	if (strcmp (bogus, "temperatures:") != 0) return 0;

	for (i = 0; i < size; i++) {
		if (fscanf (f, "%d", &ar[i]) <= 0) {
			fclose (f);
			return i;
		}
	}
	fclose (f);
	return 0; /* there were more thermals values than array size */
}

#ifdef SELF_TEST
static void print_array (int *ar, int size) {
	int i;
	printf ("[%d] ", size);
	for (i = 0; i < size; i++)
		printf ("%d ", ar[i]);
	printf ("\n");
	return;
}
int main ()
{
	int ar[100];
	int ret = thermal_get_temps (ar, 2);

	print_array (ar, ret);
	assert (ret == 0);

	ret = thermal_get_temps (ar, 100);
	print_array (ar, ret);
	
	return 0;
}
#endif
