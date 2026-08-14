# Design Decisions
- This buffer uses a counter variable to determine if it is full or empty.
- The implementation of this buffer works with single characters only, not with strings of characters together.
- The next step in the design process is to implement an `is_full` flag to ensure buffer operations are atomic, making it safe for use with ISRs.
