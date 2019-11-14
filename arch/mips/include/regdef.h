/*	$NetBSD: regdef.h,v 1.12 2005/12/11 12:18:09 christos Exp $	*/

/*
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell. This file is derived from the MIPS RISC
 * Architecture book by Gerry Kane.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)regdef.h	8.1 (Berkeley) 6/10/93
 * $FreeBSD$
 */

#ifndef _MIPS_REGDEF_H
#define _MIPS_REGDEF_H

#define zero	$0	/* always zero */
#define AT	$at	/* assembler temporary */
#define v0	$2	/* return value */
#define v1	$3
#define a0	$4	/* argument registers */
#define a1	$5
#define a2	$6
#define a3	$7
#if defined(__mips_n32) || defined(__mips_n64)
#define	a4	$8
#define	a5	$9
#define	a6	$10
#define	a7	$11
#define	t0	$12	/* temp registers (not saved across subroutine calls) */
#define	t1	$13
#define	t2	$14
#define	t3	$15
#else
#define t0	$8	/* temp registers (not saved across subroutine calls) */
#define t1	$9
#define t2	$10
#define t3	$11
#define t4	$12
#define t5	$13
#define t6	$14
#define t7	$15
#endif /* __mips_n32 || __mips_n64 */
#define s0	$16	/* saved across subroutine calls (callee saved) */
#define s1	$17
#define s2	$18
#define s3	$19
#define s4	$20
#define s5	$21
#define s6	$22
#define s7	$23
#define t8	$24	/* two more temporary registers */
#define t9	$25
#define k0	$26	/* kernel temporary */
#define k1	$27
#define gp	$28	/* global pointer */
#define sp	$29	/* stack pointer */
#define s8	$30	/* one more callee saved */
#define ra	$31	/* return address */

/*
 * These are temp registers whose names can be used in either the old
 * or new ABI, although they map to different physical registers.  In
 * the old ABI, they map to t4-t7, and in the new ABI, they map to a4-a7.
 *
 * Because they overlap with the last 4 arg regs in the new ABI, ta0-ta3
 * should be used only when we need more than t0-t3.
 */
#if defined(__mips_n32) || defined(__mips_n64)
#define	ta0	$8
#define	ta1	$9
#define	ta2	$10
#define	ta3	$11
#else
#define	ta0	$12
#define	ta1	$13
#define	ta2	$14
#define	ta3	$15
#endif /* __mips_n32 || __mips_n64 */

#ifdef CPU_CHERI
#define	DDC		(CHERIBASE + CREG_SIZE * 0)
#define	C1		(CHERIBASE + CREG_SIZE * 1)
#define	C2		(CHERIBASE + CREG_SIZE * 2)
#define	C3		(CHERIBASE + CREG_SIZE * 3)
#define	C4		(CHERIBASE + CREG_SIZE * 4)
#define	C5		(CHERIBASE + CREG_SIZE * 5)
#define	C6		(CHERIBASE + CREG_SIZE * 6)
#define	C7		(CHERIBASE + CREG_SIZE * 7)
#define	C8		(CHERIBASE + CREG_SIZE * 8)
#define	C9		(CHERIBASE + CREG_SIZE * 9)
#define	C10		(CHERIBASE + CREG_SIZE * 10)
#define	STC		(CHERIBASE + CREG_SIZE * 11)
#define	C12		(CHERIBASE + CREG_SIZE * 12)
#define	C13		(CHERIBASE + CREG_SIZE * 13)
#define	C14		(CHERIBASE + CREG_SIZE * 14)
#define	C15		(CHERIBASE + CREG_SIZE * 15)
#define	C16		(CHERIBASE + CREG_SIZE * 16)
#define	C17		(CHERIBASE + CREG_SIZE * 17)
#define	C18		(CHERIBASE + CREG_SIZE * 18)
#define	C19		(CHERIBASE + CREG_SIZE * 19)
#define	C20		(CHERIBASE + CREG_SIZE * 20)
#define	C21		(CHERIBASE + CREG_SIZE * 21)
#define	C22		(CHERIBASE + CREG_SIZE * 22)
#define	C23		(CHERIBASE + CREG_SIZE * 23)
#define	C24		(CHERIBASE + CREG_SIZE * 24)
#define	C25		(CHERIBASE + CREG_SIZE * 25)
#define	IDC		(CHERIBASE + CREG_SIZE * 26)
#define	C27		(CHERIBASE + CREG_SIZE * 27)
#define	C28		(CHERIBASE + CREG_SIZE * 28)
#define	C29		(CHERIBASE + CREG_SIZE * 29)
#define	C30		(CHERIBASE + CREG_SIZE * 30)
#define	C31		(CHERIBASE + CREG_SIZE * 31)
#define	PCC		(CHERIBASE + CREG_SIZE * 32)
#define	CAPCAUSE	(CHERIBASE + CREG_SIZE * 33)
#endif

#endif /* _MIPS_REGDEF_H */
