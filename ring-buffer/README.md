# Design Decisions
- This buffer uses an is_full flag to control the writing and reading of the data. 
- The implementation of this buffer works with single characters only, not with strings of characters together.
- It's a support module for communication protocols such as UART, SPI, I2C, etc, which will be developed in another repo.

