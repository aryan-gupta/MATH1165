
import os

for i in range(28):
	print("Test case: ", i)
	os.system(f"echo {i} | ./a.out | grep \"Enter\"")