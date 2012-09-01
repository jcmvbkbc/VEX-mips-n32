
/*---------------------------------------------------------------*/
/*--- begin                                   libvex_emnote.h ---*/
/*---------------------------------------------------------------*/

/*
   This file is part of Valgrind, a dynamic binary instrumentation
   framework.

   Copyright (C) 2004-2012 OpenWorks LLP
      info@open-works.net

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA.

   The GNU General Public License is contained in the file COPYING.

   Neither the names of the U.S. Department of Energy nor the
   University of California nor the names of its contributors may be
   used to endorse or promote products derived from this software
   without prior written permission.
*/

#ifndef __LIBVEX_EMNOTE_H
#define __LIBVEX_EMNOTE_H


/* VEX can sometimes generate code which returns to the dispatcher
   with the guest state pointer set to VEX_TRC_JMP_EMWARN or 
   VEX_TRC_JMP_EMFAIL.  This means that VEX is trying to tell Valgrind
   something noteworthy about emulation progress. For example, that Valgrind
   is doing imprecise emulation in some sense.  The guest's pseudo-register
   "guest_EMNOTE" will hold a value of type VexEmNote, which describes
   the nature of the warning.  Currently the limitations that are
   warned about apply primarily to floating point support.

   All guest states must have a 32-bit (UInt) guest_EMNOTE pseudo-
   register, that emulation warnings can be written in to.

   Note that guest_EMNOTE only carries a valid value at the jump
   marked as VEX_TRC_JMP_EMWARN / VEX_TRC_JMP_EMFAIL.  You can't assume
   it will continue to carry a valid value from any amount of time after
   the jump.
*/

typedef
   enum {
      /* no note indicated */
      EmNote_NONE=0,

      /* unmasking x87 FP exceptions is not supported */
      EmWarn_X86_x87exns,

      /* change of x87 FP precision away from 64-bit (mantissa) */
      EmWarn_X86_x87precision,

      /* unmasking SSE FP exceptions is not supported */
      EmWarn_X86_sseExns,
      
      /* setting mxcsr.fz is not supported */
      EmWarn_X86_fz,
      
      /* setting mxcsr.daz is not supported */
      EmWarn_X86_daz,

      /* settings to %eflags.ac (alignment check) are noted but ignored */
      EmWarn_X86_acFlag,
      
      /* unmasking PPC32/64 FP exceptions is not supported */
      EmWarn_PPCexns,

      /* overflow/underflow of the PPC64 _REDIR stack (ppc64 only) */
      EmWarn_PPC64_redir_overflow,
      EmWarn_PPC64_redir_underflow,

      /* stfle insn is not supported on this host */
      EmFail_S390X_stfle,

      /* stckf insn is not supported on this host */
      EmFail_S390X_stckf,

      /* ecag insn is not supported on this host */
      EmFail_S390X_ecag,

      /* insn needs floating point extension facility which is not
         available on this host */
      EmFail_S390X_fpext,

      EmNote_NUMBER
   }
   VexEmNote;


/* Produces a short string describing the warning. */
extern HChar* LibVEX_EmNote_string ( VexEmNote );


#endif /* ndef __LIBVEX_EMNOTE_H */

/*---------------------------------------------------------------*/
/*---                                         libvex_emnote.h ---*/
/*---------------------------------------------------------------*/
