/* -------------------------------------------

    Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.

------------------------------------------- */

#ifndef __BITMANIP_H__
#define __BITMANIP_H__

/// Name: CoreBoot Bits API.
/// Purpose: Bit manip helpers.

#define cb_set_bit(X, O)   X = (1 << O) | X
#define cb_clear_bit(X, O) X = ~(1 << O) & X
#define cb_toogle(X, O)	   X = (1 << O) ^ X
#define cb_lsb(X)		   X = X & -X
#define cb_msb(X)		   X = -(cb_lsb(X)) & X

#endif // ifndef __BITMANIP_H__
