# Altair Manual Part 3

- 25 toggle switches, 36 indicator and status LEDs
- Routine operations: 15 swtiches, 16 LEDs

## Front panel switches and LEDs

> The chapter contains descriptions of every switch and LEDs. My notes will contain some stand-out information.

The DATA switches are 7-0. The ADDRESS switches are 15-0.

UP denotes a 1 bit.

Use the EXAMINE switch to examine the contents of memory at the specified ADDRESS. Use the DEPOSIT switch to write the DATA to the specified ADDRESS.

- The single step switch runs an instruction, ≤5 machine cycles.

- The EXAMINE NEXT will increment the memory address, then EXAMINE.

## Indicator LEDs

Address LEDs are A15-A0. Data LEDs are D7-D0.

Indicator LEDs have information such as whether the memory is protected, whether the CPU is in a WAIT state, and whether a HOLD has been acknowledged.

## Status LEDs

Various LEDs meant to assist with the operation of the computer. Examples include MEMR, which indicates that the memory bus will be used for memory read data, INP, the address bus containing the address of an input device, and M1, indicating that the CPU is processing the first step of an instruction.

## Addition program instructions

The chapter contains precise instructions on how to load a basic addition program into the computer.

## C. Using the Memory

- The Altair does not automatically keep track of memory.
- The programmer must create a memory mapping, assigning certain types of data to certain blocks.

Example memory mapping:

> A typical memory map for the ALTAIR 8800 with 256 words of memory might assign programs to the first 100 words, subroutines to the second 100 words, and data to the remaining 56 words. Of course the various blocks of memory can be modified at will, and the main purpose of memory mapping is to provide a cohesive organization of the available memory.

| Memory Block       | Address Range | Purpose     |
| ------------------ | ------------- | ----------- |
| First 100 words    | 0x0000-0x0063 | Programs    |
| Second 100 words   | 0x0064-0x00C7 | Subroutines |
| Remaining 56 words | 0x00C8-0x00FF | Data        |

## D. Memory Addressing

- Direct addressing: Directly address the memory (2 bytes) after the instruction pointer.
- Register pair addressing: Use a register pair (BC, DE, HL) to point to memory. HL by default. Can be changed with STAX or LDAX.
- Stack pointer addressing: Uses a stack to PUSH and POP data from memory. The stack must be reserved by loading a memory address into the Stack Pointer (using the LXI instruction).
- Immediate addressing: Data is loaded as a part of the program. They are stored in the block of memory reserved for programs.
- Stack addressing of subroutines: This method allows for nested subroutine calls and returns, enabling more complex program structures.

## Operator Hints

1. Proofread your programs after you enter them into memory. Hit RESET (if you started at 0) then use EXAMINE NEXT to check each byte.
2. Use NOPs, an instruction that does nothing, to separate sections of code. This makes it easier to modify the program later.
3. Use the SINGLE STEP switch to run through your program one instruction at a time. This allows you to see the contents of the address and data LEDs change with each machine cycle.
