#include "xparameters.h"
#include "xgpio.h"
#include "xstatus.h"
#include "xil_printf.h"

// Dia chi cua AXI GPIO
#define GPIO_DEVICE_ID  XPAR_XGPIO_0_BASEADDR

// Mau LED ban dau
#define LED_PATTERN     0xC3

// Delay de thay LED nhap nhay
#define LED_DELAY       10000000

// Channel GPIO dieu khien LED
#define LED_CHANNEL     1

#define printf xil_printf

// Bien dieu khien GPIO
XGpio gpio_dev;

int run_led_demo(void)
{
	volatile int delay;
	int status;

	// Gia tri hien tai cua LED
	int led_state = LED_PATTERN;

	// Khoi tao GPIO
	status = XGpio_Initialize(&gpio_dev, (u16)GPIO_DEVICE_ID);

	if (status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	// Set GPIO thanh output
	XGpio_SetDataDirection(&gpio_dev, LED_CHANNEL, 0x00);

	// Vong lap chay LED lien tuc
	while (1) {

		// Xuat du lieu ra LED
		XGpio_DiscreteWrite(&gpio_dev, LED_CHANNEL, led_state);

		// Dao trang thai LED
		led_state = ~led_state;

		// Delay mem
		for (delay = 0; delay < LED_DELAY; delay++);
	}

	return XST_SUCCESS;
}

int main(void)
{
	int status;

	// Chay chuong trinh LED
	status = run_led_demo();

	// Bao loi neu GPIO fail
	if (status != XST_SUCCESS) {
		xil_printf("LED demo failed!\r\n");
	}

	return 0;
}
