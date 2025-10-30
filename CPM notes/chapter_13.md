# Chapter 13: Buffered Input/Output

**Chapter goal**: enter, assemble, and test subroutines that transfer
*a line at a time*

## The importance of backups

We periodically erase all .bak files, so it's a good idea to save
an actual backup of our file.

The chapter suggests using C12 as the file extension to identify the version of the file (chapter 12).

## Library files

We should use library files to work with smaller files instead of one
very large source file.

ED can easily merge a lib file with the current buffer using the
R command.

We create CPMIO.asm, CH13.lib, and TESTC13.lib.

Using the R command then the E command within ED will cause the
libraries that we R'd to be saved appended with the source.

## Editing the program

We start deleting the old test program. Each one sets up the stakc pointer, and will not change from one program to another.

We use the RBUFF code to read a buffer.

## Subroutines

- CCRLF: starts a new line by printing CR and LF to the console using the CO subroutine. A byte saving technique used JMP CO instead of CALL CO and RET. This works because CO: is the last instruction in the CCRLF subroutine, and there's no need to return to CCRLF, so doing a raw JMP without storing the CCRLF instruction pointer will just jump back to the previous program. If we put CO immediately after CCRLF then we wouldn't even need JMP CO. But if we used that trick, things would get dicey later when we needed to edit/make insertions.
- COMSG: displays a line of text. Uses the index register (H/L) to point to one character at a time. You start by pointing to the first character in the index register (LXI H, SINON). COMSG increments that register and outputs the character until it reaches a null terminating character (0x00). We use RZ for the conditional and ORA for the dummy instruction that sets the zero flag. This is a case where blank lines are especially helpful because the RZ somewhere in the middle of the function isn't as obvious as RET at the end of our other subroutines.
   - DB allows us to define constant variables to the assembler. You can combine strings (use single quotes) and symbols; concatenate with commas.
 - CIMSG: gets a line from the operator. It gets a line using the BDOS call to INBUF:, for whcih some overhead is required (such as defining the maximum character count and pointing DE to where we want the characters to be stored. The line is then converted from the BDOS format (character count then characters) to our format (null-terminated sequence).

## Debugging

DDT allows you to step through your program and run commands, such as inspecting the values of registers.

It replaces the BDOS routines in case you need to trace every call the program makes.

You can use interrupt calls to add breakpoints, which DDT also subs out the vectors of.
