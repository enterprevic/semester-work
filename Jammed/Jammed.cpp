// Jammed.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>

#include "combination.h"

using namespace std;

struct Combination {
	
	//массив char для хранения комбинации
	char data[2][4];

	//считываем из stdin комбинацию символов
	void read(istream& inputData) {
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 4; ++j) {
				inputData >> data[i][j];
			}
		}
	}

	//ищем '#', проверяем возможен ли сдвиг в di, dj и получаем новую комбинацию 
	Combination shift(int di, int dj) const {
		Combination next = *this;
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (next.data[i][j] == '#') {
					int ni = i + di;
					int nj = j + dj;
					if (0 <= ni && ni < 2 && 0 <= nj && nj < 4) {
						//если не выходим за края, то обменяем местами '#' и текущий символ и получим новую комбинацию
						swap(next.data[i][j], next.data[ni][nj]);
					}
					return next;
				}
			}
		}
	}
};

//сравниватель двух комбинаций, если равны то возвр. 0, если l < r то возвр отрицат. значение, если l > r возвр. положительное значение 
int compare(const Combination& l, const Combination& r) {
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (l.data[i][j] != r.data[i][j]) {
				return l.data[i][j] - r.data[i][j];
			}
		}
	}
	return 0;
}

//оператор сравнения на <
bool operator <(const Combination& l, const Combination& r) {
	return compare(l, r) < 0;
}

//оператор сравнения на ==
bool operator ==(const Combination& l, const Combination& r) {
	return compare(l, r) == 0;
}

//реализация решения
int solution(Combination& start, Combination& finish) {
	//словарь для хранения соответствия комбинации->количеству шагов за которое в эту комбинацию пришли от начальной 
	map<Combination, int> steps;

	//очередь для хранения перебираемых комбинаций
	queue<Combination> q;

	steps[start] = 0;
	q.push(start);

	//пока очередь комбинаций не пуста 
	while (!q.empty()) {
		//берем текущую комбинацию из очереди
		Combination cur = q.front();
		q.pop();

		//и проверяем, если она финальная то возвращаем количество шагов до нее и завершаем программу 
		if (cur == finish) {
			return steps[cur];
		}

		//генерируем новые комбинации сдвигая '#' во все возможные положения из текущего
		for (int di = -1; di <= 1; ++di) {
			for (int dj = -1; dj <= 1; ++dj) {
				if (di * di + dj * dj == 1) {
					Combination next = cur.shift(di, dj);
					if (steps.count(next) == 0) {
						steps[next] = steps[cur] + 1;
						q.push(next);
					}
				}
			}
		}
	}

	//очередь комбинаций опустела, но нужная не нашлась, выводим -1 по условию задачи
	return -1;
}

int main(int argc, char* argv[]) {

	//если параметров не 3, то прекращаем работу
	if (argc != 3) {
		cout << "not enough arguments";
		return -1;
	}

	ifstream finput(argv[1]);
	ofstream fout(argv[2]);
	
	//считываем начальную кобинацию
	Combination start;
	start.read(finput);

	//считываем финальную комбинацию
	Combination finish;
	finish.read(finput);

	//запускаем поиск решения от стартовой и финишной комбинации
	int res = solution(start, finish);

	fout << res;
	return 0;
}
