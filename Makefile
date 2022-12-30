CC = gcc
CFLAGS = -g
OBJ = build/glthread.o \
	build/graph.o \
	build/interface.o \
	build/link.o \
	build/node.o \
	build/net.o \
	build/comm.o \
	build/layer2.o \
	build/arp_entry.o \
	build/arp_table.o \
	build/arp.o \
	build/ethernet.o


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

build/net.o:lib/net.c
	${CC} ${CFLAGS} -c lib/net.c -o build/net.o

build/comm.o:lib/comm.c
	${CC} ${CFLAGS} -c lib/comm.c -o build/comm.o

build/layer2.o:Layer2/layer2.c
	${CC} ${CFLAGS} -c Layer2/layer2.c -o build/layer2.o

build/arp_entry.o:Layer2/arp_entry.c
	${CC} ${CFLAGS} -c Layer2/arp_entry.c -o build/arp_entry.o

build/arp_table.o:Layer2/arp_table.c
	${CC} ${CFLAGS} -c Layer2/arp_table.c -o build/arp_table.o

build/arp.o:Layer2/arp.c
	${CC} ${CFLAGS} -c Layer2/arp.c -o build/arp.o

build/ethernet.o:Layer2/ethernet.c
	${CC} ${CFLAGS} -c Layer2/ethernet.c -o build/ethernet.o

clean:
	rm -rf build/*
	rm test.o
	rm out