I use the following bit-naming convention for recalling easily the opcode bits:
* From a to e, with a assigned to the most significant bit (left one) and e the least significant bit (right one)
  * a b c d e 
  * 0 0 0 0 0
 
 For a complete explanation of the purpose of this signals, go to [this file](../../../documentation/control_signals.md).  
 
 ### FULL CIRCUIT
![alt_text__](https://github.com/GiacomoPauletti/Frontier/blob/e117ec560269a53e7a5579a90f4d1dd80247ddbf/circuit/Components/control_unit/full_circuit0.png)
![alt_text__](https://github.com/GiacomoPauletti/Frontier/blob/e117ec560269a53e7a5579a90f4d1dd80247ddbf/circuit/Components/control_unit/full_circuit1.png)

This is the full control_unit of the CPU.
It generates all signals that control all units and all MUX, making them behave as required by the specific instruction.

Here follows the table of the signals for each instruction:
| ISTRUZIONE | OPCODE | FlagWrite | ALUOp | ALUSrc2 | ImmType0 | ImmType1 | Branch | Jump | JumpSrc | RegWrite | MemToRead | MemWrite |
|------------|--------|-----------|-------|---------|----------|----------|--------|------|---------|----------|-----------|----------|
| add        | 00001  | 1         | 0001  | 0       | X        | X        | 0      | 0    | X       | 1        | 0         | 0        |
| sub        | 00010  | 1         | 0110  | 0       | X        | X        | 0      | 0    | X       | 1        | 0         | 0        |
| and        | 00011  | 0         | 1011  | 0       | X        | X        | 0      | 0    | X       | 1        | 0         | 0        |
| or         | 00111  | 0         | 1110  | 0       | X        | X        | 0      | 0    | X       | 1        | 0         | 0        |
| not        | 00000  | 0         | 0000  | 0       | X        | X        | 0      | 0    | X       | 1        | 0         | 0        |
| mul        | 00100  | 0         | X     | 0       | X        | X        | 0      | 0    | X       | 1        | 0         | 0        |
| div        | 00110  | 0         | X     | 0       | X        | X        | 0      | 0    | X       | 1        | 0         | 0        |
| addi       | 01001  | 1         | 0001  | 1       | 0        | 1        | 0      | 0    | X       | 1        | 0         | 0        |
| andi       | 01011  | 0         | 1011  | 1       | 0        | 1        | 0      | 0    | X       | 1        | 0         | 0        |
| ori        | 01111  | 0         | 1110  | 1       | 0        | 1        | 0      | 0    | X       | 1        | 0         | 0        |
| muli       | 01100  | 0         | X     | 1       | 0        | 1        | 0      | 0    | X       | 1        | 0         | 0        |
| divi       | 01110  | 0         | X     | 1       | 0        | 1        | 0      | 0    | X       | 1        | 0         | 0        |
| slli       | 01000  | 0         | X     | 1       | 0        | 1        | 0      | 0    | X       | 1        | 0         | 0        |
| srli       | 01010  | 0         | X     | 1       | 0        | 1        | 0      | 0    | X       | 1        | 0         | 0        |
| mv         | 00101  | 0         | 1010  | 0       | X        | X        | 0      | 0    | X       | 1        | 0         | 0        |
| load       | 10010  | 0         | X     | X       | X        | X        | 0      | 0    | X       | 1        | 1         | 0        |
| store      | 10011  | 0         | X     | X       | X        | X        | 0      | 0    | X       | 0        | 0         | 1        |
| lui        | 11000  | 0         | ?     | 1       | 0        | 0        | 0      | 0    | X       | 1        | 0         | 0        |
| b          | 11110  | 0         | X     | X       | 1        | 0        | 1      | 1    | 0       | 0        | 0         | 0        |
| jal        | 01101  | 0         | X     | X       | 0        | 0        | 0      | 1    | 1       | 1        | 0         | 0        |
| jalr       | 11101  | 0         | X     | X       | X        | X        | 0      | 1    | 0       | 1        | 0         | 0        |
| j          | 11100  | 0         | X     | X       | 0        | 0        | 0      | 1    | 1       | 0        | 0         | 0        |
| jr         | 10101  | 0         | X     | X       | X        | X        | 0      | 1    | 0       | 0        | 0         | 0        |
| in         | 10000  | 0         | X     | X       | X        | X        | 0      | 0    | X       | 1        | 0         | 0        |
| out        | 10001  | 0         | X     | X       | X        | X        | 0      | 0    | X       | 0        | 0         | 0        |

X stands for "dont't care", ? stands for "work in progress".  
The following signals have been omitted because their columns were equivalent to other columns:
* WriteRa, AluSrc1: equivalent to Branch
* MemRead: equivalent to MemToReg

### ALU OPERATION
![alt text  ](https://github.com/GiacomoPauletti/Frontier/blob/124cc740786ddc1c4ed53e6f7818cfa397a218ef/circuit/Components/control_unit/aluop.png)  
OpCode is refered to a logical-arithmetical operation if ***a* bit is zero**.
For example:
  * 00010 is a logical-arithmetical operation (in particular it's a sub), but 10010 it's not

Not all opcodes with `a=0` are useful ALU operation, because there are more opcodes than possible (and useful) ALU operation.
**AluOp** is the signal that specifies to ALU the operation to do.  
This circuits generates from the 3 last bit of the opcode, the AluOp according to 74ls181 ic (ALU ic).  
ALso **M** (ALU mode) and **Cn** (Carry in) are required for each operation.

The following table resumes all useful cases of the circuit, with the 2nd colum being the input and the last 3 the outputs:


| Operation     | Opcode        |AluOp         | M     | Cn  |
|:-------------:|:-------------:|:------------:|:-----:|:---:|
| not | 00000 | 0000 | 1 | 1 |
| add | 00001 | 1001 | 0 | 1 |
| sub | 00010 | 0110 | 0 | 0 |
| or  | 00111 | 0001 | 0 | 1 |
| and | 00011 | 1011 | 0 | 1 |
| mv  | 00101 | 1010 | 1 | 1 |

Moreover, the *b* bit indicates wether the second ALU operand is a register (`b=0`) or an immediate (`b=1`).

There is no real logic behind the circuit. I started observing how the AluOps are required by the 74ls181, then
I tried to make a circuit valid for all of them.  
Maybe it's not the most optimized one, but I can consider myself satisfied.

### CIRCUIT PART 0
![alt_text__](https://github.com/GiacomoPauletti/Frontier/blob/d0f188552f4eb62b1f73ab4b1a75a1300f266432/circuit/Components/control_unit/part0.png)
* AluSrc2 = b
* FlagWrite = (e xor d) and not c and not a
  * Active only for "add", "addi" and "sub" instructions
* JumpSrc = 1 if the offset is in a register, 0 if it's immediate
  

### CIRCUIT PART 1
![alt_text__](https://github.com/GiacomoPauletti/Frontier/blob/d0f188552f4eb62b1f73ab4b1a75a1300f266432/circuit/Components/control_unit/part1.png)
* Jump = branch and not d
  * Jump = 1 if it's a jump instruction but not a branch
* Branch = PcSrc = WriteRA = AluSrc1 = (a and b) xor ( not a and b and c and not d and e)
  * First xor input is for "jalr", "j", "jr" and "b" instrctions
  * Second xor input is for "jal" instruction
* ImmType0 = branch and d
  * ImmType0 = 1 only with "b" instruction
* ImmType1 = not a and (not(c and not d and not e))
  * ImmType1 = 1 only with logical-arithmetical instructions
  * Nand used for excluding "jal" instruction

ImmType = 00 -> lui, jal and j
ImmType = 01 -> b
ImmType = 10 -> logical-arithmetical instructions
  
### CIRCUIT PART 2
![alt_text__](https://github.com/GiacomoPauletti/Frontier/blob/d0f188552f4eb62b1f73ab4b1a75a1300f266432/circuit/Components/control_unit/part2.png)
* MemWrite = a and not b and not c and d and e
  * It's active only with a "store" instruction
* MemToReg = MemRead = a and not b and not c and d and not e
  * It's active only with a "load" instruction"
* RegWrite = not(a and (b xor e)) or (a and b and notc and not d and note)
  * It's active always except for "j", "jr", "b", "store" and "out"
  * The second or operand is used to activate RegWrite also with "lui" instruction 


