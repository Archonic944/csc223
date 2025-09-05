# Binary Multiply

## Program

| ADDRESS       | MNEMONIC  | OCTAL CODE      | EXPLANATION                                      |
|---------------|-----------|-----------------|--------------------------------------------------|
| 000 001       | MVIA      | 076 002         | Multiplier to A Register                         |
| 002 003       | MVID      | 026 003         | Multiplicand to D,E Registers                    |
| 004 005       | MVIE      | 036 000         |                                                  |
| 006 007 010   | LXIH      | 041 000 000     | Clear H,L Registers to initialize Partial Product |
| 011 012       | MVIB      | 006 010         | Iteration Count to B Register                    |
| 013           | DADH      | 051             | Shift Partial Product left into Carry            |
| 014           | RAL       | 027             | Rotate Multiplier Bit to Carry                   |
| 015 016 017   | **JNC**   | 322 023 000     | Test Multiplier at Carry                         |
| 020           | DADD      | 031             | Add Multiplicand to Partial Product if Carry =1  |
| 021 022       | ACI       | 316 000         |                                                  |
| 023           | DCRB      | 005             | Decrement Iteration Counter                      |
| 024 025 026   | **JNZ**   | 302 013 000     | Check Iterations                                 |
| 027 030 031   | SHLD      | 042 100 000     | Store Answer in Locations 100,101                |
| 032 033 034   | **JMP**   | 303 000 000     | Restart                                          |

## Explanation

1. The **multiplier** (8 bits) is stored in the A register. 076 is the MVIA instruction,
   and **002** (= 2 in decimal) is our multiplier.
2. The **multiplicand** (8 bits) is stored in the E register (low byte). It is also storing a byte of 0 at the D register (high byte). This is because we need extra empty space for all the left shifting we're going to do.
3. The H and L registers are cleared to initialize the partial product. This is where we will accumulate our final answer!
4. The **iteration count** starts at 8. It will be decremented every time we move to the next bit of the multiplier. **When the iteration count is 0, the program will end; the mechanics of that will be explained later.**
5. We start by consuming the first bit of our 
