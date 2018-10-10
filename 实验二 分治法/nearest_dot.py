import math
import random
import numpy as np
import matplotlib.pyplot as plt

a = [(100 * random.random(), 100 * random.random()) for i in range(0, 10)]
a.sort()
plt.close()
dots_x = np.array([a_x[0] for a_x in a])
dots_y = np.array([a_y[1] for a_y in a])
par = []
mi = float("inf")
fig = plt.figure()
ax1 = fig.add_subplot(111)
ax1.set_title('nearest doc')
plt.xlabel('X')
plt.ylabel('Y')
plt.ion()
ax1.scatter(dots_x, dots_y, c='r', marker='o')
plt.pause(3)
color = ('black', 'peachpuff', 'yellow', 'steelblue', 'lime', 'lightcoral', 'gold', 'cyan')


def eudis(x, y):
    global par
    h = math.sqrt((x[0] - y[0]) ** 2 + (x[1] - y[1]) ** 2)
    if h < mi:
        par = []
        par.append(x)
        par.append(y)
    return h


def combine(l1, l2, alpha):
    x = float("inf")
    mini = l1[-1][0] - alpha
    maxi = l1[-1][0] + alpha
    for i in l1:
        if (mini < i[0] < maxi):
            for j in l2:
                if ((mini < j[0] < maxi) and abs(i[1] - j[1]) < alpha):
                    x = min(x, eudis(i, j))
    return x


def divide(a, n):
    global mi
    if (len(a) == 2):
        return eudis(a[0], a[1])
    if (len(a) < 2):
        return float("inf")
    else:
        i = int(len(a) / 2)
        left = a[0:i]
        right = a[i:]
        dots_x = np.array([index[0] for index in left])
        dots_y = np.array([index[1] for index in left])
        # plt.cla()
        ax1.scatter(dots_x, dots_y, c=color[n], marker='o')
        plt.plot([a[i][0]-1, a[i][0]-1], [0, 100], c=color[n])
        n += 1
        plt.pause(0.1)
        s1 = divide(left, n)
        s2 = divide(right, n)
        s3 = combine(left, right, mi)
        s = min(s1, s2, s3)
        mi = min(s, mi)
        return mi


result = divide(a, 0)
print(result)


# 暴力解法
min_d = 1000
for i in range(len(a)):
    for j in range(len(a)):
        if j+i+1 < len(a):
            j = j+i+1
            min_d = min(eudis(a[i], a[j]), min_d)
print(min_d)

