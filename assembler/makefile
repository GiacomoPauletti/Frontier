assembler: assembler.o common/common.o log/log.o syntax_check/syntax_check.o tokenize/tokenize.o
	gcc -o assembler assembler.o common/common.o log/log.o syntax_check/syntax_check.o tokenize/tokenize.o -lm

assembler.o:  assembler.c assembler.h common/common.h  syntax_check/syntax_check.h  tokenize/tokenize.h
	gcc -c assembler.c -o assembler.o

common.o: common/common.c common/common.h
	gcc -c common/common.c -o common/common.o

syntax_check.o: syntax_check/syntax_check.c syntax_check.h common/common.h tokenize/tokenize.h 
	gcc -c syntax_check/syntax_check.c -o syntax_check/syntax_check.o

tokenize.o: tokenize/tokenize.c tokenize/tokenize.h common/common.h 
	gcc -c tokenize/tokenize.c -o tokenize/tokenize.o

log.o: log/log.c log/log.h common/common.h
	gcc -c log/log.c -o log7log.o
