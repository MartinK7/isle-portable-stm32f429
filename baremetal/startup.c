#include <stdint.h>

/* Symbols defined in the linker script */
extern uint32_t _estack;
extern uint32_t _sbss;
extern uint32_t _ebss;

/* Function prototypes */
void Reset_Handler(void);
void Default_Handler(void);

/* Weak aliases for all exception handlers to Default_Handler */
void NMI_Handler(void)              __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)      __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)             __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void)        __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)         __attribute__((weak, alias("Default_Handler")));

/* Replace with your actual IRQ handlers as needed */
void IRQ0_Handler(void)            __attribute__((weak, alias("Default_Handler")));
/* ... Add more IRQ handlers or alias them to Default_Handler */

/* Forward declaration of main */
extern int main(void);

/* Vector table (placed in .isr_vector section via linker script) */
__attribute__((section(".isr_vector")))
const void *vector_table[] = {
	(void *)&_estack,         // Initial stack pointer
	Reset_Handler,            // Reset handler
	NMI_Handler,              // NMI
	HardFault_Handler,        // Hard fault
	MemManage_Handler,        // Memory management
	BusFault_Handler,         // Bus fault
	UsageFault_Handler,       // Usage fault
	0, 0, 0, 0,               // Reserved
	SVC_Handler,              // SVCall
	DebugMon_Handler,         // Debug monitor
	0,                        // Reserved
	PendSV_Handler,           // PendSV
	SysTick_Handler,          // SysTick
	/* IRQ handlers */
	IRQ0_Handler              // IRQ0 (example, extend as needed)
};

/* Reset handler */
void Reset_Handler(void)
{
	/* Zero-initialize the .bss section */
	uint32_t *bss = &_sbss;
	while (bss < &_ebss) {
		*bss++ = 0;
	}

	/* Call the application's entry point */
	main();

	/* If main returns, loop forever */
	while (1) {}
}

/* Default interrupt handler */
void Default_Handler(void)
{
	while (1) {}
}

