#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <time.h>
#include <random>
#include "BST.h"

int main()
{
	const int MAX_ORDER = pow(10, 2);

	static std::random_device rd;
	static std::default_random_engine dre(rd());
	std::uniform_int_distribution<int> rnd(0, MAX_ORDER);

	BST::BinSerTree<int>* bst = new BST::BinSerTree<int>();

	for (int i = 0; i < MAX_ORDER; i++) {
		int r = rnd(dre);
		bst->Push(r);
	}
	std::cout << bst->ToString(3);

	for (int i = 0; i < MAX_ORDER; i++) {
		int r = rnd(dre);
		if (bst->Pop(bst->Find(r))) std::cout << "Node: " << r << " found and removed" << std::endl;
	}
	std::cout << bst->ToString(3);

	bst->Erase();
	std::cout << bst->ToString();

	delete bst;
	return 0;
}

// --------------------------------------------------------------------------------------------- //

struct some_object {
	int field_1;
	char field_2;
};

std::string some_objects_str(some_object* so) {
	return "(" + std::to_string(so->field_1) + ", " + so->field_2 + ")";
}

bool some_objects_cmp(some_object* so1, some_object* so2) {
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