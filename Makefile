CC = gcc
CFLAGS = -g
OBJ = build/glthread.o build/graph.o build/interface.o build/link.o build/node.o

TARGET:out

out: test.o ${OBJ}
	${CC} ${CFLAGS} test.o ${OBJ} -o out

test.o:test.c ${OBJ}
	${CC} ${CFLAGS} -c test.c -o test.o

build/glthread.o:DS/glthread.c
	${CC} ${CFLAGS} -c DS/glthread.c -o build/glthread.o

build/graph.o:DS/graph.c
	${CC} ${CFLAGS} -c DS/graph.c -o build/graph.o

build/interface.o:DS/interface.c
	${CC} ${CFLAGS} -c DS/interface.c -o build/interface.o

build/link.o:DS/link.c
	${CC} ${CFLAGS} -c DS/link.c -o build/link.o

build/node.o:DS/node.c
	${CC} ${CFLAGS} -c DS/node.c -o build/node.o