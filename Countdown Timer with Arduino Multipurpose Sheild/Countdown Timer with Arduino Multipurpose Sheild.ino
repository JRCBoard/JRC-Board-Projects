#include <MFShield.h>

/* ======== USER SETTINGS =========== */
// special effects
#define ENABLE_TICK_SOUND				true
#define ENABLE_BUTTON_SOUND			true
#define DISPLAY_LEADING_ZERO		true

// timer configuration settings
#define DEFAULT_INTERVAL			10
#define TIMER_STEP						5
#define TIMER_VALUE_MIN				5
#define TIMER_VALUE_MAX				600

// alarm settings
#define ALARM_PERIOD_MS				100
#define ALARM_TIMEOUT_MS			5000

// button assignment settings
#define BUTTON_START	2
#define BUTTON_PLUS		1
#define BUTTON_MINUS	3

/* ================================== */

MFShield mfs;

boolean countdown = false;	// countdown flag variable
uint16_t counter = DEFAULT_INTERVAL;	// countdown value
uint32_t t;	// a variable for non blocking loop, using millis()


/* ~~~~~~~~~~~~ LOOPED ALARM ROUTINE ~~~~~~~~~~~~~~~~ */
void alarm (const uint32_t period_ms, const uint32_t timeout_ms)
{
	uint32_t t_alarm = 0;	// make a counter variable for non blocking loop
	uint32_t alarm_timeout = millis() + timeout_ms;	// set alarm timeout
	while (true)
	{
		boolean blink = mfs.getLed(1);
		if (millis() - t_alarm >= period_ms)
		{		// non blocking loop: run this code once every <period_ms>
			t_alarm = millis();
			mfs.setLed(1, !blink);			// blink led
			mfs.showDisplay(!blink);		// blink display
			mfs.beep (period_ms / 2);
		}
   
		if (millis() > alarm_timeout)
		{
			counter = DEFAULT_INTERVAL;
			countdown = false;
			return;
		}
		mfs.loop();
	}
}
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/* ============= BUTTONS HANDLER FUNCTION ============= */
void keyAction (uint8_t key)
{
	if (countdown) return;    // do nothing if the countdown has begun
	
	switch (key)
	{
		case BUTTON_PLUS:
			counter += TIMER_STEP;
			break;

		case BUTTON_MINUS:
			counter -= TIMER_STEP;
			break;

		case BUTTON_START:
			countdown = true;
			t = millis();
			break;
	}
	counter = constrain (counter, TIMER_VALUE_MIN, TIMER_VALUE_MAX);	// limit counter range between these values (see definitions)
	if (ENABLE_BUTTON_SOUND)	mfs.beep(5);
	mfs.display(counter, DISPLAY_LEADING_ZERO);
}
/* =================================================== */

void setup()
{
	mfs.display(counter, DISPLAY_LEADING_ZERO);		
	// assign handler function for buttons (see above)
	mfs.onKeyPress (keyAction);
}

void loop()
{
	mfs.loop();
	if (!countdown) mfs.showDisplay ();
	else if (millis() - t >= 1000)
	{
		t = millis();
		if (counter > 0)
		{
			counter--;
		  mfs.setLed (1, !mfs.getLed(1));
			if (ENABLE_TICK_SOUND) mfs.beep (1);
		}
		else
			alarm(ALARM_PERIOD_MS, ALARM_TIMEOUT_MS);
		mfs.display(counter, DISPLAY_LEADING_ZERO);
	}
}
