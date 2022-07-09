# This file is Copyright (c) 2022 RapidSilicon.
# SPDX-License-Identifier: TBD.

import os

from migen import *

from litex.soc.interconnect import axi

from litex.soc.integration.soc import *
from litex.soc.integration.doc import AutoDoc, ModuleDoc


def _to_signal(obj):
    return obj.raw_bits() if isinstance(obj, Record) else obj


class Open(Signal): pass
class gpio_axi(Module, AutoDoc, AutoCSR):
    def __init__(self, platform, pads, default_enable=0):
        self.intro = ModuleDoc("""GPIO_AXI: A verilog RTL-based GPIOs derived from Xilinx Vivado IP library.""")

        self.bus  = bus = axi.AXILiteInterface(address_width=32,data_width=32)

        # # #

        internal = not (hasattr(pads, "o")  and hasattr(pads, "i"))
        nbits    = len(pads) if internal else len(pads.o)

        if internal:
            if isinstance(pads, Record):
                pads = pads.flatten()


        self.specials += Instance("AXI4LITE_GPIO",
            i_CLK=ClockSignal(),
            i_RSTN=~ResetSignal(),
            i_GPIN=self.GPIN,
            o_GPOUT=self.GPOUT,
            o_INT=self.INT,
            i_AWADDR=bus.aw.addr,
            i_AWPROT=Open(),
            i_AWVALID=bus.aw.valid,
            o_AWREADY=bus.aw.ready,
            i_WDATA=bus.w.data,
            i_WSTRB=bus.w.strb,
            i_WVALID=bus.w.valid,
            o_WREADY=bus.w.ready,
            o_BRESP=bus.b.resp,
            o_BVALID=bus.b.valid,
            i_BREADY=bus.b.ready,
            i_ARADDR=bus.ar.addr,
            i_ARPROT=Open(),
            i_ARVALID=bus.ar.valid,
            o_ARREADY=bus.ar.ready,
            o_RDATA=bus.r.data,
            o_RRESP=bus.r.resp,
            o_RVALID=bus.r.valid,
            i_RREADY=bus.r.ready,
        )
        nbits = 7
        for i in range(nbits):
            self.comb += pads.i[i].eq(self.GPIN[i])
            self.comb += pads.o[i].eq(self.GPOUT[i])
            
    
        rtl_path = str(os.path.expanduser('~')) + "/litex_instll/litex_rs/Core_IPs/AXI_GPIO/rtl"
        platform.add_source_dir(path=rtl_path)
