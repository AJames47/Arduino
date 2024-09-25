This project is to send a 6_channal data via nrf24 using the pre-build lib....
The lib can be downloaded and installed from the arduino IDE and integrated to the program file.
The pipeout can be anything from 0x000000000000 to 0xffffffffffff (remember the address is a hex value and should be the same on the receiving side too).
You can add more pipeline and connect the same transmiter with multiple receiver but make sure the pipeline address has to be different.
The nrf24 module is connected to the arduino using SPI communication protocol.
