;
; module name       : c7x_mmu
;
; module descripton : MMU page table, cache enable operations
;
; Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
;
; ALL RIGHTS RESERVED
;

	.global CSL_c7xSetTCR0
CSL_c7xSetTCR0:
	MVC	.S1	A4,		ECR785		;; Table Control Register 0
	RET	.B1



	.global CSL_c7xSetTBR0
CSL_c7xSetTBR0:
	MVC	.S1	A4,		ECR787		;; Table Base Register 0
	RET	.B1



	.global CSL_c7xSetMAR
CSL_c7xSetMAR:
	MVC	.S1	A4,		ECR789		;; Memory Attribute Register
	RET	.B1



	.global CSL_c7xSetSCR
CSL_c7xSetSCR:
	MVC	.S1	A4,		ECR784		;; System Control Register
	RET	.B1



	.global CSL_c7xSetL1DCFG
CSL_c7xSetL1DCFG:
	MVC .S1 A4,     ECR256      ;; L1D Cache Configuration Register
	RET .B1



	.global CSL_c7xGetL1DCFG
CSL_c7xGetL1DCFG:
	MVC .S1 ECR256, A4  ;; L1D Cache Configuration Register
	RET .B1
