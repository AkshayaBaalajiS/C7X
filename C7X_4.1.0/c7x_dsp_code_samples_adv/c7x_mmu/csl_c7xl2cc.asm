;
; module name       : c7x_mmu
;
; module descripton : MMU page table, cache enable operations
;
; Copyright (C) 2015-2019 Texas Instruments Incorporated - http://www.ti.com/
;
; ALL RIGHTS RESERVED
;

    .global CSL_c7xSetL2CC
CSL_c7xSetL2CC:
    MVC .S1 A4,     ECR385      ;; L2 Cache Control Register
    RET .B1



    .global CSL_c7xGetL2CC
CSL_c7xGetL2CC:
    MVC .S1 ECR385, A4  ;; L2 Cache Control Register
    RET .B1
