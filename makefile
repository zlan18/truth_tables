#Student ID: 140009228
#23 February 2016
#Logic Practical
#makefile

clean:
	rm *.o ttable

ttable: ttable_main.o formula_parser.o ttable_printer.o
	gcc ttable_main.o formula_parser.o ttable_printer.o -lm -o ttable -std=c99 -Wall -Wextra -g

ttable_printer.o: ttable_printer.c ttable.h
	gcc -c ttable_printer.c -std=c99 -Wall -Wextra -g

formula_parser.o: formula_parser.c ttable.h
	gcc -c formula_parser.c -std=c99 -Wall -Wall -g

ttable_main.o: ttable_main.c ttable.h
	gcc -c ttable_main.c -std=c99 -Wall -Wextra -g
