int search(int n, function<bool(int)> lt) {
	int i = 0, k = n;
	while (i < k) {
		int m = i + (k - i) / 2;
		if (lt(m)) { // max(lt(m)) s.t. lt(m) is true
			i = m + 1;
		} else {
			k = m;
		}
	}
	return i; // returns where needle SHOULD be!
}