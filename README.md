# BM78
* This project would be responsible for handling the communication with bluetooth module, BM78spps5mc2-0004aa-nd.
* Find the datasheet and other relevant documents in the following link: [https://www.microchip.com/en-us/product/BM78](https://www.microchip.com/en-us/product/BM78).
  - [BM78-Bluetooth Dual Mode Module Datasheet][1]
  - [IS1678S UART Command Set User Guide][2]
* The code would be based off the following GitHub repository: [https://github.com/kubovy/mclib/blob/master/modules/bm78.c](https://github.com/kubovy/mclib/blob/master/modules/bm78.c)

# Developer Notes:
* Jul 30, 2023:
  - Repository created.
  - Added README file.
  - Added transmit-related functions.
  - To do:
    - Figure out the pin configuration settings needed to enable bluetooth capabilities on the STM32F46VE board.
    - Figure out the UART settings needed to create a UART instance on UART3 and share it to main.h.
    - Figure out how long the "Command_Complete" event would be during reception. Update sendPacket function.
    - Setup the HAL receive callback function.

[1]: https://ww1.microchip.com/downloads/aemDocuments/documents/WSG/ProductDocuments/DataSheets/60001380E.pdf
[2]: https://ww1.microchip.com/downloads/en/DeviceDoc/IS1678S_UARTCommandSet_UserGuide.pdf
