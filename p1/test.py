from subprocess import Popen, PIPE, STDOUT
import math

for a in range(-100, 100):
	for b in range(-100, 100):
		print(a, " ", b)
		if a is 0 and b is 0: continue
		p = Popen(['./a.out'], stdout=PIPE, stdin=PIPE)
		stdout_data = p.communicate(input=f'{a} {b}'.encode())[0].decode()
		gcd, _, x, _, y = stdout_data.split()
		gcd = int(gcd)
		x = int(x)
		y = int(y)
		# print(gcd, " = ", a, "*", x, " + ", b, "*", y, "  ")
		if math.gcd(a, b) != gcd:
			print("gcd failed")
			print(a, " ", b)
		if x * a + b * y != gcd:
			print("lc failed")
			print(a, " ", b)