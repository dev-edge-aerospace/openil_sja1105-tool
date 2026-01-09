/******************************************************************************
 * Copyright (c) 2017, NXP Semiconductors
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from this
 * software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/* These are our own includes */
#include <lib/include/static-config.h>
#include <lib/include/gtable.h>
#include <lib/include/spi.h>

static void sja1105_cfg_pad_mii_tx_access(
		void *buf,
		struct sja1105_cfg_pad_mii_tx *pad_mii_tx,
		int write)
{
	int  (*pack_or_unpack)(void*, uint64_t*, int, int, int);
	int    size = 4;

	if (write == 0) {
		pack_or_unpack = gtable_unpack;
		memset(pad_mii_tx, 0, sizeof(*pad_mii_tx));
	} else {
		pack_or_unpack = gtable_pack;
		memset(buf, 0, size);
	}
	pack_or_unpack(buf, &pad_mii_tx->d32_os,   28, 27, 4);
	pack_or_unpack(buf, &pad_mii_tx->d32_ipud, 25, 24, 4);
	pack_or_unpack(buf, &pad_mii_tx->d10_os,   20, 19, 4);
	pack_or_unpack(buf, &pad_mii_tx->d10_ipud, 17, 16, 4);
	pack_or_unpack(buf, &pad_mii_tx->ctrl_os,  12, 11, 4);
	pack_or_unpack(buf, &pad_mii_tx->ctrl_ipud, 9,  8, 4);
	pack_or_unpack(buf, &pad_mii_tx->clk_os,    4,  3, 4);
	pack_or_unpack(buf, &pad_mii_tx->clk_ih,    2,  2, 4);
	pack_or_unpack(buf, &pad_mii_tx->clk_ipud,  1,  0, 4);
}


static void sja1105_cfg_pad_mii_id_access(
		void *buf,
		struct sja1105_cfg_pad_mii_id *pad_mii_id,
		int write)
{
	int  (*pack_or_unpack)(void*, uint64_t*, int, int, int);
	int    size = 4;

	if (write == 0) {
		pack_or_unpack = gtable_unpack;
		memset(pad_mii_id, 0, sizeof(*pad_mii_id));
	} else {
		pack_or_unpack = gtable_pack;
		memset(buf, 0, size);
	}
	pack_or_unpack(buf, &pad_mii_id->rxc_stable_ovr,   15, 15, 4);
	pack_or_unpack(buf, &pad_mii_id->rxc_delay, 14, 10, 4);
	pack_or_unpack(buf, &pad_mii_id->rxc_bypass,   9, 9, 4);
	pack_or_unpack(buf, &pad_mii_id->rxc_pd, 8, 8, 4);
	pack_or_unpack(buf, &pad_mii_id->txc_stable_ovr,  7, 7, 4);
	pack_or_unpack(buf, &pad_mii_id->txc_delay, 6,  2, 4);
	pack_or_unpack(buf, &pad_mii_id->txc_bypass,    1,  1, 4);
	pack_or_unpack(buf, &pad_mii_id->txc_pd,    0,  0, 4);
}



void sja1105_cfg_pad_mii_tx_pack(void *buf,
                                 struct sja1105_cfg_pad_mii_tx *pad_mii_tx)
{
	sja1105_cfg_pad_mii_tx_access(buf, pad_mii_tx, 1);
}

void sja1105_cfg_pad_mii_id_pack(void *buf,
                                 struct sja1105_cfg_pad_mii_id *pad_mii_id)
{
	sja1105_cfg_pad_mii_id_access(buf, pad_mii_id, 1);
}

void sja1105_cfg_pad_mii_tx_unpack(void *buf,
                                   struct sja1105_cfg_pad_mii_tx *pad_mii_tx)
{
	sja1105_cfg_pad_mii_tx_access(buf, pad_mii_tx, 0);
}

void sja1105_cfg_pad_mii_tx_show(struct sja1105_cfg_pad_mii_tx *pad_mii_tx)
{
	printf("D32_OS    %" PRIX64 "\n", pad_mii_tx->d32_os);
	printf("D32_IPUD  %" PRIX64 "\n", pad_mii_tx->d32_ipud);
	printf("D10_OS    %" PRIX64 "\n", pad_mii_tx->d10_os);
	printf("D10_IPUD  %" PRIX64 "\n", pad_mii_tx->d10_ipud);
	printf("CTRL_OS   %" PRIX64 "\n", pad_mii_tx->ctrl_os);
	printf("CTRL_IPUD %" PRIX64 "\n", pad_mii_tx->ctrl_ipud);
	printf("CLK_OS    %" PRIX64 "\n", pad_mii_tx->clk_os);
	printf("CLK_IH    %" PRIX64 "\n", pad_mii_tx->clk_ih);
	printf("CLK_IPUD  %" PRIX64 "\n", pad_mii_tx->clk_ipud);
}

