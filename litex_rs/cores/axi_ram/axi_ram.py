# This file is Copyright (c) 2022 RapidSilicon.
# SPDX-License-Identifier: TBD.

import os

from migen import *

from litex.soc.interconnect import axi

from litex.soc.integration.soc import *
from litex.soc.integration.doc import AutoDoc, ModuleDoc
from litex.soc.integration.soc import SoCRegion

class Open(Signal): pass
class axi_ram(Module, AutoDoc, AutoCSR):
    """Verilog RTL-based Axi_ram"""
    def __init__(self, platform, pads, default_enable=0):
        self.intro = ModuleDoc("""axi_ram: A verilog RTL-based axi_ram derived from the OpenCores.""")

        self.bus  = bus = axi.AXILiteInterface(data_width=32)

        # # #

        self.specials += Instance("axi_ram",
            i_clk=ClockSignal(),
            i_rst=ResetSignal(),
            i_s_axi_awid=Open(),
            i_s_axi_awaddr=bus.aw.addr,
            i_s_axi_awlen=Open(),
            i_s_axi_awsize=Open(),
            i_s_axi_awburst=Open(),
            i_s_axi_awlock=Open(),
            i_s_axi_awcache=Open(),
            i_s_axi_awprot=Open(),
            i_s_axi_awvalid=bus.aw.valid,
            o_s_axi_awready=bus.aw.ready,
            i_s_axi_wdata=bus.w.data,
            i_s_axi_wstrb=bus.w.strb,
            i_s_axi_wlast=Open(),
            i_s_axi_wvalid=bus.w.valid,
            o_s_axi_wready=bus.w.ready,
            o_s_axi_bid=Open(),
            o_s_axi_bresp=bus.b.resp,
            o_s_axi_bvalid=bus.b.valid,
            i_s_axi_bready=bus.b.ready,
            i_s_axi_arid=Open(),
            i_s_axi_araddr=bus.ar.addr,
            i_s_axi_arlen=Open(),
            i_s_axi_arsize=Open(),
            i_s_axi_arburst=Open(),
            i_s_axi_arlock=Open(),
            i_s_axi_arcache=Open(),
            i_s_axi_arprot=Open(),
            i_s_axi_arvalid=bus.ar.valid,
            o_s_axi_arready=bus.ar.ready,
            o_s_axi_rid=Open(),
            o_s_axi_rdata=bus.r.data,
            o_s_axi_rresp=bus.r.resp,
            o_s_axi_rlast=Open(),
            o_s_axi_rvalid=bus.r.valid,
            i_s_axi_rready=bus.r.ready,
        )
        
        rtl_path = str(os.path.expanduser('~')) + "/litex_instll/litex_rs/Core_IPs/AXI_RAM/rtl/axi_ram.v"
        platform.add_source(rtl_path)
