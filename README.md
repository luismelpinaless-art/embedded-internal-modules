## Purpose

Almost every embedded project ends up rebuilding the same internal pieces: a buffer to move data between an interrupt and the main loop, a queue to hand work between modules, a state machine to organize behavior. This repo collects those pieces as small, self-contained modules, each designed carefully once and reusable everywhere.

They are called *internal* because they work **inside** the firmware, with no knowledge of any specific peripheral or board. Anything that talks to hardware or to the outside world is built on top of them, not in here.

## Design principles

Every module in this repo follows the same rules:

- **Instantiable as many times as needed.** All state lives inside a struct and every function receives a pointer to it, so there is no global state. The same module can be instantiated any number of times, each instance fully independent (for example, one buffer per communication channel).
- **Plain C, hardware-agnostic.** Modules are written in standard C and never touch registers directly. Anything that depends on the hardware goes through a HAL, which acts as the support layer. The module logic stays identical across microcontrollers and can even be tested on a PC.

## Usage

Each module lives in its own folder with its own README explaining its design decisions. Copy the folder into your project, add it to your include path, and include its header.

## License

MIT, see [LICENSE](./LICENSE).
