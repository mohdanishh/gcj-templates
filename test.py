import random

n = random.randint(5000, 5000)
print n
for i in xrange(n):
   print random.randint(1, 1000000), random.randint(1, 1000000)
