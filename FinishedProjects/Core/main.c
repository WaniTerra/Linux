#include <stdio.h>
#include <stdint.h>

uint8_t memory[256];
uint16_t registers[4];
uint16_t pc = 0;

void execute_cycle()
{
    uint16_t instruction = (memory[pc] << 8) | memory[pc + 1];
    pc += 2;

    uint16_t opcode = (instruction & 0xF000) >> 12;
    uint16_t reg1 = (instruction & 0x0F00) >> 8;
    uint16_t reg2 = (instruction & 0x00F0) >> 4;

    if (opcode == 0x1)
    {
        registers[reg1] = registers[reg1] + registers[reg2];
    }
}

int main()
{
    registers[0] = 15;
    registers[1] = 25;

    memory[0] = 0x10;
    memory[1] = 0x10;

    printf("Before CPU Cycle -> R0: %d\n", registers[0]);

    execute_cycle();

    printf("After CPU Cycle  -> R0: %d\n", registers[0]);

    return 0;
}