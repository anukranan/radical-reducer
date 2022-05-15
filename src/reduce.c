/* SPDX-License-Identifier: MIT */

/*
 * Copyright (c) 2022 Roland Gehl
 *
 * reduce.c - Functions for simplification and approximation.
 */

#include "rr.h"
#include <math.h>

/* Return an accurate approximation of a root using Newton's method. */
double
root(int degree, int radicand)
{
        /* Is there a way to find a more accurate first guess? */
        double x_past = rand() % radicand; /* First guess */
        double x_current;

        /* Need a better way to find a good amount of iterations. This is fine
           for now though. */
        int iter = (int)(ceil(20 * log2(degree)));
        for (int i = 0; i < iter; ++i) {
                x_current = ((degree - 1) * x_past + (double)radicand
                        / pow(x_past, degree - 1)) / (double)degree;
                x_past = x_current;
        }

        return x_current;
}

/* Return a reduced expression for the provided value. */
struct reduced_exp
reduce_exp(int degree, int radicand)
{
        struct reduced_exp exp;
        exp.place = 1;
        exp.ans = (double)radicand;

        double root_val = root(degree, radicand);
        double results[(int)(floor(exp.ans) + 2)];

        /* Floating points are hard sometimes, hence int q, for now. */
        for (int i = 1; i < (floor(root_val) + 1); ++i) {
                results[i] = pow((root_val / i), degree);
                int q = (int)(fmod(results[i], 1) * 100);
                if (q == 0 || q == 99 || q == 100) {
                        exp.place = i;
                        exp.ans = results[i];
                }
        }

        return exp;
}
