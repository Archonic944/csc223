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

