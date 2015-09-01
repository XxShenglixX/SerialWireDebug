#include "ProgramLoader.h"

/** tlvCreateSession is a function to create necessary element needed by TLV protocol */
Tlv_Session *tlvCreateLoaderSession(void) {
  static Tlv_Session session;
  
  session.handler = uartInit(UART_PORT, UART_BAUD_RATE);
  /* Set Initial state for send and receive*/
  session.sendState = END_SEND;
  session.receiveState = START_RECEIVE;
  
  session.tState = TRANSMISSION_FREE;
  session.TIMEOUT_FLAG = false;
  session.DATA_ARRIVE_FLAG = false;
  
  return &session;
}

/** tlvWriteTargetRegister is a function to write data into target register
  * 
  * input   : session contain a element/handler used by tlv protocol
  *           registerAddress is the address of the target register
  *           data is the data need to write into the target register
  *
  * return  : NONE
  */
void tlvWriteTargetRegister(Tlv_Session *session, uint32_t *registerAddress, uint32_t *data)  {
  
  /* create tlv packet with register address */
  Tlv *tlv = tlvCreatePacket(TLV_WRITE_REGISTER, 4, (uint8_t *)registerAddress);
  
  /* Insert data into tlv packet value */
  tlvPackIntoBuffer(&tlv->value[4], (uint8_t *)data, 4);
  tlv->length += 4;

  tlvSend(session, tlv);
}

/** tlvReadTargetRegister is a function to read target register
  * 
  * input   : session contain a element/handler used by tlv protocol
  *           registerAddress is the address of the target register
  *
  * return  : NONE
  */
void tlvReadTargetRegister(Tlv_Session *session, uint32_t *registerAddress)  {
  
  /* create tlv packet with register address */
  Tlv *tlv = tlvCreatePacket(TLV_READ_REGISTER, 4, (uint8_t *)registerAddress);
  tlvSend(session, tlv);
}