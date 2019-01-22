#include <cstdlib>
#include <ctime>
#include <random>

#include "labirint.hpp"

Labirint::Labirint(const Labirint& l) {
	this->size = l.get_size();
	this->lab = new int*[this->size];
	for (size_t i = 0; i < this->size; i++) {
		this->lab[i] = new int[this->size];
	}
	for (size_t i = 0; i < this->size; i++) {
		for (size_t j = 0; j < this->size; j++) {
			this->lab[i][j] = l.getme(i, j);
		}
	}
}

size_t Labirint::get_size() const{
	return size;
}

int Labirint::getme(int i, int j) const {
	return lab[i][j];
}

int Labirint::Proverka(Position *p1) {
	int a = 0, b = 0, c = 0, d = 0;
	int N = static_cast<int> (size);
	if (p1->j != N - 2) {
		if (lab[p1->i][p1->j + 2] == -1) {
			a = 1;
		}
	}
	if (p1->j != 1) {
		if (lab[p1->i][p1->j - 2] == -1) {
			b = 1;
		}
	}
	if (p1->i != N - 2) {
		if (lab[p1->i + 2][p1->j] == -1) {
			c = 1;
		}
	}
	if (p1->i != 1) {
		if (lab[p1->i - 2][p1->j] == -1) {
			d = 1;
		}
	}
	if (p1->j == N - 2) {
		a = 1;
	}
	if (p1->j == 1) {
		b = 1;
	}
	if (p1->i == N - 2) {
		c = 1;
	}
	if (p1->i == 1) {
		d = 1;
	}
	return (a + b + c + d);
}

Position *Labirint::NumStep(Position *p1) {
	int c, x = 4;
	int N = static_cast<int> (size);
	Position *p2 = new Position;
	c = rand() % 4;
	while (x>0) {
		switch (c) {
		case 0:
			if (p1->i != 1) {
				if (lab[p1->i - 2][p1->j] != -1) {
					lab[p1->i - 1][p1->j] = 1;
					p2->i = p1->i - 2;
					p2->j = p1->j;
					p2->visited = p1;
					return p2;
				}
			}
			break;
		case 1:
			if (p1->j != N - 2) {
				if (lab[p1->i][p1->j + 2] != -1) {
					lab[p1->i][p1->j + 1] = 1;
					p2->j = p1->j + 2;
					p2->i = p1->i;
					p2->visited = p1;
					return p2;
				}
			}
			break;
		case 2:
			if (p1->i != N - 2) {
				if (lab[p1->i + 2][p1->j] != -1) {
					lab[p1->i + 1][p1->j] = 1;
					p2->i = p1->i + 2;
					p2->j = p1->j;
					p2->visited = p1;
					return p2;
				}
			}
			break;
		case 3:
			if (p1->j != 1) {
				if (lab[p1->i][p1->j - 2] != -1) {
					lab[p1->i][p1->j - 1] = 1;
					p2->j = p1->j - 2;
					p2->i = p1->i;
					p2->visited = p1;
					return p2;
				}
			}
			break;
		}
		x--;
		c = (c + 1) % 4;
	}
	return p2;
}

Labirint::Labirint(size_t n) {
	srand(time(NULL));
	size = n;
	lab = new int*[size];
	for (size_t i = 0; i < size; i++) {
		lab[i] = new int[size];
	}

	for (size_t i = 0; i < size; i += 2) {
		for (size_t j = 0; j < size; j++) {
			lab[i][j] = 0;
		}
	}

	for (size_t i = 1; i < size - 1; i += 2) {
		for (size_t j = 0; j < size; j += 2) {
			lab[i][j] = 0;
		}
		for (size_t j = 1; j < size - 1; j += 2) {
			lab[i][j] = 1;
		}
	}
	Work();
	lab[1][1] = 2;
	lab[n-2][n-2] = 2;
	add_new_way();
}

void Labirint::add_new_way() {
	int p_num = 2 + rand() % ((size - 2) / 6);
	for (size_t i = 2; i < size - 2; i++) {
		for (int j = 0; j < p_num; j++) {
			size_t temp = 1 + rand() % (size - 2);
			if (lab[i + 1][temp] != 0 && lab[i - 1][temp] != 0) {
				lab[i][temp] = 1;
			}
		}
	}
}

void Labirint::Work() {
	Position *p1 = new Position;
	p1->i = 1;
	p1->j = 1;
	p1->visited = NULL;
	do {
		while (Proverka(p1) != 4) {
			lab[p1->i][p1->j] = -1 * lab[p1->i][p1->j];
			p1 = NumStep(p1);
		}
		lab[p1->i][p1->j] = -1 * lab[p1->i][p1->j];
		while (Proverka(p1) == 4) {
			p1 = p1->visited;
			if (p1->i == 1 && p1->j == 1)
				break;
		}
	} while (p1->visited != NULL);
}

void Labirint::OutputLab() {
	std::cout << std::endl;
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			if ((i == 1 && j == 0) || (i == size - 2 && j == size - 1)) {
				std::cout << "<";
			}
			else if (abs(lab[i][j]) == 1) {
				std::cout << " ";
			}
			else {
				std::cout << "*";
			}
		}
		std::cout << std::endl;
	}
}

void Labirint::WorkOutputLab() {
	std::cout << std::endl;
	for (size_t i = 0; i < size; i++) {
		for (size_t j = 0; j < size; j++) {
			if (lab[i][j] < 0) {
				std::cout << " " << lab[i][j];
			}
			else {
				std::cout << "  " << lab[i][j];
			}
		}
		std::cout << std::endl;
	}
}
