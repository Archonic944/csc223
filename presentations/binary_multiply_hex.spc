3a # Load multiplicand from mem 40
28
00
5f # Move A -> E (DE = multiplicand)
16 # Clear D (high byte of DE = 0)
00
3a # Load multiplier from mem 41
29
00
06 # Loop counter B = 8 (process 8 bits)
08
21 # Clear HL (product accumulator)
00
00
1f # Rotate A right through Carry (get multiplier LSB)
d2 # If Carry clear, jump to first XCHG
13
00
19 # (Executed only if Carry = 1) HL = HL + DE
eb # Swap HL <-> DE
29 # DE = DE + HL (effectively shift DE left)
eb # Swap back HL <-> DE
05 # Decrement loop counter
c2 # If B != 0, repeat loop (back to RAR)
0e
00
22 # Store HL (16-bit product) into mem 42/43
2a
00
fb # Enable interrupts
76 # Halt processor
