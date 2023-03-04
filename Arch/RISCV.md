> ref: [RISC-V bytes](https://danielmangum.com/categories/risc-v-bytes/)

## Basic

### 特权级

<img src="RISCV.assets/risc_v_priv_levels_1.png" style="zoom:30%;" />

PMP: Physical Memory Protection（introduced in RISC-V Priv 1.10）

HAL: hardware abstraction layer

ABI: Application Binary Interface

hart: hardware thread

CSR: control and status register

RISC-V的行为依赖它的执行环境。A RISC-V execution environment interface(EEI)定义了程序的初始状态，harts支持的特权级等。

> A RISC-V execution environment interface (EEI) defines the initial state of the program, the number
> and type of harts in the environment including the privilege modes supported by the harts, the accessibility and attributes of memory and I/O regions, the behavior of all legal instructions executed on each hart (i.e., the ISA is one component of the EEI), and the handling of any interrupts or exceptions raised during execution including environment calls.

典型的EEI包括：Linux application binary interface(ABI), RISC-V supervisor binary interface(SBI)

1. slli: logical left shift

2. lw & sw rs2 rs1

    load and store 32-bit values from the low bits of register rs2 from / to memory

## QEMU

why does qemu always start at 0x1000?

[answer](https://stackoverflow.com/a/72060395/16598178)

