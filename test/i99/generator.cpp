#include <random>
#include <cstdio>

using i32 = int;

std::random_device seed;
std::mt19937 rng(seed());

inline void genlongint(i32 len) {
	if (rng() % 2) putchar('-');
	for (; len; --len) putchar('0' + rng() % 10);
}

i32 main() {
	i32 lena = rng() % 3000;
	i32 lenb = rng() % 3000;
	// const i32 op = "+-*/%"[rng() % 5];
	if (lena < lenb) std::swap(lena, lenb);
	if (lena == lenb) ++lena;
	genlongint(lena); puts("");
	// printf("\n%c\n", op);
	genlongint(lenb);

	return 0;
}
