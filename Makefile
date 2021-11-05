all: fcrypt

OBJECTS=Fcrypt.o Buffer.o Exception.o File.o

fcrypt: $(OBJECTS)
	g++ $(OBJECTS) -o Fcrypt

%.o: %.cc *.h
	g++ $(CXXFLAGS) -c $<
	
clean:
	rm -f Fcrypt *.o
	