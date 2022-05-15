/* SPDX-License-Identifier: MIT */

/*
 * Copyright (c) 2022 Roland Gehl
 *
 * rr.h - Main header file.
 */

#ifndef REDUCER_H
#define REDUCER_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define _POSIX_C_SOURCE 200809L

struct reduced_exp {
        int place; /* Multiplier */
        double ans; /* Radicand */
};

double root(int degree, int radicand);
struct reduced_exp reduce_exp(int degree, int radicand);

#endif /* RR_H */
