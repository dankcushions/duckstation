/***************************************************************************
 *   Original copyright notice from PGXP code from Beetle PSX.             *
 *   Copyright (C) 2016 by iCatButler                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.           *
 ***************************************************************************/

#pragma once
#include "types.h"

namespace PGXP {

#define PGXP_MODE_NONE 0

#define PGXP_MODE_MEMORY (1 << 0)
#define PGXP_MODE_CPU (1 << 1)
#define PGXP_MODE_GTE (1 << 2)

#define PGXP_VERTEX_CACHE (1 << 4)
#define PGXP_TEXTURE_CORRECTION (1 << 5)

void PGXP_Init(); // initialise memory
void PGXP_InitGTE();
void PGXP_InitMem();
void PGXP_InitCPU();

void PGXP_SetModes(u32 modes);
u32 PGXP_GetModes();
void PGXP_EnableModes(u32 modes);
void PGXP_DisableModes(u32 modes);

static inline int PGXP_enabled(void)
{
  return (PGXP_GetModes() & (PGXP_MODE_MEMORY | PGXP_VERTEX_CACHE)) != 0;
}

// -- GTE functions
// Transforms
void PGXP_pushSXYZ2f(float _x, float _y, float _z, unsigned int _v);
void PGXP_pushSXYZ2s(s64 _x, s64 _y, s64 _z, u32 v);

void PGXP_RTPS(u32 _n, u32 _v);

int PGXP_NLCIP_valid(u32 sxy0, u32 sxy1, u32 sxy2);
float PGXP_NCLIP();

// Data transfer tracking
void PGXP_GTE_MFC2(u32 instr, u32 rtVal, u32 rdVal); // copy GTE data reg to GPR reg (MFC2)
void PGXP_GTE_MTC2(u32 instr, u32 rdVal, u32 rtVal); // copy GPR reg to GTE data reg (MTC2)
void PGXP_GTE_CFC2(u32 instr, u32 rtVal, u32 rdVal); // copy GTE ctrl reg to GPR reg (CFC2)
void PGXP_GTE_CTC2(u32 instr, u32 rdVal, u32 rtVal); // copy GPR reg to GTE ctrl reg (CTC2)
// Memory Access
void PGXP_GTE_LWC2(u32 instr, u32 rtVal, u32 addr); // copy memory to GTE reg
void PGXP_GTE_SWC2(u32 instr, u32 rtVal, u32 addr); // copy GTE reg to memory

bool PGXP_GetVertex(u32 addr, u32 value, int x, int y, int xOffs, int yOffs, float* out_x, float* out_y, float* out_w);

// -- CPU functions
void PGXP_CPU_LW(u32 instr, u32 rtVal, u32 addr);
void PGXP_CPU_LH(u32 instr, u16 rtVal, u32 addr);
void PGXP_CPU_LHU(u32 instr, u16 rtVal, u32 addr);
void PGXP_CPU_LB(u32 instr, u8 rtVal, u32 addr);
void PGXP_CPU_LBU(u32 instr, u8 rtVal, u32 addr);
void PGXP_CPU_SB(u32 instr, u8 rtVal, u32 addr);
void PGXP_CPU_SH(u32 instr, u16 rtVal, u32 addr);
void PGXP_CPU_SW(u32 instr, u32 rtVal, u32 addr);

} // namespace PGXP