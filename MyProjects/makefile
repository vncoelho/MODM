all: app_MODM

SRC_MODM = $(wildcard MODM/*.cpp) mainMODM.cpp

app_MODM: $(SRC_MODM:%.cpp=%.o) MODMScanner.o
	g++ -o $@ $^

MODMScanner.o: ../OptFrame/Scanner++/Scanner.cpp
	g++ -c $(CPPFLAGS) ../OptFrame/Scanner++/Scanner.cpp -o MODMScanner.o

-include $(SRC_MODM:%.cpp=%.d)

#CPPFLAGS = --std= c++11 -g
CPPFLAGS = --std= c++11 -Ofast  
CPPFLAGS += -MD -MP

examples:
	make -C ../Examples/
	
clean: 
	make clean -C ../Examples/
	rm -f app_*
	rm -f *.o *.d
	rm -f MODM/*.o MODM/*.d
