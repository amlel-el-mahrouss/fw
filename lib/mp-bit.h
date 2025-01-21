/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#ifndef __BITMANIP_H__
#define __BITMANIP_H__

/// Name: CoreBoot Bits API.
/// Purpose: Bit manip helpers.

#define mp_set_bit(X, O)   X = (1 << O) | X
#define mp_clear_bit(X, O) X = ~(1 << O) & X
#define mp_toogle(X, O)	   X = (1 << O) ^ X
#define mp_lsb(X)		   X = X & -X
#define mp_msb(X)		   X = -(mp_lsb(X)) & X

#endif // ifndef __BITMANIP_H__
