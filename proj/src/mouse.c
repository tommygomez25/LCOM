#include "mouse.h"

int mouse_hook_id = 12;
uint8_t scancode;

int (mouse_subscribe_int)(uint8_t *bit_no){
    *bit_no = (uint8_t) mouse_hook_id;
    if (sys_irqsetpolicy(MOUSE_IRQ,(IRQ_REENABLE|IRQ_EXCLUSIVE),&mouse_hook_id)){
        return 1;
    }
    return 0;
}

int (mouse_unsubscribe_int)() {
    if (sys_irqrmpolicy(&mouse_hook_id)){
        return 1;
    }
    return 0;
}

void (mouse_ih)() {
    uint8_t stat;
    uint8_t output;

    if (util_sys_inb(STAT_REG,&stat)){
        return;
    }

    if (stat & ST_OUT_BUF){
        if (util_sys_inb(OUT_BUF,&output)){
            return;
        }

        if (stat & (ST_PAR_ERR | ST_TO_ERR)){
            scancode = 0;
        }

        else {
            scancode = output;
            return;}
    }

    scancode = 0;
}

void (buildPacket)(struct packet * pacote) {
    
  pacote->lb = pacote->bytes[0] & BIT(0);
  
  pacote->rb = pacote->bytes[0] & BIT(1);

  pacote->mb = pacote->bytes[0] & BIT(2);

  pacote->delta_x = convert_2_complement(pacote->bytes[1],BIT(4), pacote);

  pacote->delta_y = convert_2_complement(pacote->bytes[2],BIT(5), pacote);

  pacote->x_ov = pacote->bytes[0] & BIT(6);

  pacote->y_ov = pacote->bytes[0] & BIT(7);

}

int(mouse_write_cmd)(uint32_t cmd, uint8_t *resp) {
  int count = 0;
  uint8_t stat;
  while (count < 3) {
    
    if (util_sys_inb(KBC_CMD_REG,&stat) == 0){
        
        if (stat & ST_IN_BUF) return 1;

        if (sys_outb(WRITE_CMD_BYTE, cmd) != 0) {return 1;} // escreve no porto 0x60 o comando que dá disable ao mouse data reporting

        if (util_sys_inb(OUT_BUF, resp) != 0) {return 1;} // lê o OUT_BUF para ver qual a resposta obtida

        return 0;
    }
    
    count++;
  }

  return 1;
}


int (mouse_disable_data_reporting)() {
    uint8_t resp;
    uint8_t error = 0;
    while (error < 2) {
        if (sys_outb(KBC_CMD_REG,WRITE_BYTE_MOUSE)) {return 1;} // escreve no porto 0x64 o commando 0xD4 para avisar que quer enviar um comando do rato

        if (mouse_write_cmd(DIS_DATA_REP,&resp)) {return 1;} // escreve o comando 0xF5 , obtendo resposta 

        if (resp == ACK) return 0;
        else if (resp == NACK) {error++;}
        else if (resp == ERROR) return 1;
        tickdelay(micros_to_ticks(20000));
    }
    return 1;
}
