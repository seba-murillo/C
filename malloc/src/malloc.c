/*
 ============================================================================
 Name        : malloc.c
 Author      : Sebastian Murillo
 Version     : 1.0
 Copyright   :
 Description : simple malloc implementation
 ============================================================================
 */

/*
 * PREGUNTAR
 * 		como funciona malloc() original? por que retorna direcciones anteriores al heap_start?
 */

/*
 * reallocate(block->ptr, size)
 * 		if(invalid block pointer) => allocate()
 * 		if(block->size > size)
 * 			try to join(block, block->next)
 * 			if(cannot join) => allocate()
 * 				copy data to new_block
 * 				try to resize(new_block, size)
 * 				release(block)
 * 		if(block->size < size)
 * 			try to resize(block, size)
 * 			if(cannot resize) => allocate()
 * 				release(block)
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

/*
 * TEST = 1 -> tests allocate() and allocate_cleared()
 * TEST = 2 -> tests reallocate() to smaller size
 * TEST = 3 -> tests reallocate() to bigger size
 * TEST = 4 -> tests defragmentate()
 * TEST = 5 -> tests first-fit and best-fit separetely (see config)
 */

// [test config]
#define TEST 4
#define POLICY BEST_FIT
#define verbose 1
int show_bestfit_search = 0;
// [/test config]

// [config]
#define FIRST_FIT 1
#define BEST_FIT 2
#define WORD_SIZE 4
#define MIN_BLOCK_SPACE 4
// [/config]

typedef struct memoryBlock mBlock;

struct memoryBlock {
	unsigned int size;
	unsigned int used;
	void* ptr;
	mBlock* prev;
	mBlock* next;
};

void* allocate(unsigned int bytes);
void* allocate_cleared(const unsigned int bytes);
void* reallocate(void* ptr, unsigned int size);
mBlock* resize(mBlock* block, const unsigned int size);
mBlock* getSuficientMemoryBlock(const unsigned int bytes);
mBlock* getMemoryBlockFromPointer(void* ptr);
int release(void* ptr);
int align(const unsigned int bytes);
int join(mBlock* block);
int copy(mBlock* dest, mBlock* source, int bytes);
int defragmentate();
void print(const char* name, mBlock* block);
void print_data(void* ptr);
void print_all_blocks();
void print_all_blocks_state(char* title);

int alloc_counter = 0;
void* heap_start = 0;
mBlock* last = NULL;

int main(void) {
	//init
	printf(">malloc test started\n\n");
	//redirecto ERR->OUT
	if (dup2(fileno(stdout), fileno(stderr)) < 0) {
		perror("failed ERR->OUT redirection");
		exit(EXIT_FAILURE);
	}
	// config
	printf(">config:\n");
	printf("|\t%-20s[%lu]\n", "sizeof(mBlock):", sizeof(mBlock));
	printf("|\t%-20s[%d]\n", "test:", TEST);
	printf("|\t%-20s[%d]\n", "WORD_SIZE:", WORD_SIZE);
	printf("|\t%-20s[%d]\n", "MIN_BLOCK_SIZE:", MIN_BLOCK_SPACE);
	if (POLICY == FIRST_FIT)
		printf("|\t%-20s%s\n", "search policy:", "first fit");
	else if (POLICY == BEST_FIT)
		printf("|\t%-20s%s\n", "search policy:", "best fit");
	printf(">end of config\n\n");
	if (TEST == 1) { // allocate()
		printf(">STARTING TEST 1 - allocate() & allocate_cleared():\n\n");
		allocate(10);
		printf("\n");
		void* ptrA = allocate(360);
		printf("\n");
		allocate(20);
		printf("\n");
		// release()
		int result = release(ptrA);
		printf("\n");
		if (result > 0)
			printf("\terror releasing ptrA\n");
		ptrA = allocate(30);
		printf("\n");
		// allocate_cleared()
		void* ptrB = allocate_cleared(200);
		printf("\n");
		print_all_blocks();
		print_data(ptrB);
	}
	if (TEST == 2) { // realloc() to smaller size
		printf(">STARTING TEST 2 - reallocate():\n\n");
		void* ptr = allocate(60);
		printf("\n");
		sprintf(ptr, "%s", "I AM ALIVE!");
		printf("@formatting ptr to: [%s]\n\n", (char *) ptr);
		print_data(ptr);
		ptr = reallocate(ptr, 20);
		printf("\n");
		print_data(ptr);
		print_all_blocks();
	}
	if (TEST == 3) { // realloc() to bigger size
		printf(">STARTING TEST 3 - realloc():\n\n");
		// pointing to a non-allocate()-returned position
		void* fake_pointer = sbrk(0);
		printf("\n");
		// will fail -> redirect to allocate()
		reallocate(fake_pointer, 10);
		printf("\n");
		void* ptr = allocate(20);
		printf("\n");
		void* ptr2 = allocate(100);
		printf("\n");
		allocate(50);
		printf("\n");
		// free 100 bytes after ptr
		release(ptr2);
		printf("\n");
		printf("@block state so far:\n");
		print_all_blocks();
		// resize ptr to size 80 -> will join ptr with ptr2
		ptr = reallocate(ptr, 110);
		printf("\n");
		print_all_blocks();
	}
	if (TEST == 4) {
		printf(">STARTING TEST 4 - defragmentate():\n\n");
		// O: empty		X: used
		// blocks [X X O X O O X]
		allocate(50);
		printf("\n");
		allocate(100);
		printf("\n");
		getMemoryBlockFromPointer(allocate(150))->used = 0;
		printf("\n");
		allocate(200);
		printf("\n");
		getMemoryBlockFromPointer(allocate(250))->used = 0;
		printf("\n");
		getMemoryBlockFromPointer(allocate(300))->used = 0;
		printf("\n");
		allocate(350);
		printf("\n");
		print_all_blocks_state("> block state BEFORE defragmentate()");
		defragmentate();
		printf("\n");
		print_all_blocks_state("> block state AFTER defragmentate()");
	}
	if (TEST == 5) {
		printf(">STARTING TEST 4 - first-fit and best-fit search:\n\n");
		void* P1 = allocate(150);
		printf("\n");
		allocate(100);
		printf("\n");
		void* P2 = allocate(60);
		printf("\n");
		allocate(20);
		printf("\n");
		void* P3 = allocate(45);
		printf("\n");
		allocate(20);
		printf("\n");
		void* P4 = allocate(150);
		printf("\n");
		release(P1);
		printf("\n");
		release(P2);
		printf("\n");
		release(P3);
		printf("\n");
		release(P4);
		printf("\n");
		print_all_blocks_state("> block state BEFORE best-fit allocate()");
		printf("\n");
		show_bestfit_search = 1;
		allocate(50);
		printf("\n");
		print_all_blocks_state("> block state AFTER best-fit allocate()");
		printf("\n");
	}
	printf(">TEST FINISHED\n");
	return EXIT_SUCCESS;
}

void* allocate(unsigned int bytes) {
	if (verbose)
		printf(">allocate(%u) call: [%d]\n", bytes, ++alloc_counter);
	// check blocks in list
	mBlock* block = getSuficientMemoryBlock(bytes);
	if (block) {
		block->used = 1;
		if (block->size > bytes + sizeof(mBlock))
			resize(block, bytes);
		if (verbose)
			printf("|\tgetSuficientMemoryBlock() succeeded\n");
		if (verbose)
			printf(">%-20s[%p] of size [%u]\n", "allocate() returned",
					block->ptr, block->size);
		return block->ptr;
	}
	if (verbose)
		printf("|\tgetSuficientMemoryBlock() failed\n");
	//get more heap memory
	if (!heap_start)
		heap_start = sbrk(0);
	if (verbose)
		printf("|\textending heap memory...\n");
	// create new block
	bytes = align(bytes);
	block = sbrk(0);
	if (sbrk(sizeof(mBlock) + bytes) == (void*) -1) {
		perror("|\tfailed to extend heap memory");
		return NULL;
	}
	block->size = bytes;
	block->used = 1;
	//block->ptr = block + sizeof(mBlock);
	block->ptr = block + 1; // PREGUNTAR porque #$@#@! multiplica el '1' por sizeof(mBlock)
	block->prev = last;
	block->next = NULL;
	if (last)
		last->next = block;
	last = block;
	if (verbose)
		printf(">%-20s[%p] of size [%u]\n", "allocate() returned", block->ptr,
				block->size);
	return block->ptr;
}

void* allocate_cleared(const unsigned int bytes) {
	char* ptr = allocate(bytes);
	for (int p = 0; p < bytes; p++)
		ptr[p] = 0;
	return (void *) ptr;
}

void* reallocate(void* ptr, unsigned int size) {
	// redirrect to allocate()
	if (!ptr)
		return allocate(size);
	// reallocate to smaller size
	mBlock* block = getMemoryBlockFromPointer(ptr);
	if (!block) {
		if (verbose)
			printf(">reallocate(%p) from [???] to [%u]\n", ptr, size);
		perror(
				"|\tERROR: not an allocate() pointer: redirecting to allocate()");
		ptr = allocate(size);
		block = getMemoryBlockFromPointer(ptr);
		printf(">%-20s [%p] of size [%u]\n", "reallocate() returned", ptr,
				block->size);
		return ptr;
	}
	if (verbose)
		printf(">reallocate(%p) from [%u] to [%u]\n", ptr, block->size, size);
	// reallocate to bigger size
	if (size >= block->size) {
		// try to join with next => avoids data copy
		while (!join(block)) { // while join() works
			// is the joined space enough?
			if (size >= block->size)
				continue;
			// now block is big enough to hold 'size' -> resize if posible:
			if (verbose)
				printf("|\t@join - now size is [%u]\n", block->size);
			resize(block, size);
			printf(">%-20s [%p] of size [%u]\n", "reallocate() returned",
					block->ptr, block->size);
			return block->ptr;
		}
		// allocate again
		void* new_ptr = allocate(size);
		if (!new_ptr) {
			perror(
					"|\tERROR: failed to reallocate bigger size: allocate() failed\n");
			printf(">%-20s [%p] of size [%u]\n", "reallocate() returned", NULL,
					0);
			return NULL;
		}
		mBlock* new = getMemoryBlockFromPointer(new_ptr);
		// copy data
		if (copy(new, block, block->size)) {
			release(new);
			perror("failed to copy block data");
			return NULL;
		}
		printf(">%-20s [%p] of size [%u]\n", "reallocate() returned", new_ptr,
				new->size);
		release(block->ptr);
		return new_ptr;
	}
	// reallocate to smaller size
	else {
		// try to resize
		if (!resize(block, size)) {
			// resize did not work
			perror("|\tERROR: cannot resize block: redirecting to allocate()");
			// allocate again
			void* new_ptr = allocate(size);
			if (!new_ptr) {
				perror(
						"|\tERROR: failed to reallocate smaller size: allocate() failed\n");
				printf(">%-20s [%p] of size [%u]\n", "reallocate() returned",
						NULL, 0);
				return NULL;
			}
			mBlock* new = getMemoryBlockFromPointer(new_ptr);
			// copy data
			if (copy(new, block, new->size)) {
				release(new);
				perror("failed to copy block data");
				return NULL;
			}
			release(block->ptr);
			printf(">%-20s [%p] of size [%u]\n", "reallocate() returned", new,
					new->size);
			return NULL;
		}
		// resize worked
		printf(">%-20s [%p]\n", "reallocate() returned", block->ptr);
		return block->ptr;
	}
}

mBlock* resize(mBlock* block, const unsigned int size) {
	if (!block)
		return NULL;
	if (verbose)
		printf("|\t@resize\n");
	mBlock* new;
	new = block->ptr + size; //PREGUNTAR: a diferencia de antes, aca la suma anda bien
	/*
	 if(verbose){
	 printf("%-20s[%p]\n", "block:", block);
	 printf("%-20s[%p]\n", "block->ptr:", block->ptr);
	 printf("%-20s[%p]\n", "new:", new);
	 printf("%-20s[%ld]\n", "block - block->ptr:", (void *) block - block->ptr);
	 printf("%-20s[%ld]\n", "block - new:", (void *) block - (void *) new);
	 }
	 */
	if (sizeof(mBlock) + size + MIN_BLOCK_SPACE > block->size) { // already checked when calling, just making sure
		perror("|\timpossible to resize: blocksize too small.");
		return NULL;
	}
	new->size = block->size - sizeof(mBlock) - size;
	new->used = 0;
	new->ptr = new + sizeof(mBlock);
	new->prev = block;
	new->next = block->next;
	if (block->next)
		block->next->prev = new;
	block->size = size;
	block->next = new;
	if (verbose) {
		printf("|\t\tblock resized to [%u]\n", size);
		printf("|\t\tnew->ptr: [%p]\n", new->ptr);
		printf("|\t\tnew->size: [%u]\n", new->size);
		printf("|\t\tnew->used: [%d]\n", new->used);
	}
	return new;
}

mBlock* getSuficientMemoryBlock(const unsigned int bytes) {
	if (!last)
		return NULL;
	mBlock* block = last;
	mBlock* selected = NULL;
	// first-fit
	if (POLICY == FIRST_FIT) {
		while (block) {
			if (block->size > +bytes && block->used < 1)
				return block;
			block = block->prev;
		}
	}
	// best-fit
	else if (POLICY == BEST_FIT) {
		long int minDiff = LONG_MAX;
		if (verbose && show_bestfit_search)
			printf("|\t@best-fit - search for block size [%u]\n", bytes);
		while (block) {
			long int diff = (long int) block->size - (long int) bytes; // if not casted, it will fail if (bytes > block->size) for all blocks
			if (verbose && show_bestfit_search)
				printf(
						"|\t@best-fit - block: [%p]\tblock->size: [%u]\tdiff: %li\n",
						block, block->size, diff);
			if (diff > 0 && block->used < 1) {
				if (diff < minDiff) {
					minDiff = diff;
					selected = block;
				}
			}
			block = block->prev;
		}
	}
	if (verbose && show_bestfit_search)
		printf("|\t@best-fit: block selected: [%p]\n", selected);
	return selected;
}

mBlock* getMemoryBlockFromPointer(void* ptr) {
	mBlock* block = last;
	while (block) {
		if (block->ptr == ptr)
			return block;
		block = block->prev;
	}
	return NULL;
}

int release(void* ptr) {
	if (ptr < heap_start || ptr > sbrk(0)) {
		perror("|\t@release - invalid pointer");
		return 1;
	}
	if (verbose)
		printf(">release():\n");
	int result = 1;
	mBlock* block = last;
	while (block) {
		if (block->ptr == ptr) {
			block->used = 0;
			//join with both adyacent blocks (if they are empty)
			if (block->next)
				join(block); // join checks if block->next is empty
			if (block->prev && !block->prev->used)
				join(block->prev); // join DOES NOT check if block->prev is empty
			printf("|\tblock found and released\n");
			result = 0;
			break;
		}
		block = block->prev;
	}
	if (verbose)
		printf(">release() returned [%d]\n", result);
	return result;
}

int align(const unsigned int bytes) {
	return (((WORD_SIZE - 1) & bytes) ?
			((bytes + WORD_SIZE) & ~(WORD_SIZE - 1)) : bytes);
}

int join(mBlock* block) {
	if (!block) {
		if (verbose)
			printf("|\t@join: block NULL\n");
		return 1;
	}
	if (!block->next) {
		if (verbose)
			printf("|\t@join: block->next NULL\n");
		return 1;
	}
	if (block->next->used) {
		if (verbose)
			printf("|\t@join: block->next is USED\n");
		return 1;
	}
	block->size = block->size + block->next->size + sizeof(mBlock); // sizeof(block->next)
	//block->used = unchanged
	//block->ptr  = unchanged
	//block->prev = unchanged
	block->next = block->next->next;
	if (block->next->next)
		block->next->next->prev = block;
	if (verbose)
		printf("|\t@join [%p] with [%p]\n", (void *) block,
				(void *) block->next);
	return 0;
}

int copy(mBlock* dest, mBlock* source, int bytes) {
	if (!dest || !source)
		return 1;
	char* D = dest->ptr;
	char* S = source->ptr;
	for (int d = 0; d < bytes; d++)
		D[d] = S[d];
	return 0;
}

int defragmentate() {
	printf(">defragmentate() starting...\n");
	int done = 0, loop = 0, iteration = 0, count = 0;
	;
	while (!done) {
		mBlock* block = last;
		done = 1;
		while (block) {
			mBlock* next = block->next;
			// if this block is free, and the next one is used...
			if (!block->used && next && next->used) {
				// skip 'next' on the list
				block->next = next->next;
				if (next->next)
					next->next->prev = block;
				// copy from next to block
				if (next == last)
					last = block;
				block->used = 1;
				block->size = next->size;
				copy(block, next, next->size);
				// just completed op -> assuming not done
				done = 0;
				count++;
			}
			iteration++;
			block = block->prev;
		}
		loop++;
	}
	printf("|\tperformed [%d] operations in [%d] iterations in [%d] loops\n",
			count, iteration, loop);
	printf(">defragmentate() finished\n");
	return 0;
}

void print(const char* name, mBlock* block) {
	if (!block) {
		printf("> attempted to print NULL block [%s]", name);
		return;
	}
	printf("|\t%-20s%s\n", "printing block @", name);
	printf("|\t%-20s%p\n", "META address:", block);
	printf("|\t%-20s%u\n", "size:", block->size);
	printf("|\t%-20s%u\n", "used:", block->used);
	printf("|\t%-20s%p\n", "address:", block->ptr);
	printf("|\t%-20s%p\n", "address (prev):", block->prev);
	printf("|\t%-20s%p\n", "address (next):", block->next);
}

void print_data(void* ptr) {
	printf(">%-25s[%p]\n", "printing data from block: ", ptr);
	mBlock* block = getMemoryBlockFromPointer(ptr);
	if (!block) {
		printf(">block does not exists\n\n");
		return;
	}
	printf("|\t%-18s[%u]\n", "block->size ", block->size);
	char* data = block->ptr;
	for (int d = 0; d < block->size; d++) {
		if (d == 0)
			printf("|\tdata (int):  [");
		printf("%d", data[d]);
		if (d + 1 != block->size)
			printf(",");
		else
			printf("]\n");
	}
	for (int d = 0; d < block->size; d++) {
		if (d == 0)
			printf("|\tdata (char): [");
		printf("%c", data[d]);// PREGUNTAR: porque no se puede escribir mas en esta linea???
		if (d + 1 != block->size)
			printf(",");
		else
			printf("]\n");
	}
	printf(">finished printing data from block\n\n");
}

void print_all_blocks() {
	printf(">print_all_blocks()\n");
	mBlock* block = last;
	int id = 0;
	char name[20];
	while (block) {
		sprintf(name, "block id: [%d]", id++);
		print(name, block);
		printf("|\n");
		block = block->prev;
	}
	printf("\n");
}

void print_all_blocks_state(char* title) {
	printf("%s\n", title);
	mBlock* block = last;
	while (block) {
		printf("|\tblock: [%p]\tsize: [%d]\tused: [%d]\n", block->ptr,
				block->size, block->used);
		block = block->prev;
	}
	printf("\n");
}