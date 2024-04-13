# USART Driver Optimization with Queue

This project aims to optimize the Universal Synchronous/Asynchronous Receiver/Transmitter (USART) driver for the Blue Pill development board based on the STM32 microcontroller. The optimization is achieved by implementing a queue data structure to efficiently manage data transmission and reception.

## Overview

USART communication is crucial for many embedded systems, facilitating serial communication with peripheral devices, sensors, and other microcontrollers. However, traditional USART implementations often suffer from inefficiencies, especially in handling asynchronous data transmission and reception.

To address these inefficiencies, this project leverages a queue data structure. Queues are first-in-first-out (FIFO) data structures that enable efficient management of data, ensuring that data is processed in the order it was received. By integrating a queue into the USART driver, we can optimize data transmission and reception, leading to improved system performance and reliability.

## Features

- Optimized USART driver for Blue Pill development board.
- Integration of a queue data structure for efficient data management.
- Support for asynchronous data transmission and reception.
- Improved system performance and reliability.
- Detailed debugging demonstration provided in the video file `Keil_Keil_USART_Debugging_Using_Interrupt.mp4`.
- Visual representation of USART operation through register visualization and logic analyzer frame.

## Contents

- `APP/`: Contains the application used to test the USART driver.
  - `APP.c`: Source code file for the application.
  - `APP.h`: Header file for the application.
- `Inc/`: Contains global header files.
  - `Stm32f103x6.h`: Header file containing all registers.
- `MCAL/`: Contains peripheral driver files.
  - `Inc/`: Contains local header files for peripheral drivers.
    - `fifo.h`: Header file for the FIFO implementation.
    - `USART.h`: Header file for USART driver.
    - `GPIO.h`: Header file for GPIO operations.
    - `RCC.h`: Header file for RCC (Reset and Clock Control) operations.
    - `EXIT.h`: Header file for external interrupt handling.
  - `fifo.c`: Source code file for the FIFO implementation.
  - `USART.c`: Source code file for the optimized USART driver.
  - `GPIO.c`: Source code file for GPIO operations.
  - `RCC.c`: Source code file for RCC (Reset and Clock Control) operations.
  - `EXIT.c`: Source code file for external interrupt handling.
- `main.c`: Source code file containing the main function to run the application.
- `Keil_Keil_USART_Debugging_Using_Interrupt.mp4`: Video file demonstrating the debugging process in Keil uVision, showcasing register visualization and logic analyzer frame.
- `README.md`: You are here.

## Video Demonstration

Watch the detailed debugging and operation demonstration in the video below:

[![USART Debugging Using Interrupt - Video Demonstration](https://example.com/video_thumbnail.png)](https://example.com/Keil_Keil_USART_Debugging_Using_Interrupt.mp4)

Replace `https://example.com/video_thumbnail.png` with the URL of the thumbnail image for your video, and `https://example.com/Keil_Keil_USART_Debugging_Using_Interrupt.mp4` with the URL of the video file itself.

## Contributing

Contributions to this project are welcome! If you have ideas for further optimization or improvements, feel free to open an issue or submit a pull request.

## Acknowledgments

Special thanks to the creators of Keil uVision and the developers of the Blue Pill development board for their tools and hardware, enabling embedded systems development and optimization.

---

Feel free to customize this README according to your specific project details and requirements. Happy optimizing! 🚀
