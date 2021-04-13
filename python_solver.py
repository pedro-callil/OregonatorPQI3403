#! /usr/bin/python3

import sys
from scipy.integrate import solve_ivp

class data_struct ():
    def __init__(self, k1, k2, k3, k4, kc, f, A, B):
        self.k1 = k1
        self.k2 = k2
        self.k3 = k3
        self.k4 = k4
        self.kc = kc
        self.f = f
        self.A = A
        self.B = B

def differential (t, y, data):
    X = y[0]
    Y = y[1]
    Z = y[2]
    k1 = data.k1
    k2 = data.k2
    k3 = data.k3
    k4 = data.k4
    kc = data.kc
    f = data.f
    A = data.A
    B = data.B
    dXdt = k1*A*Y - k2*X*Y + k3*A*X - 2*k4*X*X
    dYdt = -k1*A*Y - k2*X*Y + 0.5*f*kc*B*Z
    dZdt = 2*k3*A*X - kc*B*Z
    return [dXdt, dYdt, dZdt]

def get_cmd_line_args (argv):
    try:
        data = data_struct(float(argv[1]), float(argv[2]), float(argv[3]),
            float(argv[4]), float(argv[5]), float(argv[6]),
            float(argv[7]), float(argv[8]))
    except:
        data = data_struct(1.28, 2.4e6, 33.6, 2400, 1, 1, 0.06, 0.02)
    return data

def main ():
    argv = sys.argv
    data = get_cmd_line_args(argv)
    solution = solve_ivp( differential, (0,1000),
            [3e-6, 3e-6, 300e-6], method='BDF', args=[data],
            rtol=1e-6, atol=1e-12)
    t = solution.t
    y = solution.y
    for i in range(len(t)):
        print(str(t[i]) + "," + str(y[0][i]) + "," +
                str(y[1][i]) + "," + str(y[2][i]))

main()

