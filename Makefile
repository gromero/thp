OBJS=mmap.o

%.o:	%.c
	gcc -g -O0 $< -c -o $@

all:	${OBJS}
	gcc -g -O0 mmap.o -o mmap

clean:
	rm -fr ${OBJS}
	rm -fr mmap
