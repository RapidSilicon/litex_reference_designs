
build/AXI_RAM.elf:     file format elf32-littleriscv


Disassembly of section .vector:

00000000 <crtStart>:
.global crtStart
.global main
.global irqCallback

crtStart:
  j crtInit
   0:	0b00006f          	j	b0 <crtInit>
  nop
   4:	00000013          	nop
  nop
   8:	00000013          	nop
  nop
   c:	00000013          	nop
  nop
  10:	00000013          	nop
  nop
  14:	00000013          	nop
  nop
  18:	00000013          	nop
  nop
  1c:	00000013          	nop

00000020 <trap_entry>:

.global  trap_entry
trap_entry:
  sw x1,  - 1*4(sp)
  20:	fe112e23          	sw	ra,-4(sp)
  sw x5,  - 2*4(sp)
  24:	fe512c23          	sw	t0,-8(sp)
  sw x6,  - 3*4(sp)
  28:	fe612a23          	sw	t1,-12(sp)
  sw x7,  - 4*4(sp)
  2c:	fe712823          	sw	t2,-16(sp)
  sw x10, - 5*4(sp)
  30:	fea12623          	sw	a0,-20(sp)
  sw x11, - 6*4(sp)
  34:	feb12423          	sw	a1,-24(sp)
  sw x12, - 7*4(sp)
  38:	fec12223          	sw	a2,-28(sp)
  sw x13, - 8*4(sp)
  3c:	fed12023          	sw	a3,-32(sp)
  sw x14, - 9*4(sp)
  40:	fce12e23          	sw	a4,-36(sp)
  sw x15, -10*4(sp)
  44:	fcf12c23          	sw	a5,-40(sp)
  sw x16, -11*4(sp)
  48:	fd012a23          	sw	a6,-44(sp)
  sw x17, -12*4(sp)
  4c:	fd112823          	sw	a7,-48(sp)
  sw x28, -13*4(sp)
  50:	fdc12623          	sw	t3,-52(sp)
  sw x29, -14*4(sp)
  54:	fdd12423          	sw	t4,-56(sp)
  sw x30, -15*4(sp)
  58:	fde12223          	sw	t5,-60(sp)
  sw x31, -16*4(sp)
  5c:	fdf12023          	sw	t6,-64(sp)
  addi sp,sp,-16*4
  60:	fc010113          	addi	sp,sp,-64
  call irqCallback
  64:	0dc000ef          	jal	ra,140 <irqCallback>
  lw x1 , 15*4(sp)
  68:	03c12083          	lw	ra,60(sp)
  lw x5,  14*4(sp)
  6c:	03812283          	lw	t0,56(sp)
  lw x6,  13*4(sp)
  70:	03412303          	lw	t1,52(sp)
  lw x7,  12*4(sp)
  74:	03012383          	lw	t2,48(sp)
  lw x10, 11*4(sp)
  78:	02c12503          	lw	a0,44(sp)
  lw x11, 10*4(sp)
  7c:	02812583          	lw	a1,40(sp)
  lw x12,  9*4(sp)
  80:	02412603          	lw	a2,36(sp)
  lw x13,  8*4(sp)
  84:	02012683          	lw	a3,32(sp)
  lw x14,  7*4(sp)
  88:	01c12703          	lw	a4,28(sp)
  lw x15,  6*4(sp)
  8c:	01812783          	lw	a5,24(sp)
  lw x16,  5*4(sp)
  90:	01412803          	lw	a6,20(sp)
  lw x17,  4*4(sp)
  94:	01012883          	lw	a7,16(sp)
  lw x28,  3*4(sp)
  98:	00c12e03          	lw	t3,12(sp)
  lw x29,  2*4(sp)
  9c:	00812e83          	lw	t4,8(sp)
  lw x30,  1*4(sp)
  a0:	00412f03          	lw	t5,4(sp)
  lw x31,  0*4(sp)
  a4:	00012f83          	lw	t6,0(sp)
  addi sp,sp,16*4
  a8:	04010113          	addi	sp,sp,64
  mret
  ac:	30200073          	mret

000000b0 <crtInit>:
crtInit:
 /* .option push
  .option norelax
  la gp, __global_pointer$
  .option pop*/
  la sp, _stack_start
  b0:	57000113          	li	sp,1392

000000b4 <bss_init>:

bss_init:
  la a0, _bss_start
  b4:	17000513          	li	a0,368
  la a1, _bss_end
  b8:	17000593          	li	a1,368

000000bc <bss_loop>:
bss_loop:
  beq a0,a1,bss_done
  bc:	00b50863          	beq	a0,a1,cc <bss_done>
  sw zero,0(a0)
  c0:	00052023          	sw	zero,0(a0)
  add a0,a0,4
  c4:	00450513          	addi	a0,a0,4
  j bss_loop
  c8:	ff5ff06f          	j	bc <bss_loop>

000000cc <bss_done>:
bss_done:

ctors_init:
  la a0, _ctors_start
  cc:	16c00513          	li	a0,364
  addi sp,sp,-4
  d0:	ffc10113          	addi	sp,sp,-4

000000d4 <ctors_loop>:
ctors_loop:
  la a1, _ctors_end
  d4:	16c00593          	li	a1,364
  beq a0,a1,ctors_done
  d8:	00b50e63          	beq	a0,a1,f4 <ctors_done>
  lw a3,0(a0)
  dc:	00052683          	lw	a3,0(a0)
  add a0,a0,4
  e0:	00450513          	addi	a0,a0,4
  sw a0,0(sp)
  e4:	00a12023          	sw	a0,0(sp)
  jalr  a3
  e8:	000680e7          	jalr	a3
  lw a0,0(sp)
  ec:	00012503          	lw	a0,0(sp)
  j ctors_loop
  f0:	fe5ff06f          	j	d4 <ctors_loop>

000000f4 <ctors_done>:
ctors_done:
  addi sp,sp,4
  f4:	00410113          	addi	sp,sp,4


  li a0, 0x880     //880 enable timer + external interrupts
  f8:	00001537          	lui	a0,0x1
  fc:	88050513          	addi	a0,a0,-1920 # 880 <_stack_start+0x310>
  csrw mie,a0
 100:	30451073          	csrw	mie,a0
  li a0, 0x1808     //1808 enable interrupts
 104:	00002537          	lui	a0,0x2
 108:	80850513          	addi	a0,a0,-2040 # 1808 <_stack_start+0x1298>
  csrw mstatus,a0
 10c:	30051073          	csrw	mstatus,a0

  call main
 110:	034000ef          	jal	ra,144 <main>

00000114 <infinitLoop>:
infinitLoop:
  j infinitLoop
 114:	0000006f          	j	114 <infinitLoop>

Disassembly of section .memory:

00000118 <AXI_CDMA_TEST>:
static inline u32 read_u32(u32 address){
    return *((volatile u32*) address);
}

static inline void write_u32(u32 data, u32 address){
    *((volatile u32*) address) = data;
 118:	100007b7          	lui	a5,0x10000
 11c:	00002623          	sw	zero,12(zero) # c <regnum_a2>
 120:	30078793          	addi	a5,a5,768 # 10000300 <_stack_start+0xffffd90>
 124:	00f02a23          	sw	a5,20(zero) # 14 <regnum_s4>
 128:	10000793          	li	a5,256
 12c:	00f02e23          	sw	a5,28(zero) # 1c <regnum_t3>
 130:	01500793          	li	a5,21
 134:	00f02223          	sw	a5,4(zero) # 4 <regnum_tp>
    return *((volatile u32*) address);
 138:	00002783          	lw	a5,0(zero) # 0 <_heap_size>
 13c:	00100073          	ebreak

00000140 <irqCallback>:
	while((read_u32(R_AXIDMACTRL) & DMA_BUSY_BIT)==0);

}
void irqCallback(int irq){

}
 140:	00008067          	ret

Disassembly of section .text.startup:

00000144 <main>:
 144:	100007b7          	lui	a5,0x10000
 148:	00002623          	sw	zero,12(zero) # c <regnum_a2>
 14c:	30078793          	addi	a5,a5,768 # 10000300 <_stack_start+0xffffd90>
 150:	00f02a23          	sw	a5,20(zero) # 14 <regnum_s4>
 154:	10000793          	li	a5,256
 158:	00f02e23          	sw	a5,28(zero) # 1c <regnum_t3>
 15c:	01500793          	li	a5,21
 160:	00f02223          	sw	a5,4(zero) # 4 <regnum_tp>
 164:	00002783          	lw	a5,0(zero) # 0 <_heap_size>
 168:	00100073          	ebreak
