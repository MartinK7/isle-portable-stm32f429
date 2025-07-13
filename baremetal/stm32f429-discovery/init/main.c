
#include "stm32f429xx.h"

#include "unit_tests/sdram_test.h"

static void gpio_init(void)
{
	// Enable GPIO clocks
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN | RCC_AHB1ENR_GPIOEEN | RCC_AHB1ENR_GPIOFEN | RCC_AHB1ENR_GPIOGEN;

	// NOTE: This function is generated using gpiogen from file pinout.gpiogen.csv

	//                  FMC            FMC
	GPIOB->AFR[0]  &= ~(0xFU<<( 5-0)*4|0xFU<<( 6-0)*4|0);
	GPIOB->AFR[0]  |=  (0xCU<<( 5-0)*4|0xCU<<( 6-0)*4|0);
	GPIOB->AFR[1]  &= ~(0             |0             |0);
	GPIOB->AFR[1]  |=  (0             |0             |0);
	GPIOB->MODER   &= ~(0x3U<<( 5*2)  |0x3U<<( 6*2)  |0);
	GPIOB->MODER   |=  (0x2U<<( 5*2)  |0x2U<<( 6*2)  |0);
	GPIOB->OSPEEDR &= ~(0x3U<<( 5*2)  |0x3U<<( 6*2)  |0);
	GPIOB->OSPEEDR |=  (0x3U<<( 5*2)  |0x3U<<( 6*2)  |0);
	GPIOB->OTYPER  &= ~(0x1U<<( 5*1)  |0x1U<<( 6*1)  |0);
	GPIOB->OTYPER  |=  (0x0U<<( 5*1)  |0x0U<<( 6*1)  |0);
	GPIOB->PUPDR   &= ~(0x3U<<( 5*2)  |0x3U<<( 6*2)  |0);
	GPIOB->PUPDR   |=  (0x0U<<( 5*2)  |0x0U<<( 6*2)  |0);

	//                  FMC
	GPIOC->AFR[0]  &= ~(0xFU<<( 0-0)*4|0);
	GPIOC->AFR[0]  |=  (0xCU<<( 0-0)*4|0);
	GPIOC->AFR[1]  &= ~(0             |0);
	GPIOC->AFR[1]  |=  (0             |0);
	GPIOC->MODER   &= ~(0x3U<<( 0*2)  |0);
	GPIOC->MODER   |=  (0x2U<<( 0*2)  |0);
	GPIOC->OSPEEDR &= ~(0x3U<<( 0*2)  |0);
	GPIOC->OSPEEDR |=  (0x3U<<( 0*2)  |0);
	GPIOC->OTYPER  &= ~(0x1U<<( 0*1)  |0);
	GPIOC->OTYPER  |=  (0x0U<<( 0*1)  |0);
	GPIOC->PUPDR   &= ~(0x3U<<( 0*2)  |0);
	GPIOC->PUPDR   |=  (0x0U<<( 0*2)  |0);

	//                  FMC            FMC            FMC            FMC            FMC            FMC            FMC
	GPIOD->AFR[0]  &= ~(0xFU<<( 0-0)*4|0xFU<<( 1-0)*4|0             |0             |0             |0             |0             |0);
	GPIOD->AFR[0]  |=  (0xCU<<( 0-0)*4|0xCU<<( 1-0)*4|0             |0             |0             |0             |0             |0);
	GPIOD->AFR[1]  &= ~(0             |0             |0xFU<<( 8-8)*4|0xFU<<( 9-8)*4|0xFU<<(10-8)*4|0xFU<<(14-8)*4|0xFU<<(15-8)*4|0);
	GPIOD->AFR[1]  |=  (0             |0             |0xCU<<( 8-8)*4|0xCU<<( 9-8)*4|0xCU<<(10-8)*4|0xCU<<(14-8)*4|0xCU<<(15-8)*4|0);
	GPIOD->MODER   &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 8*2)  |0x3U<<( 9*2)  |0x3U<<(10*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOD->MODER   |=  (0x2U<<( 0*2)  |0x2U<<( 1*2)  |0x2U<<( 8*2)  |0x2U<<( 9*2)  |0x2U<<(10*2)  |0x2U<<(14*2)  |0x2U<<(15*2)  |0);
	GPIOD->OSPEEDR &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 8*2)  |0x3U<<( 9*2)  |0x3U<<(10*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOD->OSPEEDR |=  (0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 8*2)  |0x3U<<( 9*2)  |0x3U<<(10*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOD->OTYPER  &= ~(0x1U<<( 0*1)  |0x1U<<( 1*1)  |0x1U<<( 8*1)  |0x1U<<( 9*1)  |0x1U<<(10*1)  |0x1U<<(14*1)  |0x1U<<(15*1)  |0);
	GPIOD->OTYPER  |=  (0x0U<<( 0*1)  |0x0U<<( 1*1)  |0x0U<<( 8*1)  |0x0U<<( 9*1)  |0x0U<<(10*1)  |0x0U<<(14*1)  |0x0U<<(15*1)  |0);
	GPIOD->PUPDR   &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 8*2)  |0x3U<<( 9*2)  |0x3U<<(10*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOD->PUPDR   |=  (0x0U<<( 0*2)  |0x0U<<( 1*2)  |0x0U<<( 8*2)  |0x0U<<( 9*2)  |0x0U<<(10*2)  |0x0U<<(14*2)  |0x0U<<(15*2)  |0);

	//                  FMC            FMC            FMC            FMC            FMC            FMC            FMC            FMC            FMC            FMC            FMC
	GPIOE->AFR[0]  &= ~(0xFU<<( 0-0)*4|0xFU<<( 1-0)*4|0xFU<<( 7-0)*4|0             |0             |0             |0             |0             |0             |0             |0             |0);
	GPIOE->AFR[0]  |=  (0xCU<<( 0-0)*4|0xCU<<( 1-0)*4|0xCU<<( 7-0)*4|0             |0             |0             |0             |0             |0             |0             |0             |0);
	GPIOE->AFR[1]  &= ~(0             |0             |0             |0xFU<<( 8-8)*4|0xFU<<( 9-8)*4|0xFU<<(10-8)*4|0xFU<<(11-8)*4|0xFU<<(12-8)*4|0xFU<<(13-8)*4|0xFU<<(14-8)*4|0xFU<<(15-8)*4|0);
	GPIOE->AFR[1]  |=  (0             |0             |0             |0xCU<<( 8-8)*4|0xCU<<( 9-8)*4|0xCU<<(10-8)*4|0xCU<<(11-8)*4|0xCU<<(12-8)*4|0xCU<<(13-8)*4|0xCU<<(14-8)*4|0xCU<<(15-8)*4|0);
	GPIOE->MODER   &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 7*2)  |0x3U<<( 8*2)  |0x3U<<( 9*2)  |0x3U<<(10*2)  |0x3U<<(11*2)  |0x3U<<(12*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOE->MODER   |=  (0x2U<<( 0*2)  |0x2U<<( 1*2)  |0x2U<<( 7*2)  |0x2U<<( 8*2)  |0x2U<<( 9*2)  |0x2U<<(10*2)  |0x2U<<(11*2)  |0x2U<<(12*2)  |0x2U<<(13*2)  |0x2U<<(14*2)  |0x2U<<(15*2)  |0);
	GPIOE->OSPEEDR &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 7*2)  |0x3U<<( 8*2)  |0x3U<<( 9*2)  |0x3U<<(10*2)  |0x3U<<(11*2)  |0x3U<<(12*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOE->OSPEEDR |=  (0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 7*2)  |0x3U<<( 8*2)  |0x3U<<( 9*2)  |0x3U<<(10*2)  |0x3U<<(11*2)  |0x3U<<(12*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOE->OTYPER  &= ~(0x1U<<( 0*1)  |0x1U<<( 1*1)  |0x1U<<( 7*1)  |0x1U<<( 8*1)  |0x1U<<( 9*1)  |0x1U<<(10*1)  |0x1U<<(11*1)  |0x1U<<(12*1)  |0x1U<<(13*1)  |0x1U<<(14*1)  |0x1U<<(15*1)  |0);
	GPIOE->OTYPER  |=  (0x0U<<( 0*1)  |0x0U<<( 1*1)  |0x0U<<( 7*1)  |0x0U<<( 8*1)  |0x0U<<( 9*1)  |0x0U<<(10*1)  |0x0U<<(11*1)  |0x0U<<(12*1)  |0x0U<<(13*1)  |0x0U<<(14*1)  |0x0U<<(15*1)  |0);
	GPIOE->PUPDR   &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 7*2)  |0x3U<<( 8*2)  |0x3U<<( 9*2)  |0x3U<<(10*2)  |0x3U<<(11*2)  |0x3U<<(12*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOE->PUPDR   |=  (0x0U<<( 0*2)  |0x0U<<( 1*2)  |0x0U<<( 7*2)  |0x0U<<( 8*2)  |0x0U<<( 9*2)  |0x0U<<(10*2)  |0x0U<<(11*2)  |0x0U<<(12*2)  |0x0U<<(13*2)  |0x0U<<(14*2)  |0x0U<<(15*2)  |0);

	//                  FMC            FMC            FMC            FMC            FMC            FMC            FMC            FMC            FMC            FMC            FMC
	GPIOF->AFR[0]  &= ~(0xFU<<( 0-0)*4|0xFU<<( 1-0)*4|0xFU<<( 2-0)*4|0xFU<<( 3-0)*4|0xFU<<( 4-0)*4|0xFU<<( 5-0)*4|0             |0             |0             |0             |0             |0);
	GPIOF->AFR[0]  |=  (0xCU<<( 0-0)*4|0xCU<<( 1-0)*4|0xCU<<( 2-0)*4|0xCU<<( 3-0)*4|0xCU<<( 4-0)*4|0xCU<<( 5-0)*4|0             |0             |0             |0             |0             |0);
	GPIOF->AFR[1]  &= ~(0             |0             |0             |0             |0             |0             |0xFU<<(11-8)*4|0xFU<<(12-8)*4|0xFU<<(13-8)*4|0xFU<<(14-8)*4|0xFU<<(15-8)*4|0);
	GPIOF->AFR[1]  |=  (0             |0             |0             |0             |0             |0             |0xCU<<(11-8)*4|0xCU<<(12-8)*4|0xCU<<(13-8)*4|0xCU<<(14-8)*4|0xCU<<(15-8)*4|0);
	GPIOF->MODER   &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 2*2)  |0x3U<<( 3*2)  |0x3U<<( 4*2)  |0x3U<<( 5*2)  |0x3U<<(11*2)  |0x3U<<(12*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOF->MODER   |=  (0x2U<<( 0*2)  |0x2U<<( 1*2)  |0x2U<<( 2*2)  |0x2U<<( 3*2)  |0x2U<<( 4*2)  |0x2U<<( 5*2)  |0x2U<<(11*2)  |0x2U<<(12*2)  |0x2U<<(13*2)  |0x2U<<(14*2)  |0x2U<<(15*2)  |0);
	GPIOF->OSPEEDR &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 2*2)  |0x3U<<( 3*2)  |0x3U<<( 4*2)  |0x3U<<( 5*2)  |0x3U<<(11*2)  |0x3U<<(12*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOF->OSPEEDR |=  (0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 2*2)  |0x3U<<( 3*2)  |0x3U<<( 4*2)  |0x3U<<( 5*2)  |0x3U<<(11*2)  |0x3U<<(12*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOF->OTYPER  &= ~(0x1U<<( 0*1)  |0x1U<<( 1*1)  |0x1U<<( 2*1)  |0x1U<<( 3*1)  |0x1U<<( 4*1)  |0x1U<<( 5*1)  |0x1U<<(11*1)  |0x1U<<(12*1)  |0x1U<<(13*1)  |0x1U<<(14*1)  |0x1U<<(15*1)  |0);
	GPIOF->OTYPER  |=  (0x0U<<( 0*1)  |0x0U<<( 1*1)  |0x0U<<( 2*1)  |0x0U<<( 3*1)  |0x0U<<( 4*1)  |0x0U<<( 5*1)  |0x0U<<(11*1)  |0x0U<<(12*1)  |0x0U<<(13*1)  |0x0U<<(14*1)  |0x0U<<(15*1)  |0);
	GPIOF->PUPDR   &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 2*2)  |0x3U<<( 3*2)  |0x3U<<( 4*2)  |0x3U<<( 5*2)  |0x3U<<(11*2)  |0x3U<<(12*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0x3U<<(15*2)  |0);
	GPIOF->PUPDR   |=  (0x0U<<( 0*2)  |0x0U<<( 1*2)  |0x0U<<( 2*2)  |0x0U<<( 3*2)  |0x0U<<( 4*2)  |0x0U<<( 5*2)  |0x0U<<(11*2)  |0x0U<<(12*2)  |0x0U<<(13*2)  |0x0U<<(14*2)  |0x0U<<(15*2)  |0);

	//                  FMC            FMC            FMC            FMC            FMC            FMC            LEDG           LEDR
	GPIOG->AFR[0]  &= ~(0xFU<<( 0-0)*4|0xFU<<( 1-0)*4|0xFU<<( 4-0)*4|0xFU<<( 5-0)*4|0             |0             |0             |0             |0);
	GPIOG->AFR[0]  |=  (0xCU<<( 0-0)*4|0xCU<<( 1-0)*4|0xCU<<( 4-0)*4|0xCU<<( 5-0)*4|0             |0             |0             |0             |0);
	GPIOG->AFR[1]  &= ~(0             |0             |0             |0             |0xFU<<( 8-8)*4|0xFU<<(15-8)*4|0xFU<<(13-8)*4|0xFU<<(14-8)*4|0);
	GPIOG->AFR[1]  |=  (0             |0             |0             |0             |0xCU<<( 8-8)*4|0xCU<<(15-8)*4|0x0U<<(13-8)*4|0x0U<<(14-8)*4|0);
	GPIOG->MODER   &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 4*2)  |0x3U<<( 5*2)  |0x3U<<( 8*2)  |0x3U<<(15*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0);
	GPIOG->MODER   |=  (0x2U<<( 0*2)  |0x2U<<( 1*2)  |0x2U<<( 4*2)  |0x2U<<( 5*2)  |0x2U<<( 8*2)  |0x2U<<(15*2)  |0x1U<<(13*2)  |0x1U<<(14*2)  |0);
	GPIOG->OSPEEDR &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 4*2)  |0x3U<<( 5*2)  |0x3U<<( 8*2)  |0x3U<<(15*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0);
	GPIOG->OSPEEDR |=  (0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 4*2)  |0x3U<<( 5*2)  |0x3U<<( 8*2)  |0x3U<<(15*2)  |0x0U<<(13*2)  |0x0U<<(14*2)  |0);
	GPIOG->OTYPER  &= ~(0x1U<<( 0*1)  |0x1U<<( 1*1)  |0x1U<<( 4*1)  |0x1U<<( 5*1)  |0x1U<<( 8*1)  |0x1U<<(15*1)  |0x1U<<(13*1)  |0x1U<<(14*1)  |0);
	GPIOG->OTYPER  |=  (0x0U<<( 0*1)  |0x0U<<( 1*1)  |0x0U<<( 4*1)  |0x0U<<( 5*1)  |0x0U<<( 8*1)  |0x0U<<(15*1)  |0x0U<<(13*1)  |0x0U<<(14*1)  |0);
	GPIOG->PUPDR   &= ~(0x3U<<( 0*2)  |0x3U<<( 1*2)  |0x3U<<( 4*2)  |0x3U<<( 5*2)  |0x3U<<( 8*2)  |0x3U<<(15*2)  |0x3U<<(13*2)  |0x3U<<(14*2)  |0);
	GPIOG->PUPDR   |=  (0x0U<<( 0*2)  |0x0U<<( 1*2)  |0x0U<<( 4*2)  |0x0U<<( 5*2)  |0x0U<<( 8*2)  |0x0U<<(15*2)  |0x0U<<(13*2)  |0x0U<<(14*2)  |0);
}

static void rcc_init(void)
{
	// 1. Enable HSE
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY)) {
		// Wait for HSE to be ready
	}

#if 0
	// 2. Configure prescalers
	RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;
	RCC->CFGR &= ~RCC_CFGR_PPRE1_Msk;
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
	RCC->CFGR &= ~RCC_CFGR_PPRE2_Msk;
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

	// 3. Configure PLL
	// Define your PLL values, or you can #define these earlier
	const uint32_t PLL_M = 4;
	const uint32_t PLL_N = 143;
	const uint32_t PLL_P = 2;   // PLLP = 2 -> PLLP bits = 0
	const uint32_t PLL_Q = 4;
#else
	// 2. Configure prescalers
	RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;
	RCC->CFGR &= ~RCC_CFGR_PPRE1_Msk;
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
	RCC->CFGR &= ~RCC_CFGR_PPRE2_Msk;
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

	// 3. Configure PLL
	// Define your PLL values, or you can #define these earlier
	const uint32_t PLL_M = 8;
	const uint32_t PLL_N = 336;
	const uint32_t PLL_P = 2;   // PLLP = 2 -> PLLP bits = 0
	const uint32_t PLL_Q = 7;
#endif

	RCC->PLLCFGR = (PLL_M) |
		(PLL_N << RCC_PLLCFGR_PLLN_Pos) |
		(((PLL_P / 2) - 1) << RCC_PLLCFGR_PLLP_Pos) |
		(RCC_PLLCFGR_PLLSRC_HSE) |
		(PLL_Q << RCC_PLLCFGR_PLLQ_Pos);

	// 4. Enable PLL
	RCC->CR |= RCC_CR_PLLON;
	while (!(RCC->CR & RCC_CR_PLLRDY)) {
		// Wait for PLL to be ready
	}

	// 5. Configure Flash wait states, enable caches
	FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;

	// 6. Select PLL as system clock
	RCC->CFGR &= ~RCC_CFGR_SW_Msk;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {
		// Wait for PLL to be system clock
	}

	SystemCoreClockUpdate();
}

static void sdram_init(void)
{
	// Enable FMC clock
	RCC->AHB3ENR |= RCC_AHB3ENR_FMCEN;
#if 0
	FMC_Bank5_6->SDCR[0] &= ~(0x00007FFF);
	FMC_Bank5_6->SDTR[0] &= ~(0x0FFFFFFF);
	FMC_Bank5_6->SDCR[1] &= ~(0x00007FFF);
	FMC_Bank5_6->SDTR[1] &= ~(0x0FFFFFFF);

	FMC_Bank5_6->SDCR[1] |=
		( 1 << FMC_SDCR1_RPIPE_Pos)  | // No HCLK delay
		( 1 << FMC_SDCR1_RBURST_Pos) | // Enable read burst
		( 0 << FMC_SDCR1_SDCLK_Pos)  | // 2x HCLK
		( 0 << FMC_SDCR1_WP_Pos)     | // Write Protect
		( 3 << FMC_SDCR1_CAS_Pos)    | // CAS = 3
		( 1 << FMC_SDCR1_NB_Pos)     | // 4 banks
		( 1 << FMC_SDCR1_MWID_Pos)   | // 16-bit
		( 1 << FMC_SDCR1_NR_Pos)     | // 12 row
		( 1 << FMC_SDCR1_NC_Pos);      // 8 col

	FMC_Bank5_6->SDTR[1] |=                  // 1 cycle @ 143MHz = 6.99ns
		(( 3 - 1) << FMC_SDTR1_TRCD_Pos)   | // RCD delay - min 15ns
		(( 3 - 1) << FMC_SDTR1_TRP_Pos)    | // RP delay - min 15ns
		(( 3 - 1) << FMC_SDTR1_TWR_Pos)    | // Write recovery - min 2 clock
		(( 9 - 1) << FMC_SDTR1_TRC_Pos)    | // Row cycle delay - min 63ns
		(( 6 - 1) << FMC_SDTR1_TRAS_Pos)   | // Row active delay - min 42ns
		((11 - 1) << FMC_SDTR1_TXSR_Pos)   | // Exit self-refresh - min 70ns
		(( 1 - 1) << FMC_SDTR1_TMRD_Pos);    // Load mode delay - min 2 cycle
	while((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY)) {}

	// Clock enable
	FMC_Bank5_6->SDCMR = (1 << FMC_SDCMR_MODE_Pos) | (1 << FMC_SDCMR_CTB2_Pos);
	system_delay_ms(100);

	// PALL
	FMC_Bank5_6->SDCMR = (2 << FMC_SDCMR_MODE_Pos) | (1 << FMC_SDCMR_CTB2_Pos);
	while((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY)) {}

	// Auto refresh
	FMC_Bank5_6->SDCMR = (3 << FMC_SDCMR_MODE_Pos) | (7 << FMC_SDCMR_NRFS_Pos) | (1 << FMC_SDCMR_CTB2_Pos);
	while((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY)) {}

	// Mode register definition (burst length = 1, CAS = 3)
	uint32_t mode_reg =
		(0 << 3) | // burst type = sequential
		(3 << 4) | // CAS = 3
		(1 << 9);  // burst length = 1

	FMC_Bank5_6->SDCMR =
		(4 << FMC_SDCMR_MODE_Pos) |
		(mode_reg << FMC_SDCMR_MRD_Pos) |
		(1 << FMC_SDCMR_CTB2_Pos);
	while((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY)) {}

	// Set refresh rate: 64ms / 8192 = 7.81 us
	// 7.81 us * 143 MHz = ~1117
	FMC_Bank5_6->SDRTR = (1118 << 1);
	while((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY)) {}
#else
	FMC_Bank5_6->SDCR[0] = 0x00001800;
	FMC_Bank5_6->SDCR[1] = 0x000019D4;
	FMC_Bank5_6->SDTR[0] = 0x00106000;
	FMC_Bank5_6->SDTR[1] = 0x00010361;

	while((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY)) {}
	FMC_Bank5_6->SDCMR = 0x00000009; // clock
	for(volatile int i = 0; i < 100000; ++i) __NOP();
	while((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY)) {}
	FMC_Bank5_6->SDCMR = 0x0000000A; // PALL
	while((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY)) {}
	FMC_Bank5_6->SDCMR = 0x000000EB; // auto-refresh
	while((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY)) {}
	FMC_Bank5_6->SDCMR = 0x0004600C; // external memory mode
	FMC_Bank5_6->SDRTR = 1386 << 1;  // refresh rate
	while((FMC_Bank5_6->SDSR & FMC_SDSR_BUSY)) {}
#endif

	SYSCFG->MEMRMP = 1 << 10;
}

#include <stdint.h>

#define SDRAM_BASE_ADDR      0x90000000
#define SDRAM_PC_OFFSET      0x4

typedef void (*func_ptr_t)(void);

void execute_sdram_code_from_ivt(void)
{
    // Read PC from SDRAM vector table
    uint32_t entry_point = *((uint32_t *)(SDRAM_BASE_ADDR + SDRAM_PC_OFFSET));
    func_ptr_t func = (func_ptr_t)(entry_point);
    func();
}


int main(void)
{
	int result = 0;

	gpio_init();
	rcc_init();
	sdram_init();

	execute_sdram_code_from_ivt();

	if(0 != test_sdram((void *)0x90000000, 8 * 1024 * 1024)) {
		while(1);
	}

	while(1) {
		*((volatile uint32_t *)(0x40000000 + 0x00020000 + 0x00001800 + 24)) = (1UL << (13 +  0U));
		// GPIOG->BSRR = GPIO_BSRR_BS13;
		for(volatile int i = 0; i < 1000000; ++i) __NOP();

		*((volatile uint32_t *)(0x40000000 + 0x00020000 + 0x00001800 + 24)) = (1UL << (13 + 16U));
		// GPIOG->BSRR = GPIO_BSRR_BR13;
		for(volatile int i = 0; i < 1000000; ++i) __NOP();
	}

	return result;
}
