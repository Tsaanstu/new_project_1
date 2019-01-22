#ifndef PROJECT_INCLUDE_LABIRINT_HPP_
#define PROJECT_INCLUDE_LABIRINT_HPP_

#include <iostream>

#include "definitions.hpp"

typedef struct position {
	int i;
	int j;
	struct position *visited;
} Position;

class Labirint {
private:
	size_t size;
	int **lab;
public:
	size_t get_size() const;
	Labirint() = default;
	Labirint(const Labirint& l);
	Labirint(size_t size);
	int getme(int i, int j) const;
	void WorkOutputLab();
	void OutputLab();
	int Proverka(struct position *p1);
	struct position *NumStep(struct position *p1);
	void Work();
	void add_new_way();
};
#endif  //  PROJECT_INCLUDE_LABIRINT_HPP_
