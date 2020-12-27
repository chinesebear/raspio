#include <stdio.h>
#include <string.h>
#include <wiringPi.h>

static volatile int pwm_period = 500;

static int pwm_period_read (void)
{
	return pwm_period;
}

static void pwm_sub (int val)
{
	if (pwm_period <= val) {
		printf ("Fail to sub, period = %d \r\n", pwm_period * 2);
		return;
	}
	pwm_period -= val;
	printf ("pwm period sub, period = %d\r\n", pwm_period * 2);
}

static void pwm_add (int val)
{
	if (pwm_period >= 30000) {
		pwm_period = 30000;
		printf ("Fail to add, period = %d \r\n", pwm_period * 2);
		return;
	}
	pwm_period += val;
	printf ("pwm period add, period = %d\r\n", pwm_period * 2);
}

static void pwm_sub_handler (void)
{
	pwm_sub (1);
}

static void pwm_add_handler (void)
{
	pwm_add (1);
}

static void pwm_acc (void)
{
	int add = digitalRead (27);
	int sub = digitalRead (25);
	if (add == LOW) {
		pwm_add (1);
	}
	if (sub == LOW) {
		pwm_sub (1);
	}
}

int main (void)
{
	wiringPiSetup();
	pinMode (25, INPUT);
	pinMode (27, INPUT);
	pullUpDnControl (25, PUD_UP);
	pullUpDnControl (27, PUD_UP);
	wiringPiISR (25, INT_EDGE_FALLING, pwm_sub_handler);
	wiringPiISR (27, INT_EDGE_FALLING, pwm_add_handler);
	pinMode (34, OUTPUT);
	pinMode (35, OUTPUT);
	pinMode (36, OUTPUT);
	pinMode (37, OUTPUT);
	for (;;) {
		pwm_acc ();
		digitalWrite (34, HIGH);
		digitalWrite (35, HIGH);
		digitalWrite (36, HIGH);
		digitalWrite (37, HIGH);
		delay (pwm_period);
		digitalWrite (34, LOW);
		digitalWrite (35, LOW);
		digitalWrite (36, LOW);
		digitalWrite (37, LOW);
		delay (pwm_period);
	}

}
