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

#ifndef _ARM_STM_STM32L4_USART_H_
#define _ARM_STM_STM32L4_USART_H_

#define	USART_CR1		0x00 /* Control register 1 */
#define	 USART_CR1_RXNEIE	(1 << 5) /* RXNE interrupt enable */
#define	 USART_CR1_TE		(1 << 3) /* Transmitter enable */
#define	 USART_CR1_RE		(1 << 2) /* Receiver enable */
#define	 USART_CR1_UE		(1 << 0) /* USART enable */
#define	USART_CR2		0x04 /* Control register 2 */
#define	USART_CR3		0x08 /* Control register 3 */
#define	USART_BRR		0x0C /* Baud rate register */
#define	USART_GTPR		0x10 /* Guard time and prescaler register */
#define	USART_ISR		0x1C /* Interrupt and status register */
#define	 USART_ISR_RXNE		(1 << 5) /* Read data register not empty */
#define	 USART_ISR_TXE		(1 << 7) /* Transmit data register empty */
#define	USART_RDR		0x24 /* Receive data register */
#define	USART_TDR		0x28 /* Transmit data register */

struct stm32f4_usart_softc {
	uint32_t base;
};

int stm32f4_usart_init(struct stm32f4_usart_softc *sc, uint32_t base,
    uint32_t cpu_freq, uint32_t baud_rate);
void stm32f4_usart_putc(struct stm32f4_usart_softc *sc, char c);

#endif /* !_ARM_STM_STM32L4_USART_H_ */
