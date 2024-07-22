#include "window.h"

using namespace std;

int main() {
	Xwindow x;
	int c = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			x.fillRectangle(i * 50, j * 50, 50, 50, c);
			c ^= 1;
		}
		c ^= 1;
	}
	cin >> c;
}
