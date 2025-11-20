# Brendan and Gabe's PMDAS Expression Parser
*Implementation link: https://github.com/BrendanO123/csc215/blob/main/PMDAS.ASM*

For our final project, Brendan and I wrote a mathematical expression parser in assembly.

Since it would be a pain to explain every single math helper and every single parse loop, this file will give a high level explanation
of the parser's logic.

This is a **broad simplification** of the parser. The real thing is about 900 lines of assembly. You are free to read through that; it can be found on Brendan's repo.

## Evaluation Logic

The main evaluation logic takes **two passes** through the expression.

First pass: 
* multiplication,
* division,
* left shift,
* right shift,
* and modulus.

Second pass: 
* addition
* subtraction.

*Every operand is parsed as a 16-bit signed integer.*

For individual calculations, the program parses the left operand, stores it in DE, parses the right operand, stores in in BC, then jumps to a different math function based on the operator between the two operands. See BONUS - Switch Statement to see how it does that.

After the calculation is finished, the result goes in DE. DE (the result of the calculation) then **replaces the original expression**. This allows for chained operations.

For example, if the expression was $4\times3\times2$, $12$ would be stored in place of $4\times3$, and then $12\times2$ would be calculated. Rinse and repeat until we're finished, then do it again for the addition/subtraction pass.

However, we don't simply insert more ASCII into the original buffer. That would require:

1. parsing additional strings
2. resizing the buffer (BAD!)

Instead, these intermediate calculation results are stored as a binary blob inserted directly *into* the ASCII. We can then continue to parse the expression seamlessly. More on that now...

## Intermediate Values

In our program, every calculation occurs between two operands, has one operator, and yields a single result. So, how do we handle 4\*3\*2?

First, 4\*3 is evaluated in the manner described above. The result (12) is stored back into the string buffer as a 16 bit signed integer. It overwrites "4\*3" (ASCII) with `12` (a binary number).

However, now we have mixed binary values with ascii values, which could get messy. Also, what if we have something like 15\*43? The 16-bit signed integer will only take up two bytes. But the original expression (15\*43) has **five characters.** Our intermediate value should completely overwrite the expression.

So, the intermediate value needs a special structure. which takes advantage of the fact that ASCII is a 7-bit encoding:

```
Offset from P:   0                1 ... (1+skip)−2      (1+skip)−1   (1+skip)
                 ┌──────────────┬──────────────────────┬────────────┬────────────┐
Bytes:           │  SKIP BYTE   │    (unused / old     │  VALUE_LO  │  VALUE_HI  │
                 │ (flag+count) │   expression bytes)  │   (E)      │   (D)      │
                 └──────────────┴──────────────────────┴────────────┴────────────┘
```

You'll notice that the "special structure is really just one thing... a "skip byte." The highest bit of the skip byte is always set.

You know what never sets the highest bit? ASCII. Therefore, when the parser sees the highest bit set, we know a binary value is coming down the pipe.

The rest of the skip byte is a 7 bit unsigned integer that represents **how much garbage we need to skip over.** Our original expression, 4\*3, would have no garbage. Since it is 3 bytes, we can overwrite it perfectly:

1. Skip byte (containing the set highest bit, then `0`.
2. Low byte of integer
3. High byte of integer

However, our other expression, $15\times43$, would need to have a skip byte of 2, since there would be two extra characters (x and 4) that the parser needs to skip over to get to the real binary data.

After all that work, the parser can just read intermediates as if they were a part of the original expression. 

## The Parentheses Stack

Now we have gotten to the fun part. This whole document, I have been lying to you, as all good educators do. We don't simply run over the **whole string** twice like cavemen. The program keeps a parentheses stack, and evaluates **parts** of the expression twice. Here's how it works:

1. When the parser sees an **open parenthesis**, it pushes that location to the parenthesis stack.
2. When parser sees a **close parentheses**, it pops the last open parenthesis location, and evaluates from there to the current location. Both the multiplication/div/etc pass and the addition/subtraction pass is performed over its length. That entire parenthetical expression is then replaced with a binary intermediate value.

And that's it!

> It's actually quite beautiful... I can't remember who came up with it. Was it me or Brendan? What am I saying?! I'm writing this document. Let the record show that ***I*** came up with it.

Having multiple stacks going on the 8080 (the paren stack and the call stack) is a tiny bit hacky. To switch between stacks we:

1. Clear HL
2. Use `DAD SP` to get call stack pointer into `HL`
3. Put `HL` somewhere safe
4. Load parentheses stack pointer into `HL`
5. Use `SPHL` to load `HL` into `SP`

Then, we can push and pop from the parentheses stack. Doing that whole dance again restores us to the call stack.

## BONUS - Switch Statement

To make certain things easier, like choosing what operation to perform based on a character, we cooked up a simple switch statement implementation.

In Java, a switch statement looks like this:

```java
switch (day) {
            case 1:
                System.out.println("Monday");
                break;
            case 2:
                System.out.println("Tuesday");
                break;
            case 3:
                System.out.println("Wednesday");
                break;
            case 4:
                System.out.println("Thursday");
                break;
            case 5:
                System.out.println("Friday");
                break;
            case 6:
                System.out.println("Saturday");
                break;
            case 7:
                System.out.println("Sunday");
                break;
            default:
                System.out.println("Invalid day number");
                break;
}
```

In assembly, our switch statement looks like this:

```asm
MULTPASS: DB '*',EVALMULT,'<',EVALLS,'>',EVALRS,'/',EVALDIV,'%',EVALMOD,'+',EVALSKIP,'-',EVALSKIP,0,EVALDEFAULT
LHLD CURRENTPASS
JMP SWITCH
```

And here's the implementation, comments and all:

```asm
SWITCH: ; A = switch character, HL = pointer to DB with case,hook_address,case,hook_address,0,default_case_hook_address
        ; HL is set to PC after jump so caller must preserve HL if they want it saved 
        ; stack has return address on top then any previous pushes below
        ; so if you run PUSH H; CALL SWITCH, then you will need to run POP H; XTHL
        ; to get the return address to the top of the stack and HL back from the push


        PUSH PSW ; save A
        MOV A,M ; test CASE value
        CPI 0 ; if CASE value is 0
        JZ SWITCHDEFAULT ; use case as default and execute case

        POP PSW ; restore A
        CMP M ; compare with CASE value
        JZ SWITCHNEXT ; if is equal, execute case
        INX H ; else HL += 3, continue
        INX H
        INX H
        JMP SWITCH

SWITCHDEFAULT:
        POP PSW
SWITCHNEXT:
        PUSH D ; load hook into HL
        INX H ; load LS byte
        MOV E,M
        INX H ; load MS byte
        MOV D,M
        XCHG
        POP D

        PCHL ; jump to hook
        ; return address is already in stack so hook case simply needs to return
```

Our "switch statement" is a series of cases cases (single byte) each followed by memory locations (two bytes).
You define those and then call SWITCH.

The "memory locations" after each case byte are called "hooks" because they point to machine code. That machine code is a "hook" that gets executed if the case check succeeds.
SWITCH starts at the first case, compares it to the target value, and if the comparison succeeds (`JZ` instruction), then it jumps to the hook.

If the comparison fails, it increments the pointer three times to skip the current case as well as the two address bytes.

Our switch statement even supports a default case!

---------------------

Well, that's it. I hope you enjoyed.

Brendan's GH: @BrendanO123
My GH: @Archonic944
