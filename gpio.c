#include <stdio.h>
#include <string.h>
#include <wiringPi.h>

static volatile int key_a_state = 0;
static volatile int key_b_state = 1;

static void set_key_a_state (int val)
{
	key_a_state = val;
}

static int get_key_a_state (void)
{
	return key_a_state;
}

static void set_key_b_state (int val)
{
	key_b_state = val;
}

static int get_key_b_state (void)
{
	return key_b_state;
}


void key_a_handler (void)
{
	printf ("key A down\r\n");
	if (get_key_a_state () == 0) {
		set_key_a_state (1);
	} else {
		set_key_a_state (0);
	}
}

void key_b_handler (void)
{
	printf ("key B down\r\n");
	if (get_key_b_state() == 0) {
		set_key_b_state (1);
	} else {
		set_key_b_state (0);
	}
}



int main (void)
{
	wiringPiSetup ();
	pinMode (25, INPUT);
	pinMode (27, INPUT);
	pullUpDnControl (25, PUD_UP);
	pullUpDnControl (27, PUD_UP);
	wiringPiISR (25, INT_EDGE_FALLING, key_b_handler);
	wiringPiISR (27, INT_EDGE_FALLING, key_a_handler);
	pinMode (34, OUTPUT);
	pinMode (35, OUTPUT);
	pinMode (36, OUTPUT);
	pinMode (37, OUTPUT);
	pinMode (38, OUTPUT);
	for (;;)
	{
		if (get_key_a_state () == 1) {
			digitalWrite (34, HIGH);
			delay (500);
			digitalWrite (34, LOW);	
			delay (500);
		}
		if (get_key_b_state () == 1) {
			digitalWrite (36, HIGH);
			delay (500);
			digitalWrite (36, LOW);
			delay (500);
		}
 	}


}

