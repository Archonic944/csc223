# Chapter 1: Hardware Components of the Computer System

## The Computer

- Integrated circuits replaced individual transistors, resistors, and capacitors.
- We are working with a microcomputer.
- A CPU could be a single integrated circuit, a rack full of printed circuit boards, or anything in between.

## The 8080 and its relatives

- The Intel 8080 was the first widely used microprocessor.
- The instruction set of the 8080 became the industry standard.
- Intel later produced the 8085, a chip with the same instruction set and simplified power supply + faster processing.
  - > The 8085 greatly simplifies things for the hardware designer. Simply connect a single +5 volt DC power supply, connect either a crystal or a resistor-capacitor (RC) network between pins 1 and 2, and the 8085 is ready to run.

## Instructions in Memory

- CPUs fetch opcodes from memory one at a time, decode them, execute them, and fetch the next instruction.
- Initially, we would key in programs manually, but later, computers had a small program in ROM to load our programs automatically.
- PROM is programmable ROM (an IC fabricated with no stored program, but can be "burned" with a program later).
- EPROM is erasable PROM.

## Mass Storage

- 8080 microcomputers can address 65,536 bytes of memory (64KB).
- Mass storage is any external memory; even RAM outside of our 64KB.
- Addressing more than 64KB is difficult...

## Disk Addressing

- A disk is made up of circular tracks, which are divided into sectors.
  - Each sector has its own address (e.g. track 2 sector 5) called a **record**
  - Records intially held 128 bytes
- CP/M is designed to eliminate the need to know the physical layout of the disk.

## Hard Copy

- A line printer does not print one character at a time, but instead, receives characters, stores in them in a buffer, and stores them until a carriage return is received
- References to a line printer are different than references to the printer on the console.
- We do not need a line printer because we can screenshot and save things.

## Input/Output Devices

- Usually, we can read and write to floppy disks, but sometimes we need to read paper tape.
- The CP/M operating system was generated on a computer that expected reader and punchers to be available, so those device names became the default for I/O devices.
    - > And we have all been sorry ever since.
- Modem: (Modulator-demodulator) Enables us to communicate with otehr computers over a telephone line.
    - Modulates a carrier tone to send data, and demodulates a carrier tone to receive data.
- ASCII is the American Standard Code for Information Exchange.
- More peripherals can be added that "look like" a modem to the computer.

## A simple computer system

- Minimum hardware configuration for the book's exercises:
    - At least 1 floppy disk drive
    - At least 16KB of RAM
    - A terminal
    - ~~A print writer~~
- Throughout the book, we will jump into writing, editing, assembling, and debugging programs. We will learn instructions along the way instead of studying them first.




## Vocab

- **Terminal** The device through which we interact with the computer.
- **TTY** The short name for the "ASR-33 Teletype", a popular terminal in the olden days.
- **CRT** Cathode Ray Tube, the technology used in early computer monitors (or a name for an old monitor).
- **CPU** Central Processing Unit, the "brain" of the computer.
- **Intel 8080** The first widely used microprocessor.
- **Intel 8085** A later version of the 8080 with a simplified power supply and faster processing.
- **Opcode** Operation code, the part of an instruction that specifies the operation to be performed.
- **ROM** Read-Only Memory
- **Word** 40 bits, later broken up into 5 bytes of 8 bits each.
- **Record** A group of words treated as a unit (e.g. track 1 sector 5)
