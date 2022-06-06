#include <lcom/lcf.h>

#define KBD_IRQ 1
#define DELAY_US 20000
#define ESC 0x81
#define UP 0x11 
#define DOWN 0x1F    
#define LEFT 0x1E    
#define RIGHT 0x20

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

/* Mouse */
#define LB BIT(0)
#define RB BIT(1)
#define MB BIT(2)
#define MSB_X_DELTA BIT(4)
#define MSB_Y_DELTA BIT(5)
#define X_OVFL BIT(6)
#define Y_OVFL BIT(7)

#define DIS_MOUSE 0xA7
#define WRITE_BYTE_MOUSE 0xD4
#define DIS_DATA_REP 0xF5
#define ENA_DATA_REP 0xF4
#define STREAM_MODE 0xEA
#define REMOTE_MODE 0xF0
#define READ_DATA 0xEB

/* Mouse Controller command responses */
#define ACK 0xFA   //Acknowledged command or argument
#define NACK 0xFE  //Invalid byte
#define ERROR 0xFC //Second consecutive invalid byte