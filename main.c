#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "list.h"
#include "sort.h"

Sort *sort_sel[] = {
    &sg_sort,
    &dbly_sort,
};
int main(int argc, char *argv[]) {
	assert((argc == 2) && "Usage: ./sorting [OPTION] (0: singular, 1: doubly)");
	assert((atoi(argv[1]) < 2) && "Invalid OPTION (0: singular, 1: doubly)");
	Sort *imple_sort = sort_sel[atoi(argv[1])];
	int correct = 0;
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		int testcase[10] = {0};
		for (int j = 0; j < 10; j++)
			testcase[j] = rand() % 50;

		list *head = NULL; 

		for (int j = 9; j >= 0; j--)
			imple_sort->push(&head, testcase[j]);
		printf("Testcase %d: ", i+1);
		imple_sort->print(head, false);
		printf(" --> ");
		if (imple_sort->test(head, testcase, 10))
			correct++;
		imple_sort->list_free(&head);
		printf("\n");
	}
	printf("%d/100 passed.\n", correct);
	return 0;
}

#if 0
int main() {
	int correct = 0;
	srand(time(NULL));
	for (int i = 0; i < 100; i++) {
		int testcase[10] = {0};
		for (int j = 0; j < 10; j++)
			testcase[j] = rand() % 50;

		list *head = NULL;
		for (int j = 9; j >= 0; j--)
			push(&head, testcase[j]);
		printf("Testcase %d: ", i+1);
		print(head, false);
		printf(" --> ");
		if (test(head, testcase, 10))
			correct++;
		//list_free(&head);
		printf("\n");
	}
	printf("%d/100 passed.\n", correct);
	return 0;
}
#endif
