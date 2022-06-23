#!/usr/bin/env python3

#
# This file is part of LiteX.
#
# Copyright (c) 2022 Florent Kermarrec <florent@enjoy-digital.fr>
# SPDX-License-Identifier: BSD-2-Clause

from migen import *

from litex.build.io import CRG
from litex.build.generic_platform import Pins, Subsignal
from litex.build.osfpga import OSFPGAPlatform

from litex_rs.AXI_GPIO.core_axi4gpio import gpio_axi
from litex_rs.AXI_RAM.core_ram import axi_ram

from litex.soc.integration.soc_core import *
from litex.soc.integration.builder import *

from litex.soc.integration.soc import *



# Platform ---------------------------------------------------------------------------------

_io = [
    # Clk.
    ("clk", 0, Pins(1)),

    # Serial.
    ("serial", 0,
        Subsignal("tx", Pins(1)),
        Subsignal("rx", Pins(1)),
    ),
    ("gpio", 0,
    Subsignal("oe", Pins(32)),
    Subsignal("o",  Pins(32)),
    Subsignal("i",  Pins(32)),
    ),
]

class Platform(OSFPGAPlatform):
    def __init__(self, toolchain="foedag", device="mpw1"):
        OSFPGAPlatform.__init__(self, device=device, toolchain=toolchain, io=_io)

# BaseSoC ------------------------------------------------------------------------------------------

class BaseSoC(SoCCore):
    def __init__(self, platform, 
        sys_clk_freq=int(10e6), 
        axigpio=False, 
        axiram=False, 
        multiaxiram=False, 
        **kwargs):
        
        # CRG --------------------------------------------------------------------------------------
        self.submodules.crg = CRG(platform.request("clk"))

        # SoCCore ----------------------------------------------------------------------------------
        SoCCore.__init__(self, platform, sys_clk_freq, ident="LiteX Test SoC on OS-FPGA", **kwargs)


        # AXI GPIO------------------------------------------------------------------
        if axigpio:
            self.submodules.gpio_axi = gpio_axi(platform, platform.request("gpio"))
            self.bus.add_slave(name="gpio_axi", slave=self.gpio_axi.bus, region=SoCRegion(
                origin = 0xf0020000,
                size = 1024,
                cached = False,
                ))  

        # AXI RAM---------------------------------------------------------------------------------------
        if axiram:
            self.submodules.axi_ram = axi_ram(platform, pads=None)
            self.bus.add_slave(name="axi_ram", slave=self.axi_ram.bus, region=SoCRegion(
                origin = 0x50000000,
                size   = 1024, 
                cached = True, ))

# Build --------------------------------------------------------------------------------------------

def main():
    from litex.soc.integration.soc import LiteXSoCArgumentParser
    parser = LiteXSoCArgumentParser(description="LiteX Test SoC on OS-FPGA")
    target_group = parser.add_argument_group(title="Target options")
    target_group.add_argument("--build",            action="store_true",   help="Build design.")
    target_group.add_argument("--toolchain",        default="raptor",      help="FPGA toolchain.")
    target_group.add_argument("--device",           default="gemini",      help="FPGA device.")
    target_group.add_argument("--axigpio",          action="store_true",   help="AXI based 32 bit GPIO")
    target_group.add_argument("--axiram",           action="store_true",   help="AXI based RAM")
    builder_args(parser)
    soc_core_args(parser)
    args = parser.parse_args()

    platform = Platform(toolchain=args.toolchain, device=args.device)
    soc      = BaseSoC(platform,
                axigpio  = args.axigpio,
                axiram   = args.axiram,
                **soc_core_argdict(args))
                
    builder  = Builder(soc, **builder_argdict(args))
    if args.build:
        builder.build()


if __name__ == "__main__":
    main()
