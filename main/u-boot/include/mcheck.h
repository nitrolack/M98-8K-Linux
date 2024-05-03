/* SPDX-License-Identifier: GPL-2.1+ */
/*
 * Copyright (C) 1996-2024 Free Software Foundation, Inc.
 * This file is part of the GNU C Library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * <https://www.gnu.org/licenses/>.
 */
#ifndef _MCHECK_H
#define _MCHECK_H       1

/*
 * Return values for `mprobe': these are the kinds of inconsistencies that
 * `mcheck' enables detection of.
 */
enum mcheck_status {
	MCHECK_DISABLED = -1,         /* Consistency checking is not turned on.  */
	MCHECK_OK,                    /* Block is fine.  */
	MCHECK_FREE,                  /* Block freed twice.  */
	MCHECK_HEAD,                  /* Memory before the block was clobbered.  */
	MCHECK_TAIL                   /* Memory after the block was clobbered.  */
};

typedef void (*mcheck_abortfunc_t)(enum mcheck_status, const void *p);

int mcheck(mcheck_abortfunc_t func);

/*
 * Similar to `mcheck' but performs checks for all block whenever one of
 * the memory handling functions is called.  This can be very slow.
 */
int mcheck_pedantic(mcheck_abortfunc_t f);

/* Force check of all blocks now.  */
void mcheck_check_all(void);

/*
 * Check for aberrations in a particular malloc'd block. These are the
 * same checks that `mcheck' does, when you free or reallocate a block.
 */
enum mcheck_status mprobe(void *__ptr);

#endif
