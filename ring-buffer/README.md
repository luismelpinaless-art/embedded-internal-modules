# Design Decisions
- **Single producer, single consumer.** `buffer_write` is the only function that moves `head`, and `buffer_read` the only one that moves `tail`. Each side only reads the other's index, so the two never compete to write the same variable.
- **No `is_full` flag.** A flag written by both sides would create a race condition. Instead, full and empty are derived from `head` and `tail` on every call.
- **One slot is sacrificed** to tell full from empty: `head == tail` always means empty. The usable capacity is therefore `BUFFER_SIZE - 1`.
- **Data first, index after.** A character is stored before `head` advances (and read before `tail` advances), so the other side never sees an index pointing to data that isn't ready.
- **Independent instances.** All state lives inside the `BUFFER` struct and every function receives a pointer to it, so there is no global state. You can create as many buffers as you need (for example, one for UART RX and another for UART TX). Each instance supports exactly one producer and one consumer.
- **Characters only.** It handles one character at a time, not strings or blocks.
- **A support module.** It is meant to back communication protocols such as UART, SPI and I2C, which will be developed in a separate repo.
