__initial_sp        EQU     0x10001000  ; Top of RAM from LPC11U

                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler



                AREA    |.text|, CODE, READONLY

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  __main
                LDR     R0, =__main
                BX      R0
                ENDP

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP

HardFault_Handler     PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP

MemManage_Handler     PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP

BusFault_Handler     PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP

UsageFault_Handler     PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP

SVC_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP

DebugMon_Handler     PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP

PendSV_Handler     PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP

SysTick_Handler     PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP


                ALIGN
                END

