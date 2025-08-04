/* Minimal RAM-only linker script for STM32F429 */

ENTRY(Reset_Handler)

/* STM32F429 has 192K SRAM (SRAM1 + SRAM2) starting at 0x20000000 */
MEMORY
{
  RAM   (xrw) : ORIGIN = 0x20000000, LENGTH = 192K
  SDRAM (xrw) : ORIGIN = 0x90000000, LENGTH = 8M
}

_estack = ORIGIN(RAM) + LENGTH(RAM); /* Initial stack pointer */

SECTIONS
{
  /* Vector table and text/code section */
  .isr_vector :
  {
    KEEP(*(.isr_vector))
  } > SDRAM

  .text :
  {
    *(.text*)
    *(.rodata*)
    KEEP(*(.init))
    KEEP(*(.fini))
  } > SDRAM

  .data :
  {
    *(.data*)
  } > SDRAM

  .bss :
  {
    . = ALIGN(8);
    _sbss = .;
    *(.bss*)
    *(COMMON)
    . = ALIGN(8);
    _ebss = .;
  } > SDRAM

  /* Heap section in SDRAM */
  .heap (NOLOAD) :
  {
    . = ALIGN(8);
    _heap_start = .;
    KEEP(*(.heap))
    . = ALIGN(8);
    _heap_end = .;
  } > SDRAM

  . = ALIGN(4);
  _end = .;
}

