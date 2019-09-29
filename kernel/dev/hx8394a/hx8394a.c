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
#include <sys/systm.h>
#include <dev/display/dsi.h>
#include <dev/display/mipi_dcs.h>
#include <dev/hx8394a/hx8394a.h>

#define	HX8394A_DEBUG
#undef	HX8394A_DEBUG

#ifdef	HX8394A_DEBUG
#define	dprintf(fmt, ...)	printf(fmt, ##__VA_ARGS__)
#else
#define	dprintf(fmt, ...)
#endif

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define dcs_write_seq(dev, seq...)			\
({							\
	static const uint8_t data[] = { seq };		\
	dsi_cmd(dev, data, ARRAY_SIZE(data));		\
})

static void
dsi_cmd(dsi_device_t *dev, const uint8_t *params, uint32_t nparams)
{

	if (nparams < 2)
		dev->dsi_short(dev, dev->vchid, DSI_DCS_SHORT_PKT_WRITE_P1,
		    params[0], params[1]); 
	else
		dev->dsi_long(dev, dev->vchid, DSI_DCS_LONG_PKT_WRITE,
		    params, nparams); 
}

void
hx8394a_init(dsi_device_t *dev)
{

	dcs_write_seq(dev, 0x36, 0x02); /* Flip horizontally */

	dcs_write_seq(dev, 0xB9, 0xFF, 0x83, 0x94 );
	dcs_write_seq(dev, 0xBA, 0x11, 0x82, 0x00, 0x16, 0xC5, 0x00, 0x10, 0xFF, 0x0F, 0x24, 0x03, 0x21, 0x24, 0x25, 0x20, 0x08 );

	dcs_write_seq(dev, 0xB9, 0xFF, 0x83, 0x94 );
	dcs_write_seq(dev, 0xBA, 0x13, 0x42, 0x00, 0x16, 0xC5, 0x00, 0x10, 0xFF, 0x0F, 0x24, 0x03, 0x21, 0x24, 0x25, 0x20, 0x08 );
	dcs_write_seq(dev, 0xBA, 0x11, 0x82, 0x00, 0x16, 0xC5, 0x00, 0x10, 0xFF, 0x0F, 0x24, 0x03, 0x21, 0x24, 0x25, 0x20, 0x08 );
	dcs_write_seq(dev, 0xB1, 0x01, 0x00, 0x54, 0x87, 0x01, 0x11, 0x11, 0x35, 0x3D, 0x29, 0x29, 0x47, 0x12, 0x01, 0xE6, 0xE2 );
	dcs_write_seq(dev, 0xB4, 0x80, 0x08, 0x32, 0x10, 0x06, 0x32, 0x15, 0x08, 0x32, 0x10, 0x08, 0x33, 0x05, 0x55, 0x0A, 0x37, 0x05, 0x55, 0x0A, 0x68, 0x68, 0x0A );
	dcs_write_seq(dev, 0xD5, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x01, 0x00, 0x00, 0x33, 0x00, 0x00, 0x99, 0x88, 0xAA, 0xBB, 0x45, 0x67, 0x01, 0x23, 0x01, 0x23, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x99, 0xAA, 0xBB, 0x32, 0x10, 0x76, 0x54, 0x32, 0x10, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x1E, 0x08 );
	dcs_write_seq(dev, 0xB6, 0x00 );
	dcs_write_seq(dev, 0xE0, 0x00, 0x04, 0x09, 0x3F, 0x3F, 0x3F, 0x17, 0x3A, 0x06, 0x0C, 0x0E, 0x11, 0x13, 0x11, 0x14, 0x0F, 0x1B, 0x00, 0x04, 0x09, 0x3F, 0x3F, 0x3F, 0x17, 0x3A, 0x06, 0x0C, 0x0E, 0x11, 0x13, 0x11, 0x14, 0x0F, 0x1B, 0x0B, 0x14, 0x06, 0x0E, 0x0B, 0x14, 0x06, 0x0E );
	dcs_write_seq(dev, 0xBF, 0x06, 0x00, 0x10, 0x04 );
	dcs_write_seq(dev, 0xC0, 0x0C, 0x17 );
	dcs_write_seq(dev, 0xC7, 0x00, 0x10, 0x00, 0x10 );
	dcs_write_seq(dev, 0xB2, 0x00, 0xC8, 0x0D, 0x05, 0x00, 0x22 );
	dcs_write_seq(dev, 0xCC, 0x01 );
	dcs_write_seq(dev, 0xBC, 0x07 );
	dcs_write_seq(dev, 0x35, 0x00 );
	dcs_write_seq(dev, 0xD4, 0x30 );

	udelay(100000);

	dcs_write_seq(dev, MIPI_DCS_EXIT_SLEEP_MODE);

	/* Wait for sleep out */
	udelay(120000);

	dcs_write_seq(dev, MIPI_DCS_SET_DISPLAY_ON);

	udelay(100000);

	/* Content Adaptive Backlight Control */
	dcs_write_seq(dev, MIPI_DCS_SET_DISPLAY_BRIGHTNESS, 0x7F);
	dcs_write_seq(dev, MIPI_DCS_WRITE_CONTROL_DISPLAY, 0x2C);
	dcs_write_seq(dev, MIPI_DCS_WRITE_POWER_SAVE, 0x02);
	dcs_write_seq(dev, MIPI_DCS_SET_CABC_MIN_BRIGHTNESS, 0xFF);
}
