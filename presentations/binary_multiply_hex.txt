3a # Load multiplicand from mem 40
28
0
5f # Move A -> E (DE = multiplicand)
16 # Clear D (high byte of DE = 0)
0
3a # Load multiplier from mem 41
29
0
6 # Loop counter B = 8 (process 8 bits)
8
21 # Clear HL (product accumulator)
0
0
1f # Rotate A right through Carry (get multiplier LSB)
d2 # If Carry clear, jump to first XCHG
13
0
19 # (Executed only if Carry = 1) HL = HL + DE
eb # Swap HL <-> DE
29 # DE = DE + HL (effectively shift DE left)
eb # Swap back HL <-> DE
5 # Decrement loop counter
c2 # If B != 0, repeat loop (back to RAR)
e
0
22 # Store HL (16-bit product) into mem 42/43
2a
0
fb # Enable interrupts
76 # Halt processor
