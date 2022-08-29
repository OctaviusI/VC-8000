# The VC8000 Computer

The VC8000 is a decimal computer with 1,000,000 words of memory. Each word consists of 9 decimal digits. There is an additional 10 words of memory called registers. These are on chip memory.  The machine language instructions for the VC8000 is of the following form  Note: each has the same number of digits.

<font size="4" class="auto-style4"><span class="auto-style1">                             |2 digits             | 1 digit                 |6 digits             |</span>  
<span class="auto-style1">                             |<u>operation code | register number |address portion|</u>  </span></font>

<font size="4" class="auto-style4"><span class="auto-style1">or</span></font>

<font size="4" class="auto-style4"><span class="auto-style1">                             |2 digits             | 1 digit                 |1 digit               |  5 digits     |</span>  
<span class="auto-style1">                             |<u>operation code | register number |register number| unused      |</u></span></font>

 A machine language program is a sequence of machine language instructions stored in memory. The computer runs a machine language program by executing machine instructions stored in successive words of memory. The VC8000 machine assumes that the first instruction to be executed will be at location 100\. The following are the machine language instructions for the VC8000.

NAME           OP. CODE     MEANING

<font size="4" class="auto-style4"><span class="auto-style1">ADD                     01           Reg <-- c(Reg) + c(ADDR)   (The contents of the register specified in the instruction and of the memory location specified by the address portion of the instruction are added together. The result is placed in the register.):  
</span>  
<span class="auto-style1">SUBTRACT         02            Reg <-- c(Reg) - c(ADDR)  
</span>  
<span class="auto-style1">MULTIPLY           03            Reg <-- c(Reg) * c(ADDR)  
</span>  
<span class="auto-style1">DIVIDE                 04            Reg <-- c(Reg) / c(ADDR)  
</span>  
<span class="auto-style1">LOAD                   05            Reg <-- c(ADDR)  
</span>  
<span class="auto-style1">STORE                06            ADDR <-- c(Reg)</span></font>

ADD REG            07            REG1 <--c(REG1) + c(REG2)   (Note: this is the second instruction format where two registers are specified.)

<span class="auto-style3">SUB</span><span class="auto-style1"> <span class="auto-style4">REG            08            REG1 <--c(REG1) - c(REG2)</span></span>

MULT REG          09            REG1 <--c(REG1) * c(REG2)  

<font class="auto-style4" size="4"><span class="auto-style1">DIV REG              10            REG1 <--c(REG1) / c(REG2)    
</span>  
<span class="auto-style1">READ                   11            A line is read in and the number found there is recorded in the specified memory address.  The register value is ignored.  
</span>  
<span class="auto-style1">WRITE                 12            c(ADDR) is displayed  The register value is ignored.  
</span>  
<span class="auto-style1">BRANCH              13           go to ADDR for next instruction.  The register value is ignored.  
</span>  
<span class="auto-style1">BRANCH MINUS  14          go to ADDR if c(Reg) < 0  
</span>  
<span class="auto-style1">BRANCH ZERO    15          go to ADDR if c(Reg) = 0  
</span>  
<span class="auto-style1">BRANCH POSITIVE 16       go to ADDR if c(Reg) > 0  
</span>  
<span class="auto-style1">HALT                    17           terminate execution</span></font><span class="auto-style3">.  The register value and address are ignored.</span>

We will write the following examples programs in class to get a feeling for this computer:

1.  Print the value of C(5)+C(300)
2.  Print C(200)*C(6)+C(300)*C(7)
3.  Read in a number and display its factorial.
4.  Read in 100 nos. and print their average.

 Note: there was actually a time when there were decimal computers.   There might be a time in the future when they are back.  Why??? Why not???
