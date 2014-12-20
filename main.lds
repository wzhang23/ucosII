OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
ENTRY(_start) /* the entry point */
SECTIONS
{
  . = 0x50000000;   /* current address */

  .startup : {
    startup/* (.text) /* the startup code must be in the first 8k memory */
  }
  
  .text : {
    * (.text)
  }

  .data : {
    * (.data)
  }

  bss_start = .;
  .bss : {
    * (.bss)
  }
  bss_end   = .;
  framebuffer_start = 0x51000000;
  framebuffer_end   = 0x51200000;
}
