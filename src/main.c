/* SPDX-License-Identifier: MIT */

/*
 * Copyright (c) 2022 Roland Gehl
 *
 * main.c - Main file.
 */

#include "rr.h"

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
                radicand = radicand * -1;
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
