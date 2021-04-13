#! /usr/bin/env python3

import sys
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

N = 256
vals = np.ones((N, 4))
vals[:, 0] = np.linspace(96/256, 80/256, N)
vals[:, 1] = np.linspace(48/256, 80/256, N)
vals[:, 2] = np.linspace(48/256, 160/256, N)
newcmp = ListedColormap(vals)

def main():
    matrix = []
    data = []
    i = 0
    try:
        crude_file = open(sys.argv[1], "r")
    except:
        print("Found an error, aborting...")
        exit(0)
    for line in crude_file:
        matrix.append(line)
    crude_file.close()
    file_counter = -1
    for line in matrix:
        if (len(line.strip().split(",")) == 1):
            data.append([])
            counter = 0
            file_counter += 1
            num_str = ("00000000"+str(file_counter))[-5:]
            if (file_counter != 0):
                plt.imsave(sys.argv[1][:-4]+num_str+".png",
                    data[-2], cmap=newcmp, vmin=0.0)
        elif (counter % 3 == 2):
            data[-1].append([])
            counter += 1
            for element in line.strip().split(","):
                data[-1][-1].append(float(element))
        else:
            counter += 1

main()

