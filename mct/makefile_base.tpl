
GCC_FLAGS=-O3

examples:
	make -C ../Examples/
	
clean: 
	make clean -C ../Examples/
	rm -f app_*
	rm -f *.o
