#include <stdio.h>

int main () {
	float n = 0.0f;
	int i = 0;
	for (; i < 10; ++i) {
		n += 0.1f; // 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1
	}
	printf("%.9f", n);
    return 0;
}
