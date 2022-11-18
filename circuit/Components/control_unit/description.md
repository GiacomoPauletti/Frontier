I use the following bit-naming convention for recalling easily the opcode bits:
* From a to e, with a assigned to the most significant bit (left one) and e the least significant bit (right one)
  * a b c d e 
  * 0 0 0 0 0

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
