#include <lcom/lcf.h>

#define KBD_IRQ 1
#define DELAY_US 20000
#define ESC 0x81
#define TWOBYTES 0xe0


/* I/O Port Adress */
#define STAT_REG 0x64
#define OUT_BUF 0x60
#define IN_BUF_CMD 0x64
#define IN_BUF_ARGS 0x60

/* Status macros*/
#define ST_OUT_BUF BIT(0)
#define ST_IN_BUF BIT(1)
#define ST_MOUSE_DATA BIT(5)
#define ST_TO_ERR BIT(6)
#define ST_PAR_ERR BIT(7)

/*Command*/
#define WRITE_COMMAND 0x60
#define COMMAND_BYTE_INTERRUPT_KB BIT(0)
