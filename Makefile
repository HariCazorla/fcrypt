all: fcrypt

OBJECTS=fcrypt.o Buffer.o Exception.o File.o

fcrypt: $(OBJECTS)
	g++ $(OBJECTS) -o fcrypt

%.o: %.cc *.h
	g++ $(CXXFLAGS) -c $<
	
clean:
	rm -f fcrypt *.o
	