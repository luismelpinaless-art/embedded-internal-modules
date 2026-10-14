# Embedded Button Debouncer

Button debouncer module in C for embedded systems.

## How it works

The debouncer is a four-state FSM. Each state waits for one condition before moving on.

- `ST_DB_IDLE`: button released, waiting for the pin to go high.
- `ST_DB_DEBOUNCE`: pin went high, the timer measures the debounce window. When it expires the pin is sampled again: still high confirms the press, low discards it as a glitch.
- `ST_DB_CLEAR`: press confirmed, waiting for the pin to go low.
- `ST_DB_OFF`: pin went low, the timer measures the release window. When it expires the pin is sampled again: still low confirms the release, high returns to `ST_DB_CLEAR` (the button never really left).

The result is read from two fields:

- A press is detected when `st_now == 1` and `st_before == 0`. It lasts exactly one `process_debounce()` call, and holding the button does not repeat it.
- `st_now` returns to 0 only after the release is confirmed, so every press produces its own edge.

## Design decisions

- `read_signal()` is a pure pin read. It never depends on `st_before`, so `ST_DB_CLEAR` really waits for the button to be released.
- `event` is a latch read by the next state, so on every transition it is set to the event that identifies the state being entered, not the one the previous state used to exit. Leaving an exit event in place makes the next state leave on its own, with the button unchanged.
- The timer must start inactive (`active = false` in `timer_init`). `timer_set()` arms it when a window begins and `timer_reset()` stops it when the window ends. A timer that starts active runs freely before the first press, and the first window ends early.
- Every window ends with `timer_reset()`, so no `EVT_TIMER_DONE` stays pending between windows.
- The pin is sampled only when a window expires, never in between.
- The window is counted in timer ticks, and the first tick is counted at the moment of detection. With a 15 tick window and a 1 ms tick, the press is confirmed 14 ms after the pin goes high.
- The falling edge is not exposed: `st_now` and `st_before` both become 0 in the same step. An event for "button released" would need them to be separated.
