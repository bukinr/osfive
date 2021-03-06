/*-
 * Copyright (c) 2018 Ruslan Bukin <br@bsdpad.com>
 * All rights reserved.
 *
 * This software was developed by SRI International and the University of
 * Cambridge Computer Laboratory under DARPA/AFRL contract FA8750-10-C-0237
 * ("CTSRD"), as part of the DARPA CRASH research programme.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef	_MACHINE_ASM_H_
#define	_MACHINE_ASM_H_

#include <machine/abi.h>

#define	VECTOR(sym)					\
	.text; .globl sym; .ent sym; sym:
#define	VECTOR_END(sym)					\
	.text; .end sym; .globl sym ## End; sym ## End:

#define	ENTRY(sym)					\
	.text; .globl sym; .ent sym; sym:

#define	GLOBAL(sym)					\
	.globl sym; sym:

#define	ASM_ENTRY(sym)					\
	.text; .globl sym; .type sym,@function; sym:

#define	END(sym) .end sym; .size sym, . - sym

#if REG_SIZE == 4
#define	REG_S		sw
#define	REG_L		lw
#define	REG_LI		li
#define	PTR_L		lw
#define	PTR_LA		la
#define	PTR_SRL		srl
#define	PTR_SLL		sll
#define	PTR_ADDU	addu
#define	PTR_ADDIU	addiu
#define	PTR_SUBU	subu
#define	MTC0		mtc0
#define	MFC0		mfc0
#elif REG_SIZE == 8
#define	REG_S		sd
#define	REG_L		ld
#define	REG_LI		dli
#define	PTR_L		ld
#define	PTR_LA		dla
#define	PTR_SRL		dsrl
#define	PTR_SLL		dsll
#define	PTR_ADDU	daddu
#define	PTR_ADDIU	daddiu
#define	PTR_SUBU	dsubu
#define	MTC0		dmtc0
#define	MFC0		dmfc0
#endif

/*
 * See Chapter 8. MIPS® Architecture For Programmers Vol. III:
 * MIPS32® / microMIPS32™ Privileged Resource Architecture.
 */
#define	HAZARD_CLEAR	nop;nop;nop;nop;ehb
#define	_C_LABEL(x)     x

#endif	/* !_MACHINE_ASM_H_ */
