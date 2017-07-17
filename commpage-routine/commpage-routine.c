/**
 * commpage-routine
 * Copyright (C) 2017 NOP 0xe1a00000
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
 * movabsq $0x7fffffe000d0, %rax
 * retq
 */
u_char hex_ins[] = {
    0x48,
    0xb8,
    0xd0,
    0x00,
    0xe0,
    0xff,
    0xff,
    0x7f,
    0x00,
    0x00,
    0xc3 // len 0xb
};

uint64_t
find_commpage_hello(uint64_t address)
{
    uint64_t max = address + 0x1000 - 0xb;
    for ( ; address < max; address++)
    {
        bool found = false;
        for (int i = 0; i < 0xb; i++)
        {
            u_char ins = *(u_char *)(address + i);
            if (ins != hex_ins[i])
            {
                break;
            }
            
            if (i == 0xa)
            {
                found = true;
            }
        }
        
        if (found)
        {
            return address;
        }
    }
    
    return 0;
}

int
main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: commpage-routine COMMPAGE_TEXT_START_ADDRESS\n");
        return -1;
    }
    
    uint64_t text_address = strtouq(argv[1], NULL, 0);
    if (0 == text_address)
    {
        printf("[*] Couldn't perform address conversion.\n");
        return -1;
    }
    
    
    uint64_t routine_address = find_commpage_hello(text_address);
    if (0 == routine_address)
    {
        printf("[*] Couldn't find hello commpage routine.\n");
        return -1;
    }
    
    printf("[*] Found hello commpage routine at address 0x%016llx\n", routine_address);
    printf("[*] Routine returns '%s'\n", ((char * (*)())routine_address)());

    return 0;
}
