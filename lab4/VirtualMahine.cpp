#include <cstdint>
#include "Assembly.cpp"

class VirtualMachine
{
public:
    VirtualMachine()
    {
        running = false;
        reg[R_COND] = FL_ZRO;
        reg[R_PC] = 0x3000;
    }
    enum
    {
        R_R0 = 0,
        R_R1,
        R_R2,
        R_R3,
        R_R4,
        R_R5,
        R_R6,
        R_R7,
        R_PC, /* program counter */
        R_COND,
        R_COUNT
    };
    enum
    {
        OP_ADD = 1,    /* add  */
        OP_LD,     /* load */
        OP_AND,    /* bitwise and */
        OP_NOT,    /* bitwise not */
        OP_JMP,    /* jump */
        OP_PRINT   /* print */
    };
    enum
    {
        FL_POS = 1 << 0,
        FL_ZRO = 1 << 1,
        FL_NEG = 1 << 2,
    };

    void run()
    {
        running = true;
        while (running)
        {
            std::string input;
            std::getline(std::cin, input);
            uint16_t instr = assembly.convert(input);
            uint16_t op = instr >> 12;

            switch (op)
            {
                case OP_ADD:
                {
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t r1 = (instr >> 6) & 0x7;
                    uint16_t r2 = instr & 0x7;
                    reg[r0] = reg[r1] + reg[r2];

                    update_flags(r0);
                    break;
                }
                case OP_LD:
                {
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t value = sign_extend(instr & 0x1FF, 9);
                    reg[r0] = value;
                    update_flags(r0);
                    break;
                }
                case OP_AND:
                {
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t r1 = (instr >> 6) & 0x7;
                    uint16_t r2 = instr & 0x7;
                    reg[r0] = reg[r1] & reg[r2];
                    update_flags(r0);
                    break;
                }
                case OP_NOT:
                {
                    uint16_t r0 = (instr >> 9) & 0x7;
                    uint16_t r1 = (instr >> 6) & 0x7;

                    reg[r0] = ~reg[r1];
                    update_flags(r0);
                    break;
                }
                case OP_JMP:
                {
                    uint16_t r1 = (instr >> 6) & 0x7;
                    reg[R_PC] = reg[r1];
                    break;
                }
                case OP_PRINT:
                {
                    uint16_t r0 = instr & 0x7;
                    std::cout << reg[r0] << '\n';
                    break;
                }
            }
        }
    }

private:

    void update_flags(uint16_t r)
    {
        if (reg[r] == 0)
        {
            reg[R_COND] = FL_ZRO;
        }
        else if (reg[r] >> 15) /* a 1 in the left-most bit indicates negative */
        {
            reg[R_COND] = FL_NEG;
        }
        else
        {
            reg[R_COND] = FL_POS;
        }
    }

    uint16_t sign_extend(uint16_t x, int bit_count)
    {
        if ((x >> (bit_count - 1)) & 1) {
            x |= (0xFFFF << bit_count);
        }
        return x;
    }

    uint16_t reg[R_COUNT];
    bool running;
    Assembly assembly;
    

};