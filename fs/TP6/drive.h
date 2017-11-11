#ifndef DRIVE_H_INCLUDED
#define DRIVE_H_INCLUDED
#include<stdio.h>
#include<stdlib.h>
#define HDA_SECTORSIZE 256
#define HDA_DATAREG 0x110
#define HDA_CMDREG 0x3F6
#define HDA_IRQ 14
#define TIMER_PARAM 0xF4
#define TIMER_ALARM 0xF8

void seek(unsigned int cyl,unsigned int sec);
void read_sector(unsigned int cyl,unsigned int sec,unsigned char *buffer);
void write_sector(unsigned int cyl,unsigned int sec,unsigned char *buffer);
void format_sector(unsigned int cyl,unsigned int sec,unsigned int nsec, unsigned int val);

#endif
