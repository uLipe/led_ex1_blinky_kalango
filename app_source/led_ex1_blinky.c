#include "board.h"
#include <KalangoRTOS/kalango_api.h>
#include <KalangoRTOS/list.h>

static TaskId task_a;
static TaskId task_b;

static void DemoTask1(void *arg) {
    uint32_t noof_wakeups = 0;
    (void)arg;


	GPIO_setPadConfig(19, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(19, GPIO_QUAL_SYNC);
	GPIO_setControllerCore(19, GPIO_CORE_CPU1);
	GPIO_setDirectionMode(19, GPIO_DIR_MODE_OUT);

    for(;;) {
        Kalango_Sleep(100);
        GPIO_togglePin(19);
        noof_wakeups++;
    }
}

static void DemoTask2(void *arg) {
    uint32_t noof_wakeups = 0;
    (void)arg;

	GPIO_setPadConfig(62, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(62, GPIO_QUAL_SYNC);
	GPIO_setControllerCore(62, GPIO_CORE_CPU1);
	GPIO_setDirectionMode(62, GPIO_DIR_MODE_OUT);

    for(;;) {
        Kalango_Sleep(250);
        GPIO_togglePin(62);
        noof_wakeups++;
    }
}

//
// Main
//
int main(void)
{
    //
    // Initialize device clock, peripheral clocks and interrupts
    //
    Device_init();

    //
    // Board Initialization
    //
    Board_init();

    TaskSettings settings;

    settings.arg = NULL;
    settings.function = DemoTask1;
    settings.priority = 8;
    settings.stack_size = 512;

    task_a = Kalango_TaskCreate(&settings);

    settings.arg = NULL;
    settings.function = DemoTask2;
    settings.priority = 4;
    settings.stack_size = 512;

    task_b = Kalango_TaskCreate(&settings);

    (void)task_a;
    (void)task_b;

    Kalango_CoreStart();

}

