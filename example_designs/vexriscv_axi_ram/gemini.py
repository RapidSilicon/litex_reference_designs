#!/usr/bin/env python3

# This file is Copyright (c) 2022 RapidSilicon.
# SPDX-License-Identifier: TBD.

from migen import *

from litex.build.io import CRG
from litex.build.generic_platform import Pins, Subsignal
from litex.build.osfpga import OSFPGAPlatform

from litex_rs.cores.axi_ram.python_wrapper  import AXIRAM

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
]

class Platform(OSFPGAPlatform):
    def __init__(self, toolchain="raptor", device="gemini"):
        OSFPGAPlatform.__init__(self, device=device, toolchain=toolchain, io=_io)

# BaseSoC ------------------------------------------------------------------------------------------

class BaseSoC(SoCCore):
    def __init__(self, platform, 
        sys_clk_freq  = int(10e6),
        with_axi_ram  = False,
        **kwargs):
        
        # CRG --------------------------------------------------------------------------------------
        self.submodules.crg = CRG(platform.request("clk"))

        # SoCCore ----------------------------------------------------------------------------------
        SoCCore.__init__(self, platform, sys_clk_freq, ident="LiteX Test SoC on OS-FPGA", **kwargs)


        # AXI RAM-----------------------------------------------------------------------------------
        if with_axi_ram:
            self.submodules.axi_ram = AXIRAM(platform, pads=None)
            self.bus.add_slave(name="axi_ram", slave=self.axi_ram.bus, region=SoCRegion(
                origin = 0x50000000,
                size   = 1024, 
                cached = True,
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
    target_group.add_argument("--with-axi-ram",  action="store_true", help="Add AXI-RAM to design.")
    builder_args(parser)
    soc_core_args(parser)
    args = parser.parse_args()

    platform = Platform(toolchain=args.toolchain, device=args.device)
    soc      = BaseSoC(platform,
        with_axi_ram  = args.with_axi_ram,
        **soc_core_argdict(args)
    )
                
    builder  = Builder(soc, **builder_argdict(args))
    if args.build:
        builder.build()


if __name__ == "__main__":
    main()
