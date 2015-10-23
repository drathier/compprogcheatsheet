vector<bool> sieve(long limit) {
	vector<bool> sieve(limit+1, true);
	sieve[0] = sieve[1] = false;
	sqlim = sqrt(limit) + 1;
	for (long i = 2; i <= sqlim; ++i) {
		if (sieve[i]) {
			for (long j = i * i; j <= limit; j += i) {
				sieve[j] = false;
			}
		}
	}
	return sieve;
}
