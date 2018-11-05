/*-
 * Copyright (c) 2018 Ruslan Bukin <br@bsdpad.com>
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
#include <sys/systm.h>
#include <arm/stm/stm32l4_rtc.h>

#include <machine/frame.h>

#define	RD4(_sc, _reg)		*(volatile uint32_t *)((_sc)->base + _reg)
#define	WR4(_sc, _reg, _val)	*(volatile uint32_t *)((_sc)->base + _reg) = _val

void
stm32l4_rtc_init(struct stm32l4_rtc_softc *sc, uint32_t base)
{

	sc->base = base;
}

int
stm32l4_rtc_enable(struct stm32l4_rtc_softc *sc)
{
	int timeout;
	int reg;

	/* Remove write protection */
	WR4(sc, RTC_WPR, 0xca);
	WR4(sc, RTC_WPR, 0x53);

	WR4(sc, RTC_ISR, ISR_INIT);

	timeout = 1000;
	do {
		reg = RD4(sc, RTC_ISR);
		if (reg & ISR_INITF)
			break;
	} while (--timeout);

	if (timeout == 0) {
		printf("%s: Failed to enter INIT mode\n", __func__);
		return (-1);
	}

	printf("%s: ISR %x\n", __func__, RD4(sc, RTC_ISR));
	printf("%s: TR %x\n", __func__, RD4(sc, RTC_TR));

	return (0);
}
