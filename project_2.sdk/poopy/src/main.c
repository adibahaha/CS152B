#include "xparameters.h"
#include "xuartlite.h"
#include "xil_printf.h"
#include "sleep.h"

#define UARTLITE_DEVICE_ID      XPAR_AXI_UARTLITE_0_DEVICE_ID

XUartLite UartLite;

int main()
{
    int Status;

    xil_printf("---- BT2 UARTLite Test Program ----\n\r");

    // Initialize UARTLite
    Status = XUartLite_Initialize(&UartLite, UARTLITE_DEVICE_ID);
    if (Status != XST_SUCCESS)
    {
        xil_printf("UARTLite Init Failed!\n\r");
        return XST_FAILURE;
    }

    xil_printf("UARTLite Initialized. Sending test messages...\n\r");

    const char *msg = "BT2 Test: Hello from FPGA!\n\r";

    while (1)
    {
        // Send test message once per second
        XUartLite_Send(&UartLite, (u8*)msg, strlen(msg));

        // Check for incoming BT2 data
        u8 recv;
        int received = XUartLite_Recv(&UartLite, &recv, 1);

        if (received == 1)
        {
            xil_printf("Received from BT2: %c\n\r", recv);

            // Echo back to BT2
            XUartLite_Send(&UartLite, &recv, 1);
        }

        sleep(1);
    }

    return 0;
}
