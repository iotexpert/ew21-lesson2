
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "joystick_task.h"

#include "capsense_task.h"

volatile int uxTopUsedPriority ;

int main(void)
{
	uxTopUsedPriority = configMAX_PRIORITIES - 1 ; // enable OpenOCD Thread Debugging

    /* Initialize the device and board peripherals */
    cybsp_init() ;
    __enable_irq();

    /* Enable printf printing to the UART */
    /* See the "Retarget IO" link in the Quick Panel Documentation */
    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);

    printf("Application Started\n");

    xTaskCreate(capsense_task, "CapSense Task", configMINIMAL_STACK_SIZE, NULL, (configMAX_PRIORITIES - 1), 0);
    xTaskCreate(joystick_task, "Joystick Task", (configMINIMAL_STACK_SIZE*4), NULL, (configMAX_PRIORITIES - 2), 0);

    vTaskStartScheduler();
}

/* [] END OF FILE */
