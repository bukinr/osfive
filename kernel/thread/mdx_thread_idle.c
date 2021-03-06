/*-
 * Copyright (c) 2019 Ruslan Bukin <br@bsdpad.com>
 * All rights reserved.
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

#include <sys/cdefs.h>
#include <sys/thread.h>

#include <machine/pcpu.h>

static struct thread idle_thread[MDX_CPU_MAX];
uint8_t idle_thread_stack[MDX_CPU_MAX][MDX_THREAD_STACK_SIZE];

/* TODO: remove main_thread from this file ? */
#if !defined(MDX_THREAD_DYNAMIC_ALLOC)
struct thread main_thread;
/* CHERI requires __CHERI_CAPABILITY_WIDTH__/8 byte alignment. */
uint8_t main_thread_stack[MDX_THREAD_STACK_SIZE] __aligned(16);
#endif

void
mdx_thread_init(int cpuid)
{
	struct thread *t;

	t = &idle_thread[cpuid];
	bzero(t, sizeof(struct thread));
	t->td_name = "idle";
	t->td_quantum = 0;
	t->td_prio = 0;
	t->td_idle = 1;
	t->td_state = TD_STATE_READY;

	PCPU_SET(curthread, t);
}
