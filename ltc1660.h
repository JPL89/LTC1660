// @File		LTC1660.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		22/05/23
//
//
// Copyright (C) 2023 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#ifndef LTC1660_H
#define LTC1660_H

#define LTC1660_SCK PORTCbits.RC0    
#define LTC1660_CS PORTCbits.RC1    
#define LTC1660_DIN PORTCbits.RC2    
#define LTC1660_CLR PORTCbits.RC3    
#define LTC1660_DOUT PORTCbits.RC4    

#define LTC1660_SCK_TRIS TRISCbits.RC0    
#define LTC1660_CS_TRIS TRISCbits.RC1    
#define LTC1660_DIN_TRIS TRISCbits.RC2    
#define LTC1660_CLR_TRIS TRISCbits.RC3    
#define LTC1660_DOUT_TRIS TRISCbits.RC4  

static void Spi_write(unsigned int data)
{
    for(unsigned int mask = 0x8000; mask; mask >>= 1)
    {
        if(data & mask) LTC1660_DIN = 1;
        else LTC1660_DIN = 0; 
        
        LTC1660_SCK = 1;
        __asm__ __volatile__("nop");
        LTC1660_SCK = 0;
        __asm__ __volatile__("nop");      
    }
}

void LTC1660_Write(unsigned char address, unsigned int code)
{
    unsigned int data = 0;
    
    // A3, A2, A1, A0
    data |= (address << 12);
    
    // D9, D8, D7, D6, D5, D4, D3, D2, D1, D0
    // X1, X0
    data |= (code << 2);
    
    LTC1660_CS = 0;    
    Spi_write(data);    
    LTC1660_CS = 1;
}

void LTC1660_Init(void)
{
    LTC1660_SCK_TRIS = 0;
    LTC1660_CS_TRIS = 0;
    LTC1660_DIN_TRIS = 0;
    LTC1660_CLR_TRIS = 0;
    LTC1660_DOUT_TRIS = 1;
    
    LTC1660_CS = 1;
}

#endif // LTC1660
