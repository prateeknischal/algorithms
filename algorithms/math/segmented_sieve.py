prime = [2]
prime_len = 0
seg_size = 10000

def primary_sieve(limit):
	p = [0] * (limit + 1)
	p[1] = 1
	sieve_lim = int(pow(1.0 * limit, 0.5)) + 1
	for i in range(3, sieve_lim, 2):
		if p[i] == 0:
			for j in range(i*i, limit , 2*i):
				p[j] = 1

	for i in range(3, limit + 1, 2):
		if p[i] == 0:
			prime.append(i)

def seg_sieve(offset, end, primes):
	p = [0] * (1+seg_size)

	idx = 0
	while prime[idx] * prime[idx] <= offset + seg_size:
		cnt = 0
		if offset % prime[idx] == 0:
			cnt = offset // prime[idx]
		else:
			cnt = (offset // prime[idx]) + 1

		while cnt * prime[idx] <= offset + seg_size:
			p[cnt * prime[idx] - offset] = 1
			cnt += 1
		idx += 1

	for i in range(0, min(offset + seg_size, end) - offset):
		if p[i] == 0:
			primes.append(i + offset)

def prime_sieve(end, start):
	start = max(start, 2)
	end = max(end, 1)
	primes = []
	base_prime_limit = int(pow(end*1.0, 0.5)) + 1
	primary_sieve(100000)
	for i in prime:
		if i >= start and i<=end and i <= 100000:
			primes.append(i)

	prime_count = max(100000, start)
	while (prime_count + seg_size <= end):
		seg_sieve(prime_count, end, primes)
		prime_count += seg_size
	
	seg_sieve(prime_count, end, primes);
	return primes;

print prime_sieve(10**9 + 10**7, 10**9)
