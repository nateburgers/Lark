/* lrkbt_linkscript.ld                                          -*-GNU-LD-*- */

/* ========================================================================= */
/* @PURPOSE: Provide a platform-independent linker script for test drivers.  */
/*                                                                           */
/* @SEE_ALSO: lrkbt_testharness                                              */
/*                                                                           */
/* @DESCRIPTION:                                                             */
/*                                                                           */
/* ------------------------------------------------------------------------- */

ENTRY(_start)

SEARCH_DIR(/usr/lib/w32api)

INPUT(test.o)

INPUT(libkernel32.a)

OUTPUT(test.tsk)

/* ========================================================================= */
/*                                  GLOBALS                                  */
/* ------------------------------------------------------------------------- */

PAGE_SIZE = 4096;

PHYSICAL_LOAD_ADDRESS = 0x1000000;
    /* The address at which the program will be loaded in physical memory. */

VIRTUAL_LOAD_ADDRESS  = 0x1000000;
    /* The address at which the program will be loaded in virtual memory. */

/* ========================================================================= */
/*                                  SECTIONS                                 */
/* ------------------------------------------------------------------------- */

SECTIONS
{
    .text : {
        *(.text)
        *(.text.*)
        *(.rodata*)
        *(.gnu.linkonce.t*)
        *(.gnu.linkonce.r*)
        
        . = ALIGN(PAGE_SIZE);
    }
 
    .data : {
        *(.data)
        *(.data.*)
        *(.gnu.linkonce.d*) 

        _LRKBT_STATIC_CONSTRUCTORS = .;
        *(.ctors) 
        _LRKBT_NUM_STATIC_CONSTRUCTORS = .;
        LONG((_LRKBT_STATIC_CONSTRUCTORS - _LRKBT_NUM_STATIC_CONSTRUCTORS) / 4 - 2)

        _LRKBT_STATIC_DESTRUCTORS = .;
        *(.dtors)
        _LRKBT_NUM_STATIC_DESTRUCTORS = .;
        LONG((_LRKBT_STATIC_DESTRUCTORS - _LRKBT_NUM_STATIC_DESTRUCTORS) / 4 - 2)

        . = ALIGN(PAGE_SIZE);
    }
 
    .bss : {
        *(.bss)
        *(.bss.*)
        *(.gnu.linkonce.b*)
        *(.COMMON)
        . = ALIGN(PAGE_SIZE);
    }
}
