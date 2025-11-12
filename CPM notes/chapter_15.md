# Chapter 15: The File Control Block

*This chapter covers file access via the File Control Block. After completing it, we will have a full understanding of CP/M and be ready to write our own programs.*

## Getting to know the FCB

- Our disk accesses will use the giant hook at location 5.
- The FCB is a 33-byte block of RAM that contains information about a file, and workspace that the ystem uses to perform write operations.
- The TFCB (transient file control block) is located at 005ch through 007ch. It is created by CP/M after a command line typed by the operator.
- Default TFCB structure:
