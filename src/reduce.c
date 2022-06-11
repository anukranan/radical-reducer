/*
 * Copyright (c) 2022 Roland Gehl
 *
 * Licensed under the MIT License.
 * See LICENSE for more details.
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define _POSIX_C_SOURCE 200809L

struct reduced_exp {
        int place; /* Multiplier */
        double ans; /* Radicand */
};

static double root(int degree, int radicand);
static struct reduced_exp reduce_exp(int degree, int radicand);

/* Return an accurate approximation of a root using Newton's method. */
static double
root(int degree, int radicand)
{
        /* Is there a way to find a more accurate first guess? */
        double x_past = rand() % radicand; /* First guess */
        double x_current = 0;

        /* Need a better way to find a good amount of iterations. This is fine
           for now though. */
        int i = 0;
        int iter = (int)(ceil(20 * log2(degree)));
        for (; i < iter; i++) {
                x_current = ((degree - 1) * x_past + (double)radicand
                        / pow(x_past, degree - 1)) / (double)degree;
                x_past = x_current;
        }

        return x_current;
}

/* Return a reduced expression for the provided value. */
static struct reduced_exp
reduce_exp(int degree, int radicand)
{
        struct reduced_exp exp;
        exp.place = 1;
        exp.ans = (double)radicand;

        double root_val = root(degree, radicand);
        double results[(int)(floor(exp.ans) + 2)];

        /* Floating points are hard sometimes, hence int q, for now. */
        int i = 1;
        for (; i < (floor(root_val) + 1); i++) {
                results[i] = pow((root_val / i), degree);
                int q = (int)(fmod(results[i], 1) * 100);
                if (q == 0 || q == 99 || q == 100) {
                        exp.place = i;
                        exp.ans = results[i];
                }
        }

        return exp;
}

int
main(void)
{
        int degree, radicand, imaginary = 0;

        /* scanf() is prone to error, it should be replaced. */
        printf("Degree: ");
        scanf("%d", &degree);
        printf("Radicand: ");
        scanf("%d", &radicand);
        printf("\n");

        /* Account for 'lateral' numbers. */
        if (radicand < 0) {
                radicand *= -1;
                imaginary = 1;
        }

        struct reduced_exp exp = reduce_exp(degree, radicand);

        /*
         * Replace this with a more modular (and better) way of display.
         * In addition, decimal points should be truncated.
         */
        switch (imaginary) {
        case 0:
                if (exp.place <= 1)
                        printf("√%f\n", exp.ans);
                else
                        printf("%d√%f\n", exp.place, exp.ans);
                break;
        case 1:
                if (exp.place <= 1)
                        printf("i√%f\n", exp.ans);
                else
                        printf("%di√%f\n", exp.place, exp.ans);
                break;
        }
}
