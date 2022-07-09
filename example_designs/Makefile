hello_world:
			mkdir -p litex_example_hello_world
			python3 vexriscv_helloworld/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --no-compile-gateware --sim-debug
			python3 vexriscv_helloworld/test/demo/demo.py --build-path=build/sim
			python3 vexriscv_helloworld/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --ram-init=demo.bin --sim-debug

axi_ram:
			mkdir -p litex_example_axiram
			python3 vexriscv_axi_ram/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --with-axi-ram --no-compile-gateware --sim-debug
			python3 vexriscv_axi_ram/test/demo/demo.py --build-path=build/sim
			python3 vexriscv_axi_ram/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --with-axi-ram --ram-init=demo.bin --sim-debug

axi_gpio:
			mkdir -p litex_example_axigpio
			python3 vexriscv_axi_gpio_led/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --with-axi-gpio --no-compile-gateware --sim-debug
			python3 vexriscv_axi_gpio_led/test/demo/demo.py --build-path=build/sim
			python3 vexriscv_axi_gpio_led/litex_sim_rs.py --integrated-main-ram-size=0x10000 --cpu-type=vexriscv --with-axi-gpio --ram-init=demo.bin --sim-debug --trace

clean:
		rm -rf litex_example*
