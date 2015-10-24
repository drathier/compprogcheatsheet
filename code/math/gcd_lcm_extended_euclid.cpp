int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}

int lcm(int a, int b) {
	return abs(a*b) / gcd(a, b);
}

using i3tuple = tuple<int, int, int>;
using i2tuple = tuple<int, int>;

i3tuple extendedEuclid(int a, int b) {
	if (a == 0) return i3tuple(b, 0, 1);
	Tuple t = extendedEuclid(b % a, a);
	int _gcd = get<0>(t), x = get<1>(t), y = get<2>(t);
	return i3tuple(_gcd, x - (b/a) * y, y);
}

i2tuple diophanticEquation(int a, int b, int c) {
	if (c%gcd(a, b) != 0) return i2tuple(-1, -1); // Unsolvable
	i3tuple t = extendedEuclid(a, b);
	int _gcd = get<0>(t), x = get<1>(t), y = get<1>(t);
	y *= c; x *= c;
	return i2tuple(x, y);
}
