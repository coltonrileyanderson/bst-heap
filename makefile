OBJS = integer.o string.o real.o scanner.o sll.o dll.o stack.o queue.o bst.o heap.o 
OOPTS = -Wall -Wextra -g -c -std=c99
LOPTS = -Wall -Wextra -g -std=c99

all : test-bst test-heap heapsort bst-0-10

test-bst : test-bst.o $(OBJS)
	gcc $(LOPTS) test-bst.o $(OBJS) -o test-bst

test-heap : test-heap.o $(OBJS)
	gcc $(LOPTS) test-heap.o $(OBJS) -o test-heap

heapsort : heapsort.o $(OBJS)
	gcc $(LOPTS) heapsort.o $(OBJS) -o heapsort

bst-0-10 : bst-0-10.o $(OBJS)
	gcc $(LOPTS) bst-0-10.o $(OBJS) -o bst-0-10

test-bst.o : test-bst.c bst.h sll.h queue.h integer.h string.h real.h scanner.h
	gcc $(OOPTS) test-bst.c

test-heap.o : test-heap.c bst.h heap.h sll.h dll.h queue.h stack.h integer.h string.h real.h scanner.h
	gcc $(OOPTS) test-heap.c

bst-0-10.o : bst-0-10.c bst.h heap.h sll.h dll.h queue.h stack.h integer.h string.h real.h scanner.h
	gcc $(OOPTS) bst-0-10.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

string.o : string.c string.h
	gcc $(OOPTS) string.c

real.o : real.c real.h
	gcc $(OOPTS) real.c

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

sll.o : sll.c sll.h
	gcc $(OOPTS) sll.c

dll.o : dll.c dll.h
	gcc $(OOPTS) dll.c

stack.o : stack.c stack.h
	gcc $(OOPTS) stack.c

queue.o : queue.c queue.h
	gcc $(OOPTS) queue.c

bst.o : bst.c bst.h
	gcc $(OOPTS) bst.c

heap.o : heap.c heap.h
	gcc $(OOPTS) heap.c

heapsort.o : heapsort.c
	gcc $(OOPTS) heapsort.c

#replace with specific BST you would like to test
test1 : all
	echo testing bst-0-10
	./bst-0-10
	echo

test : all
	echo testing bst
	./test-bst
	echo
	echo testing heap
	./test-heap
	echo

valgrind : all
	echo testing bst
	valgrind --leak-check=full ./test-bst
	echo

clean :
	rm -f $(OBJS) test-*.o heapsort.o bst-0-10.o test-bst test-heap heapsort bst-0-10