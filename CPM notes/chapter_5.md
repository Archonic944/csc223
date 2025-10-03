# Chapter 5 - Organization of CP/M

- In order to load the operating system, PROM contains I/O access primitives (drivers)
- But, those drivers are incomplete. The full drivers are stored in the CBIOS.
  - Vectors that point to disk/IO access primitives are stored in a specific area.
- User programs access all devices through the BDOS call vector. CBIOS vectors address primitive routines such as power up, rest, and device driver functions.
- A "warm start" is used to restore CP/M after a program ends.
- There are a bunch of vectors (basically syscalls) that are connected to abstract functions within physical devices
- The CCP (console command processor) is what displays the > character and waits for a command to be entered from the console
- To customize CP/M to a new computer, all you have to do is provide the loader in PROM and the 15 routines (through jump vectors)

| Unit     | Size (bytes) |
| -------- | ------------ |
| 1 record | 128          |
| 1 block  | 256          |
| 1 group  | 1024         |

- Dynamic disk space allocation - keeping track of what files have been erased, so their space can be reused
- File Control Block (FCB) - contains information about a file, such as its name, extent, and physical location on disk
- The directory is a table of FCBs
- Don't ignore read errors in .COM files - a mistake in the binary stream is usually fatal
- If you encounter a disk error, try to CTRL-C or reboot the system.
- DDT = Dynamic Debugging Tool, a symbolic debugger for CP/M
- BDOS = Basic Disk Operating System, which looks for files in directories, reads into RAM, writes from RAM to disk, etc.
- The disk interaction that we'll be doing is through the BDOS, even though you can use CBIOS calls to directly perform disk i/o
- A customized driver for each device has to be included in the CBIOS for CP/M to work with new peripherals.

## Drivers

| Function | Description                                |
| -------- | ------------------------------------------ |
| CONST    | Test CON: for keyboard character ready.    |
| CONIN    | Wait for and read CON: keyboard character. |
| CONOU    | Send one character to CON: display.        |
| LIST     | Send one character to LST: device.         |
| PUNCH    | Send one character to PUN: device.         |
| READER   | Wait for and input one RDR: character.     |

- Drivers rely on the IOBYT to know which physical device to use (for example, batch CON: input vs keyboard, or CON: output to a CRT vs TTY)

## Using the Console

- Drive designation followed by greater than symbol (A>, B>, C>, etc) is the prompt
- Expects a built in program or a .COM file
- If the .COM is not on the current drive you can do A> B: MYPROG to run MYPROG.COM on drive B:
- Options can be file names (ambiguous or unambiguous + with drive designators or not) or any other info required
- The programmer, to implement options/file specifiers, receives the properly formatted names of any file(s) specified on the command line (TFCB), and the entire text of the command line (TBUFF)
- Some functions, resident functions, are not loaded from disk, but take memory space. They COULD all be stored as .com files, but that would waste time. "transient" commands are loaded from disk.
- SAVE, ERA (erase), REN (rename), DIR, TYPE (cat), PIP (copy) are resident functions
- STAT changes the physical assignment of a logical device
- You can use SUBMIT to run batch files
