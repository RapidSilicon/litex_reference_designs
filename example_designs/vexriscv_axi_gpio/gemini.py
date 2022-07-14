#!/usr/bin/env python3

# This file is Copyright (c) 2022 RapidSilicon.
# SPDX-License-Identifier: TBD.

from migen import *

from litex.build.io import CRG
from litex.build.generic_platform import Pins, Subsignal
from litex.build.osfpga import OSFPGAPlatform

from litex_rs.cores.axi_gpio import AXIGPIO

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
    def __init__(self, toolchain="raptor", device="gemini"):
        OSFPGAPlatform.__init__(self, device=device, toolchain=toolchain, io=_io)

# BaseSoC ------------------------------------------------------------------------------------------

class BaseSoC(SoCCore):
    def __init__(self, platform, 
        sys_clk_freq  = int(10e6),
        with_axi_gpio = False,
        **kwargs):
        
        # CRG --------------------------------------------------------------------------------------
        self.submodules.crg = CRG(platform.request("clk"))

        # SoCCore ----------------------------------------------------------------------------------
        SoCCore.__init__(self, platform, sys_clk_freq, ident="LiteX Test SoC on OS-FPGA", **kwargs)


        # AXI GPIO ---------------------------------------------------------------------------------
        if with_axi_gpio:
            self.submodules.axi_gpio = AXIGPIO(platform, platform.request("gpio"))
            self.bus.add_slave(name="axi_gpio", slave=self.axi_gpio.bus, region=SoCRegion(
                origin = 0xf0020000,
                size   = 1024,
                cached = False,
                )
            )

# Build --------------------------------------------------------------------------------------------

def main():
    from litex.soc.integration.soc import LiteXSoCArgumentParser
    parser = LiteXSoCArgumentParser(description="LiteX Test SoC on OS-FPGA.")
    target_group = parser.add_argument_group(title="Target options")
    target_group.add_argument("--build",         action="store_true", help="Build design.")
    target_group.add_argument("--toolchain",     default="raptor",    help="FPGA toolchain.")
    target_group.add_argument("--device",        default="gemini",    help="FPGA device.")
    target_group.add_argument("--with-axi-gpio", action="store_true", help="Add AXI-GPIO (32-bit) to design.")
    builder_args(parser)
    soc_core_args(parser)
    args = parser.parse_args()

    platform = Platform(toolchain=args.toolchain, device=args.device)
    soc      = BaseSoC(platform,
        with_axi_gpio = args.with_axi_gpio,
        **soc_core_argdict(args)
    )
                
    builder  = Builder(soc, **builder_argdict(args))
    if args.build:
        builder.build()


if __name__ == "__main__":
    main()
