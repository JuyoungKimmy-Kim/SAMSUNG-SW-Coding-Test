#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum { RIGHT, LEFT, DOWN, UP };
const int APPLE = 1;
int dy[] = { 0,0,1,-1 };
int dx[] = { 1,-1,0,0 };

int N;
int sec = 0;
int curDir = RIGHT;

vector<vector<int>> board;
deque <pair<int, int>> snake;

void changeDir(char dir) {
	if (dir == 'L') {
		if (curDir == 0) curDir = 3;
		else if (curDir == 1) curDir = 2;
		else if (curDir == 2) curDir = 0;
		else if (curDir == 3) curDir = 1;
	}
	else if (dir == 'D') {
		if (curDir == 0) curDir = 2;
		else if (curDir == 1) curDir = 3;
		else if (curDir == 2) curDir = 1;
		else if (curDir == 3) curDir = 0;
	}
}
bool canMove() {
	pair <int, int> cur = snake.front();
	int ny = cur.first + dy[curDir];
	int nx = cur.second + dx[curDir];

	if (ny<1 || nx<1 || ny>N || nx>N) return false;
	if (board[ny][nx] == -1) return false;


	snake.push_front(make_pair(ny, nx));
	if (board[ny][nx] != APPLE) {
		int by = snake.back().first;
		int bx = snake.back().second;
		board[by][bx] = 0;
		snake.pop_back();
	}

	board[ny][nx] = -1;
	return true;
}

int main() {
	snake.push_back(make_pair(1, 1));

	int K, L;
	cin >> N >> K;
	board = vector<vector<int>>(N + 1, vector<int>(N + 1));
	board[1][1] = -1;

	for (int i = 0; i < K; i++) {
		int y, x;
		cin >> y >> x;
		board[y][x] = APPLE;
	}

	cin >> L;
	for (int i = 0; i < L; i++) {
		int x;
		char dir;
		cin >> x >> dir;
		while (sec != x) {
			if (!canMove()) {
				cout << sec + 1 << endl;
				return 0;
			}
			sec++;
		}
		changeDir(dir);
	}
	while (1) {
		if (!canMove()) {
			cout << sec + 1 << endl;
			return 0;
		}
		sec++;
	}
	return 0;
}
