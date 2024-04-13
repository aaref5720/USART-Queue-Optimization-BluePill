#include "USART.h"

USART_Config_t* Global_USART_Config[3] = {NULL};

void MCAL_UART_Init(USART_t* USARTx, USART_Config_t* UART_Config)
{
    FIFO_init(&tx_fifo, tx_buffer, TX_BUFFER_SIZE);
    FIFO_init(&rx_fifo, rx_buffer, RX_BUFFER_SIZE);

    // 1. Enable the clock for given USART peripheral
    if (USARTx == USART1) {
        RCC->APB2ENR.USART1EN = TRUE;
        Global_USART_Config[0] = UART_Config;
    } else if (USARTx == USART2) {
        RCC->APB1ENR.USART2EN = TRUE;
        Global_USART_Config[1] = UART_Config;
    } else if (USARTx == USART3) {
        RCC->APB1ENR.USART3EN = TRUE;
        Global_USART_Config[2] = UART_Config;
    }

    // 2. Enable USART Module
    USARTx->CR1.UE = TRUE;

    // 3. Enable USART TX/RX engines according to the USART_Mode configuration item
    switch (UART_Config->USART_Mode) {
        case UART_Mode_RX:
            USARTx->CR1.RE = TRUE;
            break;
        case UART_Mode_TX:
            USARTx->CR1.TE = TRUE;
            break;
        case UART_Mode_TX_RX:
            USARTx->CR1.RE = TRUE;
            USARTx->CR1.TE = TRUE;
            break;
    }

    //  4. Payload width
    USARTx->CR1.M = UART_Config->Payload_Length;

    // 5. Configuration of parity control bit field
    if (UART_Config->Parity != UART_Parity_Disable) {
        USARTx->CR1.PCE = TRUE;
        USARTx->CR1.PS = (UART_Config->Parity == UART_Parity_EVEN) ? FALSE : TRUE;
    } else {
        USARTx->CR1.PCE = FALSE;
    }

    // 6. Configuration the number of stop bits
    USARTx->CR2.STOP = UART_Config->StopBits;

    // 7. USART HW Flow Control
    switch (UART_Config->HW_FlowControl) {
        case UART_HW_FlowControl_CTS:
            USARTx->CR3.CTSE = TRUE;
            break;
        case UART_HW_FlowControl_RTS:
            USARTx->CR3.RTSE = TRUE;
            break;
        case UART_HW_FlowControl_RTS_CTS:
            USARTx->CR3.CTSE = TRUE;
            USARTx->CR3.RTSE = TRUE;
            break;
    }

    // 8. Configuration baud-rate
    uint32_t pclk = (USARTx == USART1) ? MCAL_RCC_GetPCLK2Freq() : MCAL_RCC_GetPCLK1Freq();
    USARTx->BRR.DIV_Fraction = DIV_Fraction(pclk, UART_Config->BaudRate);
    USARTx->BRR.DIV_Mantissa = DIV_Mantissa(pclk, UART_Config->BaudRate);

    // 9. Enable or Disable Interrupt
    if (UART_Config->IRQ_Enable != UART_IRQ_Enable_NONE) {
        if (USARTx == USART1) {
            NVIC_ISER->NVIC_ISER1 |= (1 << (USART1_IRQ - 32));
        } else if (USARTx == USART2) {
            NVIC_ISER->NVIC_ISER1 |= (1 << (USART2_IRQ - 32));
        } else if (USARTx == USART3) {
            NVIC_ISER->NVIC_ISER1 |= (1 << (USART3_IRQ - 32));
        }

        switch (UART_Config->IRQ_Enable) {
            case UART_IRQ_Enable_TXE:
                USARTx->CR1.TXEIE = TRUE;
                break;
            case UART_IRQ_Enable_TC:
                USARTx->CR1.TCIE = TRUE;
                break;
            case UART_IRQ_Enable_RXNEIE:
                USARTx->CR1.RXNEIE = TRUE;
                break;
            case UART_IRQ_Enable_PE:
                USARTx->CR1.PEIE = TRUE;
                break;
        }
    }
}

void MCAL_UART_DeInit(USART_t* USARTx)
{
    if (USARTx == USART1) {
        RCC->APB2RSTR.USART1RST = TRUE;
        NVIC_ICER->NVIC_ICER1 |= (1 << (USART1_IRQ - 32));
    } else if (USARTx == USART2) {
        RCC->APB1RSTR.USART2RST = TRUE;
        NVIC_ICER->NVIC_ICER1 |= (1 << (USART2_IRQ - 32));
    } else if (USARTx == USART3) {
        RCC->APB1RSTR.USART3RST = TRUE;
        NVIC_ICER->NVIC_ICER1 |= (1 << (USART3_IRQ - 32));
    }
}

void MCAL_UART_GPIO_Set_Pins(USART_t* USARTx)
{
    GPIO_PinConfig_t PinConfig;

    if (USARTx == USART1) {
        MCAL_RCC_AFIO_EN();
        MCAL_RCC_GPIO_EN(GPIOA);

        if (Global_USART_Config[0]->USART_Mode != UART_Mode_TX) {
            PinConfig.GPIO_PinNumber = GPIO_PIN_10;
            PinConfig.GPIO_MODE = GPIO_MODE_Input_AF;
            PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_Input;
            MCAL_GPIO_Init(GPIOA, &PinConfig);
        }

        if (Global_USART_Config[0]->USART_Mode != UART_Mode_RX) {
            PinConfig.GPIO_PinNumber = GPIO_PIN_9;
            PinConfig.GPIO_MODE = GPIO_MODE_Output_AF_PP;
            PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
            MCAL_GPIO_Init(GPIOA, &PinConfig);
        }

        if (Global_USART_Config[0]->HW_FlowControl != UART_HW_FlowControl_RTS) {
            PinConfig.GPIO_PinNumber = GPIO_PIN_11;
            PinConfig.GPIO_MODE = GPIO_MODE_Input_AF;
            PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_Input;
            MCAL_GPIO_Init(GPIOA, &PinConfig);
        }

        if (Global_USART_Config[0]->HW_FlowControl != UART_HW_FlowControl_CTS) {
            PinConfig.GPIO_PinNumber = GPIO_PIN_12;
            PinConfig.GPIO_MODE = GPIO_MODE_Output_AF_PP;
            PinConfig.GPIO_OUTPUT_SPEED = GPIO_SPEED_10MHZ;
            MCAL_GPIO_Init(GPIOA, &PinConfig);
        }
    }
    // Similar configurations for USART2 and USART3...
}

void MCAL_UART_SendData(USART_t* USARTx, uint16_t* P_TxBuffer, uint8_t Mechanism)
{
    // Add data to FIFO buffer
    FIFO_enqueue(&tx_fifo, *P_TxBuffer);

    // Enable TXE interrupt to start transmission
    USARTx->CR1.TXEIE = TRUE;
}

void MCAL_UART_ReceiveData(USART_t* USARTx, uint16_t* P_RxBuffer, uint8_t Mechanism)
{
    // Check if receive FIFO is not empty
    if (!FIFO_isEmpty(&rx_fifo)) {
        // Dequeue data from FIFO buffer
        *P_RxBuffer = FIFO_dequeue(&rx_fifo);
    }
}

void MCAL_UART_WAIT_TC(USART_t* USARTx)
{
    // Wait until Transmission Complete (TC) flag is set
    while (!(USARTx->SR.TC));
}

void USART2_IRQHandler(void)
{
    // TXE interrupt handler
    if (USART2->SR.TXEIE && USART2->SR.TXE) {
        if (!FIFO_isEmpty(&tx_fifo)) {
            uint16_t data = FIFO_dequeue(&tx_fifo);
            USART2->DR.DR = data;
        } else {
            // If FIFO is empty, disable TXE interrupt
            USART2->CR1.TXEIE = FALSE;
        }
    }

    // RXNE interrupt handler
    if (USART2->SR.RXNEIE && USART2->SR.RXNE) {
        uint16_t data = USART2->DR.DR;
        FIFO_enqueue(&rx_fifo, data);
    }
}

// Implement similar IRQ handlers for USART1 and USART3...
