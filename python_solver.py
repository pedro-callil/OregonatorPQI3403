#! /usr/bin/python3

import sys
import argparse
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

def get_cmd_line_args (args):
    data = data_struct(1.28, 2.4e6, 33.6, 2400, 1, 1, 0.06, 0.02)
    if args.a is not None:
        data.A = args.a
    if args.b is not None:
        data.B = args.b
    if args.f is not None:
        data.f = args.f
    if args.i is not None:
        data.k1 = args.i
    if args.j is not None:
        data.k2 = args.j
    if args.k is not None:
        data.k3 = args.k
    if args.l is not None:
        data.k4 = args.l
    if args.m is not None:
        data.kc = args.m
    return data

def main (args):
    data = get_cmd_line_args(args)
    solution = solve_ivp( differential, (0,1000),
            [3e-6, 3e-6, 300e-6], method='BDF', args=[data],
            rtol=1e-6, atol=1e-12)
    t = solution.t
    y = solution.y
    print('t,x,y,z')
    for i in range(len(t)):
        print('{0},{1},{2},{3}'.format(t[i],y[0][i],y[1][i],y[2][i]))

if __name__=="__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-a", "--a", type=float, help="<initial concentration of A>")
    parser.add_argument("-b", "--b", type=float, help="<initial concentration of B>")
    parser.add_argument("-f", "--f", type=float, help="<f>")
    parser.add_argument("-i", "--i", type=float, help="<k1>")
    parser.add_argument("-j", "--j", type=float, help="<k2>")
    parser.add_argument("-k", "--k", type=float, help="<k3>")
    parser.add_argument("-l", "--l", type=float, help="<k4>")
    parser.add_argument("-m", "--m", type=float, help="<kc>")
    args = parser.parse_args()
    main(args)

