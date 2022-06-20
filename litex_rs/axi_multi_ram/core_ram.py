import os

from migen import *

#from litex import get_data_mod
from litex.soc.interconnect import axi
from litex.soc.interconnect import wishbone

from litex.soc.integration.soc import *
from litex.soc.integration.doc import AutoDoc, ModuleDoc
from litex.soc.integration.soc import SoCRegion
from litex.soc.interconnect.axi import *

class Open(Signal): pass
class axi_ram_1(Module, AutoDoc, AutoCSR):
    """Verilog RTL-based Axi_ram"""
    def __init__(self, platform, pads, default_enable=0):
        self.intro = ModuleDoc("""axi_ram: A verilog RTL-based axi_ram derived from the OpenCores.""")

        self.bus  = bus = axi.AXILiteInterface(data_width=32)
        self.clk = ClockSignal()
        self.rst = ResetSignal()
        self.s_axi_awid = Signal(8)
        self.s_axi_awaddr = Signal(16)
        self.s_axi_awlen = Signal(8)
        self.s_axi_awsize = Signal(3)
        self.s_axi_awburst = Signal(2)
        self.s_axi_awlock = Signal()
        self.s_axi_awcache = Signal(4)
        self.s_axi_awprot = Signal(3)
        self.s_axi_awvalid = Signal()
        self.s_axi_awready = Signal()
        self.s_axi_wdata = Signal(32)
        self.s_axi_wstrb = Signal(4)
        self.s_axi_wlast = Signal()
        self.s_axi_wvalid = Signal()
        self.s_axi_wready = Signal()
        self.s_axi_bid = Signal(8)
        self.s_axi_bresp = Signal(2)
        self.s_axi_bvalid = Signal()
        self.s_axi_bready = Signal()
        self.s_axi_arid = Signal(8)
        self.s_axi_araddr = Signal(16)
        self.s_axi_arlen = Signal(8)
        self.s_axi_arsize = Signal(3)
        self.s_axi_arburst = Signal(2)
        self.s_axi_arlock = Signal()
        self.s_axi_arcache = Signal(4)
        self.s_axi_arprot = Signal(3)
        self.s_axi_arvalid = Signal()
        self.s_axi_arready = Signal()
        self.s_axi_rid = Signal(8)
        self.s_axi_rdata = Signal(32)
        self.s_axi_rresp = Signal(2)
        self.s_axi_rlast = Signal()
        self.s_axi_rvalid = Signal()
        self.s_axi_rready = Signal()

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


class axi_ram_2(Module, AutoDoc, AutoCSR):
    """Verilog RTL-based Axi_ram"""
    def __init__(self, platform, pads, default_enable=0):
        self.intro = ModuleDoc("""axi_ram: A verilog RTL-based axi_ram derived from the OpenCores.""")
        self.bus  = bus = axi.AXILiteInterface(data_width=32)
        self.clk = ClockSignal()
        self.rst = ResetSignal()
        self.s_axi_awid = Signal(8)
        self.s_axi_awaddr = Signal(16)
        self.s_axi_awlen = Signal(8)
        self.s_axi_awsize = Signal(3)
        self.s_axi_awburst = Signal(2)
        self.s_axi_awlock = Signal()
        self.s_axi_awcache = Signal(4)
        self.s_axi_awprot = Signal(3)
        self.s_axi_awvalid = Signal()
        self.s_axi_awready = Signal()
        self.s_axi_wdata = Signal(32)
        self.s_axi_wstrb = Signal(4)
        self.s_axi_wlast = Signal()
        self.s_axi_wvalid = Signal()
        self.s_axi_wready = Signal()
        self.s_axi_bid = Signal(8)
        self.s_axi_bresp = Signal(2)
        self.s_axi_bvalid = Signal()
        self.s_axi_bready = Signal()
        self.s_axi_arid = Signal(8)
        self.s_axi_araddr = Signal(16)
        self.s_axi_arlen = Signal(8)
        self.s_axi_arsize = Signal(3)
        self.s_axi_arburst = Signal(2)
        self.s_axi_arlock = Signal()
        self.s_axi_arcache = Signal(4)
        self.s_axi_arprot = Signal(3)
        self.s_axi_arvalid = Signal()
        self.s_axi_arready = Signal()
        self.s_axi_rid = Signal(8)
        self.s_axi_rdata = Signal(32)
        self.s_axi_rresp = Signal(2)
        self.s_axi_rlast = Signal()
        self.s_axi_rvalid = Signal()
        self.s_axi_rready = Signal()

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
        
        rtl_path = str(os.path.expanduser('~')) + "/tarball/tarball_20_06/litex_rs/litex_rs/axi_ram/rtl/axi_ram.v"
        platform.add_source(rtl_path)
