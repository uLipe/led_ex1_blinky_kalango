#include "board.h"
#include <KalangoRTOS/kalango_api.h>
#include <KalangoRTOS/list.h>

static TaskId task_a;
static TaskId task_b;

static TimerId t_a;
static TimerId t_b;

static SemaphoreId sem_a;
static SemaphoreId sem_b;

static void TimerExpiredCallback(void *user_data) {
    SemaphoreId sem = (SemaphoreId)user_data;
    Kalango_SemaphoreGive(sem, 1);
}

static void DemoTask1(void *arg) {
    uint32_t noof_wakeups = 0;
    TimerId t = (TimerId)arg;
 

	GPIO_setPadConfig(19, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(19, GPIO_QUAL_SYNC);
	GPIO_setControllerCore(19, GPIO_CORE_CPU1);
	GPIO_setDirectionMode(19, GPIO_DIR_MODE_OUT);

    Kalango_TimerStart(t);

    for(;;) {
        Kalango_SemaphoreTake(sem_a, KERNEL_WAIT_FOREVER);
        GPIO_togglePin(19);
        noof_wakeups++;
    }
}

static void DemoTask2(void *arg) {
    uint32_t noof_wakeups = 0;
    TimerId t = (TimerId)arg;

	GPIO_setPadConfig(62, GPIO_PIN_TYPE_STD);
	GPIO_setQualificationMode(62, GPIO_QUAL_SYNC);
	GPIO_setControllerCore(62, GPIO_CORE_CPU1);
	GPIO_setDirectionMode(62, GPIO_DIR_MODE_OUT);
    GPIO_togglePin(62);

    Kalango_TimerStart(t);

    for(;;) {
        Kalango_SemaphoreTake(sem_b, KERNEL_WAIT_FOREVER);
        GPIO_togglePin(62);
        noof_wakeups++;

        if(noof_wakeups > 30) {
            GPIO_togglePin(62);
            Kalango_TimerStop(t);
            noof_wakeups = 0;
            Kalango_Sleep(KALANGO_TICKS_FROM_MS(3000));
            Kalango_TimerStart(t);
        }
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


    sem_a = Kalango_SemaphoreCreate(0, 1);
    sem_b = Kalango_SemaphoreCreate(0, 1);

    //10KHz
    t_a = Kalango_TimerCreate(TimerExpiredCallback, KALANGO_TICKS_FROM_MS(200),
                                KALANGO_TICKS_FROM_MS(200), sem_a);
    
    //5KHz
    t_b = Kalango_TimerCreate(TimerExpiredCallback, KALANGO_TICKS_FROM_MS(100), 
                                KALANGO_TICKS_FROM_MS(100), sem_b);


  TaskSettings settings;

    settings.arg = t_a;
    settings.function = DemoTask1;
    settings.priority = 8;
    settings.stack_size = 512;

    task_a = Kalango_TaskCreate(&settings);

    settings.arg = t_b;
    settings.function = DemoTask2;
    settings.priority = 4;
    settings.stack_size = 512;

    task_b = Kalango_TaskCreate(&settings);

    (void)task_a;
    (void)task_b;

    Kalango_CoreStart();

}

