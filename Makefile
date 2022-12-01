CC = gcc
CFLAGS = -g
OBJ = build/glthread.o build/graph.o build/interface.o build/link.o build/node.o

TARGET:out

out: test.o ${OBJ}
	${CC} ${CFLAGS} test.o ${OBJ} -o out

test.o:test.c ${OBJ}
	${CC} ${CFLAGS} -c test.c -o test.o

build/glthread.o:lib/glthread.c
	${CC} ${CFLAGS} -c lib/glthread.c -o build/glthread.o

build/graph.o:lib/graph.c
	${CC} ${CFLAGS} -c lib/graph.c -o build/graph.o

build/interface.o:lib/interface.c
	${CC} ${CFLAGS} -c lib/interface.c -o build/interface.o

build/link.o:lib/link.c
	${CC} ${CFLAGS} -c lib/link.c -o build/link.o

build/node.o:lib/node.c
	${CC} ${CFLAGS} -c lib/node.c -o build/node.o