/*
 * USART.h
 *
 *  Created on: Apr 1, 2023
 *      Author: Abdelrahman Aref
 */

#ifndef INC_USART_H_
#define INC_USART_H_

#include "RCC.h"
#include "fifo.h"

typedef struct
{
    uint8_t  USART_Mode;
    uint32_t BaudRate;
    uint8_t  Payload_Length;
    uint8_t  Parity;
    uint8_t  StopBits;
    uint8_t  HW_FlowControl;
    uint8_t  IRQ_Enable;
    void (* P_IRQ_CallBack)(void);
} USART_Config_t;

#define TX_BUFFER_SIZE  128
#define RX_BUFFER_SIZE  128

element_type tx_buffer[TX_BUFFER_SIZE];
element_type rx_buffer[RX_BUFFER_SIZE];

FIFO_Buffer_t tx_fifo;
FIFO_Buffer_t rx_fifo;

#define UART_Mode_RX                0U
#define UART_Mode_TX                1U
#define UART_Mode_TX_RX             2U

#define UART_BaudRate_2400         2400
#define UART_BaudRate_9600         9600
#define UART_BaudRate_19200        19200
#define UART_BaudRate_57600        57600
#define UART_BaudRate_115200       115200
#define UART_BaudRate_230400       230400
#define UART_BaudRate_460800       460800
#define UART_BaudRate_921600       921600
#define UART_BaudRate_225000       2250000
#define UART_BaudRate_4500000      4500000

#define UART_Payload_Length_8B     0b0U
#define UART_Payload_Length_9B     0b1U

#define UART_Parity_Disable        0U
#define UART_Parity_Enable         1U
#define UART_Parity_EVEN           2U
#define UART_Parity_ODD            3U

#define UART_StopBits_1            0b00U
#define UART_StopBits_half         0b01U
#define UART_StopBits_2            0b10U
#define UART_StopBits_1_half       0b11U

#define UART_HW_FlowControl_NONE   0U
#define UART_HW_FlowControl_RTS    1U
#define UART_HW_FlowControl_CTS    2U
#define UART_HW_FlowControl_RTS_CTS 3U

#define UART_IRQ_Enable_NONE       0U
#define UART_IRQ_Enable_TXE        1U
#define UART_IRQ_Enable_TC         2U
#define UART_IRQ_Enable_RXNEIE     3U
#define UART_IRQ_Enable_PE         4U

#define Polling_Mechanism           1U
#define Interrupt_Mechanism         0U

void MCAL_UART_Init(USART_t* USARTx, USART_Config_t* UART_Config);
void MCAL_UART_DeInit(USART_t* USARTx);
void MCAL_UART_GPIO_Set_Pins(USART_t* USARTx);
void MCAL_UART_SendData(USART_t* USARTx, uint16_t* P_TxBuffer, uint8_t Mechanism);
void MCAL_UART_ReceiveData(USART_t* USARTx, uint16_t* P_RxBuffer, uint8_t Mechanism);
void MCAL_UART_WAIT_TC(USART_t* USARTx);

#endif /* INC_USART_H_ */
