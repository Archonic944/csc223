# Chapter 7: Assembly Language

## Stuff Not In Jeff's Notes
*read jeff's notes then come back here.*

* A pseudo instruction is an instruction that is not compiled into machine code, but meant as a directive towards ASM.
  * For example, the ORG instruction indicates where the TPA is.
  * The EQU instruction defines a symbol that equals a hexadecimal value (like #define).
* Putting a character in quotes looks up the hexadecimal value of that character (built in to ASM - no need to EQU hex values of characters! woo!)
* After assembling, ASM produces the .PRN and .HEX. .HEX is the ascii-encoded hex, and .prn is a summary of the changes that ASM made.
* Feed the .hex into LOAD to produce a .com
* Hex numbers are easier for memory, because we talk about memory in kilobytes (1024 bytes).
 * 64K is 10000H in hex, simpler than the 65536 in decimal.
