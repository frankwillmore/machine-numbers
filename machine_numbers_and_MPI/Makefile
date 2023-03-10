
add_float: add_float.c
	gcc add_float.c -o add_float

reduce: reduce.c
	mpicc reduce.c -o reduce

central_limit: central_limit.c
	mpicc central_limit.c -o central_limit

all: add_float reduce central_limit

clean: 
	rm -f a.out add_float reduce central_limit
