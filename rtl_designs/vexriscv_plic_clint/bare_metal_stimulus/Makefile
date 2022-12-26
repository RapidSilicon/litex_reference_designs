# Set it to yes if you are using the sifive precompiled GCC pack
SIFIVE_GCC_PACK ?= yes
PROJ_NAME=VEX_SOC_PLIC_CLINT
DEBUG=no
BENCH=no
MULDIV?=yes
LDSCRIPT = ./libs/simple.ld

SRCS = 	$(wildcard src/*.c)  \
	$(wildcard src/*.S)

ifeq ($(SIFIVE_GCC_PACK),yes)
	RISCV_NAME ?= riscv64-unknown-elf
	RISCV_PATH ?= /opt/riscv/
else
	RISCV_NAME ?= riscv32-unknown-elf
	ifeq ($(MULDIV),yes)
		RISCV_PATH ?= /opt/riscv32im/
	else
		RISCV_PATH ?= /opt/riscv32i/
	endif
endif

MABI=ilp32
MARCH := rv32i
ifeq ($(MULDIV),yes)
	MARCH := $(MARCH)m
endif
ifeq ($(COMPRESSED),yes)
	MARCH := $(MARCH)ac
endif

CFLAGS += -march=$(MARCH)  -mabi=$(MABI)
LDFLAGS += -march=$(MARCH)  -mabi=$(MABI)


ifeq ($(DEBUG),yes)
	CFLAGS += -g3 -O0 
endif

ifeq ($(DEBUG),no)
	CFLAGS += -g -O3 
endif

ifeq ($(BENCH),yes)
	CFLAGS += -fno-inline  
endif

ifeq ($(SIFIVE_GCC_PACK),yes)
	RISCV_CLIB=$(RISCV_PATH)/$(RISCV_NAME)/lib/$(MARCH)/$(MABI)/
else
	RISCV_CLIB=$(RISCV_PATH)/$(RISCV_NAME)/lib/
endif





RISCV_OBJCOPY = $(RISCV_PATH)/bin/$(RISCV_NAME)-objcopy
RISCV_OBJDUMP = $(RISCV_PATH)/bin/$(RISCV_NAME)-objdump
RISCV_CC=$(RISCV_PATH)/bin/$(RISCV_NAME)-gcc

CFLAGS +=  -MD -fstrict-volatile-bitfields 
LDFLAGS +=  -nostdlib -lgcc -mcmodel=medany -nostartfiles -ffreestanding -Wl,-Bstatic,-T,$(LDSCRIPT),-Map,$(OBJDIR)/$(PROJ_NAME).map,--print-memory-usage

OBJDIR = build
OBJS := $(SRCS)
OBJS := $(OBJS:.c=.o)
OBJS := $(OBJS:.cpp=.o)
OBJS := $(OBJS:.S=.o)
OBJS := $(addprefix $(OBJDIR)/,$(OBJS))


all: $(OBJDIR)/$(PROJ_NAME).elf $(OBJDIR)/$(PROJ_NAME).hex $(OBJDIR)/$(PROJ_NAME).asm $(OBJDIR)/$(PROJ_NAME).v 
#riscv64-unknown-elf-elf2hex --bit-width 32 --input ./build/$(PROJ_NAME).elf --output ./build/$(PROJ_NAME)_32.hex
	

$(OBJDIR)/%.elf: $(OBJS) | $(OBJDIR)
	$(RISCV_CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

%.hex: %.elf
	$(RISCV_OBJCOPY) -O ihex $^ $@

%.bin: %.elf
	$(RISCV_OBJCOPY) -O binary $^ $@
	
%.v: %.elf
	$(RISCV_OBJCOPY) -O verilog $^ $@
	
	
	
%.asm: %.elf
	$(RISCV_OBJDUMP) -S -d $^ > $@

$(OBJDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(RISCV_CC) -c $(CFLAGS)  $(INC) -o $@ $^
	
$(OBJDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(RISCV_CC) -c $(CFLAGS)  $(INC) -o $@ $^	

$(OBJDIR)/%.o: %.S
	mkdir -p $(dir $@)
	$(RISCV_CC) -c $(CFLAGS) -o $@ $^ -D__ASSEMBLY__=1

$(OBJDIR):
	mkdir -p $@
# The below conversion is successful with the riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14 toolchain as tested.



# Make sure to put this new formed .hex file into the "readmemh" block in the instruction AXI_RAM named as axi_ram.v

clean:
	rm -f $(OBJDIR)/$(PROJ_NAME).elf
	rm -f $(OBJDIR)/$(PROJ_NAME).hex
	rm -f $(OBJDIR)/$(PROJ_NAME).map
	rm -f $(OBJDIR)/$(PROJ_NAME).v
	rm -f $(OBJDIR)/$(PROJ_NAME).asm
	find $(OBJDIR) -type f -name '*.o' -print0 | xargs -0 -r rm

.SECONDARY: $(OBJS)

# Type out the following command to initiate VCS for the design

# vcs -ignore initializer_driver_checks testbench.v vex_soc_neat.v axi_ram.v VexRiscvAxi4.v axi4_interconnect.v axi_interconnect.v arbiter.v priority_encoder.v axi_ram_per.v -sverilog -debug_all -full64 +vcs+lic+wait && ./simv
 

