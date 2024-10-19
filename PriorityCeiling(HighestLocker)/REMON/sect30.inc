;/*********************************************************************
;*
;* Device     : M16C/60,30,20,10
;*
;* File Name  : sect30.inc
;*
;* Abstract   : Section definition for M16C/60,30,20,10
;*
;* History    : 1.20  (2009-01-26)
;*
;* Copyright (C) 2009 (2010) Renesas Electronics Corporation.
;* and Renesas Solutions Corporation. All rights reserved.
;*
;*********************************************************************/

;=====================================================================
;
; 	Arrangement of section
;
;---------------------------------------------------------------------
; Near RAM data area
;---------------------------------------------------------------------
; SBDATA area
		.section	data_SE,DATA
		.org		400H
data_SE_top:

		.section	bss_SE,DATA,ALIGN
bss_SE_top:

		.section	data_SO,DATA
data_SO_top:

		.section	bss_SO,DATA
bss_SO_top:

; SBDATA area definition
		.glb		__SB__
__SB__	.equ		data_SE_top

; near RAM area
		.section	data_NE,DATA,ALIGN
data_NE_top:

		.section	bss_NE,DATA,ALIGN
bss_NE_top:

		.section	data_NO,DATA
data_NO_top:

		.section	bss_NO,DATA
bss_NO_top:

;---------------------------------------------------------------------
; Stack area
;---------------------------------------------------------------------
		.section	istack,DATA,ALIGN
		.blkb		__ISTACKSIZE__
istack_top:

.if __STACKSIZE__ != 0
		.section	stack,DATA,ALIGN
		.blkb		__STACKSIZE__
stack_top:
.endif

;---------------------------------------------------------------------
; heap section
;---------------------------------------------------------------------
.if __HEAPSIZE__ != 0
		.section	heap,DATA
heap_top:
		.blkb		__HEAPSIZE__
.endif

;---------------------------------------------------------------------
; Near ROM data area
;---------------------------------------------------------------------
.if __NEAR_ROM_FLG__ != 0
		.section	rom_NE,ROMDATA,ALIGN
rom_NE_top:

		.section	rom_NO,ROMDATA
rom_NO_top:
.endif

;---------------------------------------------------------------------
; Far RAM data area
;---------------------------------------------------------------------
.if __FAR_RAM_FLG__ != 0
		.section	data_FE,DATA
		.org		10000H
data_FE_top:

		.section	bss_FE,DATA,ALIGN
bss_FE_top:

		.section	data_FO,DATA
data_FO_top:

		.section	bss_FO,DATA
bss_FO_top:
.endif

;---------------------------------------------------------------------
; Far ROM data area
;---------------------------------------------------------------------
		.section	rom_FE,ROMDATA
		.org		__ROM_TOPADR__
rom_FE_top:

		.section	rom_FO,ROMDATA
rom_FO_top:

;---------------------------------------------------------------------
; Initial data of 'data' section
;---------------------------------------------------------------------
		.section	data_SEI,ROMDATA,ALIGN
data_SEI_top:

		.section	data_SOI,ROMDATA
data_SOI_top:

		.section	data_NEI,ROMDATA,ALIGN
data_NEI_top:
 
		.section	data_NOI,ROMDATA
data_NOI_top:

.if __FAR_RAM_FLG__ != 0
		.section	data_FEI,ROMDATA,ALIGN
data_FEI_top:

		.section	data_FOI,ROMDATA
data_FOI_top:
.endif

;---------------------------------------------------------------------
; Switch Table Section
;---------------------------------------------------------------------
;		.section	switch_table,ROMDATA
;switch_table_top:

;---------------------------------------------------------------------
; code area
;---------------------------------------------------------------------
		.section	program,CODE,ALIGN
		.section	interrupt,CODE,ALIGN
		.section	program_S,CODE,ALIGN

;---------------------------------------------------------------------
; variable vector section
;---------------------------------------------------------------------
		.section	vector,ROMDATA
		.org		__VECTOR_ADR__

	.lword	dummy_int		; BRK	(vector 0)
	.lword	dummy_int		; 	(vector 1)
	.lword	dummy_int		; 	(vector 2)
	.lword	dummy_int		; 	(vector 3)
	.lword	dummy_int		; int3(for user)(vector 4)
	.lword	dummy_int		; timerB5(for user)(vector 5)
	.lword	dummy_int		; timerB4(for user)(vector 6)
	.lword	dummy_int		; timerB3(for user)(vector 7)
	.lword	dummy_int		; si/o4 /int5(for user)(vector 8)
	.lword	dummy_int		; si/o3 /int4(for user)(vector 9)
	.lword	dummy_int		; Bus collision detection(for user)(v10)
	.lword	dummy_int		; DMA0(for user)(vector 11)
	.lword	dummy_int		; DMA1(for user)(vector 12)
	.lword	dummy_int		; Key input interrupt(for user)(vect 13)
	.lword	dummy_int		; A-D(for user)(vector 14)
	.lword	dummy_int		; uart2 transmit(for user)(vector 15)
	.lword	dummy_int		; uart2 receive(for user)(vector 16)
	.lword	dummy_int		; uart0 transmit(for user)(vector 17)
	.lword	dummy_int		; uart0 receive(for user)(vector 18)
	.lword	0fcb6bh			; uart1 transmit(for user)(vector 19)
	.lword	0fcb6bh			; uart1 receive(for user)(vector 20)
	
;	.lword	dummy_int		; vector 21  (for user) timer A0
	.glb	_ta0int
	.lword	_ta0int			; timer A0(for user)(vector 21)
;	.lword	dummy_int		; vector 22  (for user) timer A1
	.glb	_ta1int
	.lword	_ta1int			; timer A0(for user)(vector 22)
	
	.lword	dummy_int		; timer A2(for user)(vector 23)
	.lword	dummy_int		; timer A3(for user)(vector 24)
	.lword	dummy_int		; timer A4(for user)(vector 25)
	.lword	dummy_int		; timer B0(for user)(vector 26)
	.lword	dummy_int		; timer B1(for user)(vector 27)
	.lword	dummy_int		; timer B2(for user)(vector 28)

	.lword	dummy_int		; int0 (for user)(vector 29)
;	.glb	_int0
;	.lword	_int0			; int0 (for user)(vector 29)

	.lword	dummy_int		; int1 (for user)(vector 30)
;	.glb	_int1
;	.lword	_int1			; int1 (for user)(vector 30)
	
	.lword	dummy_int		; int2 (for user)(vector 31)

	.glb	_svc_handler
	.lword	_svc_handler	; vector 32 (for user or MR30)
	.lword	_svc_handler	; vector 33 (for user or MR30)
	.lword	_svc_handler	; vector 34 (for user or MR30)
	.lword	_svc_handler	; vector 35 (for user or MR30)
	.lword	_svc_handler	; vector 36 (for user or MR30)
	.lword	_svc_handler	; vector 37 (for user or MR30)
	
	.lword	dummy_int		; vector 38 (for user or MR30)
	.lword	dummy_int		; vector 39 (for user or MR30)
	.lword	dummy_int		; vector 40 (for user or MR30)
	.lword	dummy_int		; vector 41 (for user or MR30)
	.lword	dummy_int		; vector 42 (for user or MR30)
	.lword	dummy_int		; vector 43 (for user or MR30)	
	.lword  dummy_int		; vector 44 (for user or MR30)
	.lword	dummy_int		; vector 45 (for user or MR30)
	.lword	dummy_int		; vector 46 (for user or MR30)
	.lword	dummy_int 		; vector 47 (for user or MR30)
	.lword	dummy_int 		; vector 48
	.lword	dummy_int 		; vector 49
	.lword	dummy_int 		; vector 50
	.lword	dummy_int 		; vector 51
	.lword	dummy_int 		; vector 52
	.lword	dummy_int 		; vector 53
	.lword	dummy_int 		; vector 54
	.lword	dummy_int 		; vector 55
	.lword	dummy_int 		; vector 56
	.lword	dummy_int 		; vector 57
	.lword	dummy_int 		; vector 58
	.lword	dummy_int 		; vector 59
	.lword	dummy_int 		; vector 60 
	.lword	dummy_int 		; vector 61
	.lword	dummy_int 		; vector 62
	.lword	dummy_int 		; vector 63

;---------------------------------------------------------------------
; for User Boot Code Area
; Please custumize this data for your setting.
;---------------------------------------------------------------------
.if 0
	.section _UB_section_FE,ROMDATA
	.org  013ff0H
	.byte 0FFh,0FFh,0FFh,0FFh,0FFh,0FFh,0FFh,0FFh ; User boot code
	.word 0FFFFh                                  ; Port address
	.byte 0FFh                                    ; Port bit
	.byte 0FFh                                    ; Boot level
	.byte 0FFh,0FFh,0FFh,0FFh                     ; Reserved
.endif

;---------------------------------------------------------------------
; fixed vector section
;---------------------------------------------------------------------
		.section	fvector,ROMDATA
		.org		0fffdcH
UDI:
		.lword		dummy_int
OVER_FLOW:
		.lword		dummy_int
BRKI:
		.lword		dummy_int
ADDRESS_MATCH:
		.lword		dummy_int
SINGLE_STEP:
		.lword		dummy_int
WDT:
		.lword		dummy_int
DBC:
		.lword		dummy_int
NMI:
		.lword		dummy_int
RESET:
		.lword	start

;=====================================================================
; ID code & ROM code protect
;---------------------------------------------------------------------
; ID code check function
		.id "#FFFFFFFFFFFFFF"

; ROM code protect control address
		; .protect 00H

;=====================================================================
; Initialize Macro declaration
;---------------------------------------------------------------------
N_BZERO	.macro		TOP_,SECT_
		mov.b		#00H,R0L
		mov.w		#(TOP_ & 0FFFFH),A1
		mov.w		#sizeof SECT_,R3
		sstr.b
		.endm

N_BCOPY .macro		FROM_,TO_,SECT_
		mov.w		#(FROM_ & 0FFFFH),A0
		mov.b		#(FROM_ >> 16),R1H
		mov.w		#TO_,A1
		mov.w		#sizeof SECT_,R3
		smovf.b
		.endm

BZERO	.macro		TOP_,SECT_
		push.w		#sizeof SECT_ >> 16
		push.w		#sizeof SECT_  & 0ffffh
		pusha		TOP_ >> 16
		pusha		TOP_ & 0ffffh
		.stk		8
		.glb		_bzero
		.call		_bzero,G
		jsr.a		_bzero
		.endm

BCOPY	.macro		FROM_ ,TO_ ,SECT_
		push.w		#sizeof SECT_  >> 16
		push.w		#sizeof SECT_  & 0ffffh
		pusha		TO_ >> 16
		pusha		TO_  & 0ffffh
		pusha		FROM_ >> 16
		pusha		FROM_  & 0ffffh
		.stk		12
		.glb		_bcopy
		.call   	_bcopy,G
		jsr.a		_bcopy
		.endm

