## CONTROL SIGNALS
Control signals are used to make CPU behave differently based on which instruction is now processed.  

Follows the explanation of each signal:
*  **ALUOp** (ALU Operation) is a 4-bit bus which controls the operation to do by the ALU for the current instruction. The following table shows all possible values of ALUOp and the corrisponding operation:


| ISTRUZIONE | OPCODE | ALUOp | MODE(M) | C_in | ALU OPERATION |
|:------------:|--------:|:-------:|:---------:|:------:|:---------------:|
| add        | 00001  | 0001  | 0       | 1    | A + B         |
| sub        | 00010  | 0110  | 0       | 0    | A - B         |
| and        | 00011  | 1011  | 0       | 1    | A and B       |
| or         | 00111  | 1110  | 0       | 1    | A or B        |
| not        | 00000  | 0000  | 1       | 1    | not A         |
| mv         | 00101  | 1010  | 1       | 1    | B             |
| lui        | 11000  | 1010  | 1       | 1    | B             |
  
  
*  **ALUSrc2** (ALU Source 2) manages a multiplexer to decide which is the 2nd operand of ALU. If set to 0, operand is rs register, else, if set to 1, it's a 16-bit immediate

*  **ALUSrc1** (ALU Source 1) manages a multiplexer to decide which is the 1st operand of ALU. If set to 0, operand is rd register, else, if set to 1, it's PC (Program Counter). It's logically equivalent to Branch

*  **FlagWrite** is set to 1 if the current instruction modifies the flag register

*  **JumpSrc** (Jump Source) manages a multiplexer to decide where is the offset to add to PC. If set to 0, it's in rd register, else it's an immediate

*  **Jump** is 0 if the current operation is not performing a jump, else it's set to 1 (branch has Jump=0)

*  **Branch** is 0 if the current operation is not performing a branch **or a jump**, else it's set to 1 (so jumps have Branch=1)

*  **WriteRA** is logically equivalent to Branch, but it has a different name just for describing it's purpose. It's 1 if there is a branch because the updated register is not rd but RA. It manages the multiplexer which switches between rd and ra as destination register.

*  **ImmType0** and **ImmType1** are used to select how much an immediate has to be shifted


| IMM0 | IMM1 | SHIFT AMOUNT |      instructions     |
|:----:|:----:|:------------:|:---------------------:|
|   0  |   0  |     4 bit    |         jal, j        |
|   0  |   1  |    10 bit    | addi, subi, slli, ... |
|   1  |   0  |     8 bit    |         branch        |
  
  
*  **MemWrite** is 1 with store instructions, else 0. Store it's the only one to write in memory
*  
*  **MemRead** is 1 with load instructions, else 0. Load it's the only one to read from memory

*  **MemToReg** is logically equivalent to MemRead. Used to control the multiplexer which selects the input for register write. 1 if it's MemoryOut (only with load) else 0 for ALUout

*  **RegWrite** 1 if the instruction updates a register, else 0.