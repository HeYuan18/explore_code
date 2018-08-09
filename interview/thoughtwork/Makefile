objects=maze.o sds.o
maze: $(objects)
	gcc -o maze $(objects)
$(objects): sds.h
clean:
	rm maze $(objects)
