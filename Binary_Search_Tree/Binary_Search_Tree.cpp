#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <time.h>
#include "BST.h"

// Does not work: Remove, ToString, main

int main()
{
	BST::BinSerTree<int>* bst = new BST::BinSerTree<int>();

	bst->Push(10);
	bst->Push(2);
	bst->Push(15);
	bst->Push(42);
	bst->Push(8);
	bst->Push(17);
	bst->Push(10);
	bst->Push(38);
	bst->Push(0);
	bst->Push(15);

	std::cout << bst->ToString(true);

	//bst->Pop(bst->find(2));

	std::cout << bst->ToString(true);

	bst->Erase();

	std::cout << bst->ToString(true);

	delete bst;

	return 0;
}

// --------------------------------------------------------------------------------------------- //

struct some_object {
	int field_1;
	char field_2;
};

std::string some_objects_str(some_object* so) {
	std::string text = "(" + std::to_string(so->field_1) + ", " + so->field_2 + ")";
	return text;
}

bool some_objects_cmp1(some_object* so1, some_object* so2) {
	return so1->field_1 == so2->field_1;
}

bool some_objects_cmp2(some_object* so1, some_object* so2) {
	return so1->field_1 >= so2->field_1;
}

int main2() {
	srand(time(NULL));
	const int MAX_ORDER = 7;
	BST::BinSerTree<some_object*>* bst = new BST::BinSerTree<some_object*>();

	for (int i = 1; i <= MAX_ORDER; i++) {
		const int n = pow(10, i);

		std::cout << "Starting the element pushing phase" << std::endl;
		clock_t t1 = clock();
		for (int j = 0; j < n; j++) {
			some_object* so = new some_object();
			so->field_1 = rand() % 100;
			so->field_2 = 'A' + rand() % 26;
			bst->Push(so);
		}
		clock_t t2 = clock();
		std::cout << "Element pushing phase done" << std::endl;

		double time = double(t2 - t1) / CLOCKS_PER_SEC;
		std::cout << bst->ToString(true, some_objects_str);
		std::cout << "Pushing time: " << time << "s" << std::endl << std::endl;

		const int m = pow(10, 4);
		int hints = 0;

		std::cout << "Starting the element finding phase" << std::endl;
		t1 = clock();
		for (int j = 0; j < n; j++) {
			some_object* so = new some_object();
			so->field_1 = rand() % 100;
			so->field_2 = 'A' + rand() % 26;

			if (bst->Find(so)) {
				hints++;
			}

			delete so;
		}
		t2 = clock();
		std::cout << "Element finding phase done" << std::endl;

		time = double(t2 - t1) / CLOCKS_PER_SEC;
		std::cout << "Finding time: " << time << "s" << std::endl;
		std::cout << "Hints: " << hints << std::endl << std::endl;

		bst->Erase();
	}

	delete bst;
	return 0;
}