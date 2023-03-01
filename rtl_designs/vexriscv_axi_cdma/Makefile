
##
## *****************************
## 0: All: 
## 	create the .elf file
##  Convert .elf to hex
## 	copy the hex file to rtl directory
##  simulate the design via VCS

.PHONY: all

# Define variables
ELF2HEX = riscv64-unknown-elf-elf2hex
BIT_WIDTH = 32
ELF_FILE = ./bare_metal_stimulus/build/AXI_RAM.elf
HEX_FILE = ./bare_metal_stimulus/build/AXI_RAM_$(BIT_WIDTH).hex
RTL_DIR = ./rtl
SUBMAKE:= $(MAKE) --no-print-directory -C
# Define targets
all: load copy_hex simulate

.PHONY: baremetal
baremetal:
	$(SUBMAKE) bare_metal_stimulus all
	

##
## *****************************
## 1: load: 
## 	create the .elf file
##  Convert .elf to hex

.PHONY: load
load:
	$(SUBMAKE) bare_metal_stimulus
	export RISCV_PATH=/nfs_eda_sw/softwares/opensource/toolchains/riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-centos6/;
	$(ELF2HEX) --bit-width $(BIT_WIDTH) --input $(ELF_FILE) --output $(HEX_FILE)


##
## *****************************
## 2: clean: 
## 	Clean the complete project

clean:

	$(SUBMAKE) bare_metal_stimulus clean


##
## *****************************
## 3: simulate: 
##  simulate the design via VCS	


.PHONY: simulate
simulate:
	vcs -sverilog -full64 ./rtl/*.v  ./sim/*.v -debug_all -timescale=1ns/100ps +define+VPD +define+fsdb -debug_acc+all -kdb -lca +define+A
	./simv

##
## *****************************
## 4: copy_hex: 
##  copy the hex file to rtl directory

.PHONY: copy_hex
copy_hex:
	cp $(HEX_FILE) $(RTL_DIR)


help: Makefile

	@sed -n 's/^##//p' $<

