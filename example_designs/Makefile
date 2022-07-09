hello_world:
			mkdir -p litex_example_hello_world
			python3 vexriscv_hello_world/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --no-compile-gateware --sim-debug
			python3 vexriscv_hello_world/test/demo/demo.py --build-path=build/sim
			python3 vexriscv_hello_world/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --ram-init=demo.bin --sim-debug

axi_ram:
			mkdir -p litex_example_axi_ram
			python3 vexriscv_axi_ram/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --with-axi-ram --no-compile-gateware --sim-debug
			python3 vexriscv_axi_ram/test/demo/demo.py --build-path=build/sim
			python3 vexriscv_axi_ram/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --with-axi-ram --ram-init=demo.bin --sim-debug

axi_gpio:
			mkdir -p litex_example_axi_gpio
			python3 vexriscv_axi_gpio/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --with-axi-gpio --no-compile-gateware --sim-debug
			python3 vexriscv_axi_gpio/test/demo/demo.py --build-path=build/sim
			python3 vexriscv_axi_gpio/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --with-axi-gpio --ram-init=demo.bin --sim-debug --trace

clean:
		rm -rf litex_example*
