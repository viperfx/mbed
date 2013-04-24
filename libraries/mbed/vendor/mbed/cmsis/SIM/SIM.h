/* 
 * A generic MCU, ideal for simple Simulation and FPGA implementation 
 */
 
 
#ifdef __cplusplus
#define     __I     volatile  
#else
#define     __I     volatile const
#endif
#define     __O     volatile      
#define     __IO    volatile      
 
#include <stdint.h>
 
typedef enum IRQn {
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
  NonMaskableInt_IRQn           = -14,      /*!< 2 Non Maskable Interrupt                         */
  MemoryManagement_IRQn         = -12,      /*!< 4 Cortex-M3 Memory Management Interrupt          */
  BusFault_IRQn                 = -11,      /*!< 5 Cortex-M3 Bus Fault Interrupt                  */
  UsageFault_IRQn               = -10,      /*!< 6 Cortex-M3 Usage Fault Interrupt                */
  SVCall_IRQn                   = -5,       /*!< 11 Cortex-M3 SV Call Interrupt                   */
  DebugMonitor_IRQn             = -4,       /*!< 12 Cortex-M3 Debug Monitor Interrupt             */
  PendSV_IRQn                   = -2,       /*!< 14 Cortex-M3 Pend SV Interrupt                   */
  SysTick_IRQn                  = -1,       /*!< 15 Cortex-M3 System Tick Interrupt               */
/******  MBED M3 Specific Interrupt Numbers *******************************************************/
  MCU_GPIO_IRQn                 = 0,   
  MCU_TIMER_IRQn                = 1,   
  MCU_RTC_IRQn                  = 2,
  MCU_UART_IRQn              = 3,
  MCU_SPI_IRQn                  = 4,
  MCU_I2C_IRQn                  = 5
} IRQn_Type;
 
/** GPIO 
 *  
 * A 32-bit GPIO port to drive outputs and read inputs/tigger interrupts
 *
 * DIR - direction of each pin, 0 is input, 1 is output; reset_state = 0
 * VAL - read for value of each pin (if pin is output, this reads as the value being driven)
 *       write for setting value of each pin (all 32-bits are registered, even if some are inputs so not seen on pin; if DIR was changed to output, you'd see this value)
 *       reset_state = 0
 * RED - Rising Edge Detect - 1 if a rising edge has been seen on this pin since last cleared, write 0 to clear, 1 ignored; reset_state = 0
 * FED - Falling Edge Detect - 1 if a falling edge has been seen on this pin since last cleared, write 0 to clear, 1 ignored  ; reset_state = 0
 * REI - Rising Edge Interrupt - if 1, an interrupt is triggered if a bit in RED changes from 0 to 1 ; reset_state = 0
 * FEI - Falling Edge Interrupt - if 1, an intterupt is triggered if a bit in FED changes from 0 to 1; reset_state = 0
 */ 
typedef struct {
    __IO uint32_t DIR; 
    __IO uint32_t VAL;
    __IO uint32_t RED;
    __IO uint32_t FED;
    __IO uint32_t REI;
    __IO uint32_t FEI;
} MCU_GPIO_TypeDef;
 
/** Timer 
 *  
 * A 32-bit timer which counts up when running, and can cause actions based on a match
 *
 * CONTROL - Control register for the timer; reset_state = 0
 *   RUN[0] - Run if 1, will cause counter to be active and incrementing
 *   IOM[1] - Interrupt on match if 1, will cause an interrupt when there is a match
 *   SOM[2] - Stop on match if 1, will cause RUN to be set to 0 when there is a match
 *   ROM[3] - Reset on match if 1, will cause COUNTER to be set to 0 when there is a match
 * PRESCALE - The prescale divider from the main system clock to the COUNTER. COUNTER is incremented every (PRESCALE + 1) system clocks (i.e. 0 is running at system clock speed). Reads the PRESCALE register, on write, the internal prescale counter is reset to 0; reset_state = 0
 * COUNTER - The active counter. Read the current value, write to set current value (internal prescale counter will be set to 0) ; reset_state = 0
 * MATCH - The match register, causing a match event if it matches COUNTER; reset_state = 0
 * Internal prescaler counter reset_state = 0
 */ 
typedef struct {
    __IO uint32_t CONTROL;
    __IO uint32_t PRESCALE;
    __IO uint32_t COUNTER;
    __IO uint32_t MATCH;                                    
} MCU_TIMER_TypeDef;
 
/** PWM
 *  
 * A continuous PWM output with adjustable period and pulsewidth
 *
 * CONTROL - Control register for the PWM; reset_state = 0
 *   RUN[0] - Run if 1, will cause PWM counter to be active and incrementing
 * PRESCALE - The prescale divider from the main system clock to the COUNTER. COUNTER is incremented every (PRESCALE + 1) system clocks (i.e. 0 is running at system clock speed). Reads the PRESCALE register, on write, the internal prescale counter is reset to 0; reset_state = 0
 * COUNTER - The active counter. Read the current value, write to set current value (internal prescale counter will be set to 0) ; reset_state = 0
 * PULSEWIDTH - Output will be high if COUNTER <= PULSEWIDTH, else low; reset_state = 0
 * PERIOD - On match with COUNTER, COUNTER will reset to 0 on next tick; reset_state = 0
 * Internal prescaler counter reset_state = 0
 */ 
typedef struct {
    __IO uint32_t CONTROL;
    __IO uint32_t PRESCALE;
    __IO uint32_t COUNTER;
    __IO uint32_t PULSEWIDTH;
    __IO uint32_t PERIOD;
} MCU_PWM_TypeDef;
 
/** RTC 
 *  
 * A 32-bit RTC representing time as unix timestamp
 *
 * CONTROL - Control register for the RTC; reset_state = 0
 *   RUN[0] - Run if 1, will cause clock to be active and incrementing
 *   IOM[1] - Interrupt on match if 1, will cause an interrupt when there is a match
 * TIMESTAMP - The active timestamp counter. Read the current value, write to set current value; reset_state = 0
 * MATCH - The match register, causing a match event if it matches TIMESTAMP; reset_state = 0
 */ 
typedef struct {
    __IO uint32_t CONTROL;
    __IO uint32_t TIMESTAMP;
    __IO uint32_t MATCH;    
} MCU_RTC_TypeDef;
 
/** UART
 *
 * CONTROL - Control register for the UART; reset_state = 0
 *   RXB[0] - True if character in available to read, writes ignored
 *   TXB[1] - True if space available to write character, writes ignored
 *   RXI[2] - Interrupt when character is available (RXB is 1)
 *   TXI[3] - Interrupt when character is sent (TXB is 1)
 * BAUDRATE - 19200 (Fixed), read only register.
 * VALUE - read a character (0 if none availble), write a character (bottom 8 bits)
 */
 
typedef struct {
    __IO uint32_t CONTROL;
    __IO uint32_t BAUDRATE;
    __IO  uint32_t VALUE;
} MBED_M3_UART_TypeDef;
 
/** ADC
 *  
 * A 16-bit ADC
 *
 * VALUE - Returns the input as an unsigned 16-bit value in lower half of 32-bit register
 */ 
typedef struct {
  __IO uint32_t VALUE;
} MCU_ADC_TypeDef;
 
/** DAC
 *  
 * A 16-bit DAC
 *
 * VALUE - Sets the output based on unsigned 16-bit value in lower half of 32-bit rgister
 */ 
typedef struct {
  __IO uint32_t VALUE;
} MCU_DAC_TypeDef;
 
 
/** SPI
 * STATUS - Status register for the SPI Master; 
 *   [0]BSY = True if SPI is busy transmitting data, 0 if idle.
 *
 * CONTROL - Control register for SPI Master, reset_state = 0
 *   [0]RXI = Interrupt when finished sending (BSY = 0)
    
 * PRESCALAR - 16 Bit Prescalar Value
 *
 * VALUE - 8 bit. A Write will start transmitting the data (BSY = 1)
 *               For reading a data, you have to write a dummy value and then read from this register when BSY = 0
 *
 * A Write or read when BSY = 1 will give unpredictable result
 */
 
typedef struct {
    __IO uint32_t STATUS;
    __IO uint32_t CONTROL;
    __IO uint32_t PRESCALE;
    __IO uint32_t VALUE;
} MCU_SPI_TypeDef;
 


/** I2C
 * CONTROL - Transaction control register for I2C
 *  [0] - When set to 1, I2C will start transmitting data depending on CONFIG Reigster
 *        When BYS becomes 1, this should be auto reset to 0
 *
 * CONFIG - Configuration register for I2C
 *  [0]STA - I2C Start Condition. When set to 1, the controller will start the transaction with START BIT
 *  [1]STO - I2C Stop Condition. When set to 1, the controller will end the transaction with STOP BIT
 *  [2]ACK - I2C Acknoledge. When TRUE, Controller will send ACK after revieving byte else will send NACK
 *  [3]RW  - I2C Read/Write. When set to 1, the controller will read a byte and send ack according to [2]. When 0, the controller will send a byte present in data register. The ACK received will go to STATUS[1]
 *
 * STATUS - Status of I2C Master
 *  [0]BSY - When TRUE, I2C is busy in a transaction
 *  [1]RCK - Copy of the recieved ACK after write
 *  
 * WRITE DATA - 8 Bit write value to be sent during write operation
 *
 * READ DATA - 8 Bit Read Value after read operation
 * 
 * A Write or read when BSY = 1 will give unpredictable result
 */
 
typedef struct {
    __IO uint32_t CONTROL;
    __IO uint32_t CONFIG;
    __IO uint32_t STATUS;
    __IO uint32_t WRITE;
    __IO uint32_t VALUE;
    __IO uint32_t PRESCALE;
} MCU_I2C_TypeDef;

#define MCU_FLASH_BASE        (0x00000000UL)
#define MCU_RAM_BASE          (0x10000000UL)
#define MCU_BASE              (0xE0000000UL)
 
#define MCU_GPIO_BASE         (0x50000000)
#define MCU_WDT_BASE          (0x51000000)
#define MCU_TIMER_BASE        (0x52000000)
#define MCU_UART_BASE         (0x53000000)
#define MCU_PWM_BASE          (0x54000000)
#define MCU_RTC_BASE          (0x55000000)
#define MCU_ADC_BASE          (0x56000000)
#define MCU_DAC_BASE          (0x57000000)
#define MCU_SPI1_BASE         (0x58000000)
#define MCU_SPI2_BASE         (0x59000000)
#define MCU_I2C1_BASE         (0x60000000)
#define MCU_I2C2_BASE         (0x61000000)
 
#define MCU_GPIO              ((MCU_GPIO_TypeDef*) MCU_GPIO_BASE)
#define MCU_WDT               ((MCU_WDT_TypeDef*) MCU_WDT_BASE)
#define MCU_TIMER             ((MCU_TIMER_TypeDef*) MCU_TIMER_BASE)
#define MCU_UART              ((MCU_UART_TypeDef*) MCU_UART_BASE)
#define MCU_PWM               ((MCU_PWM_TypeDef*) MCU_PWM_BASE)
#define MCU_RTC               ((MCU_RTC_TypeDef*) MCU_RTC_BASE)
#define MCU_ADC               ((MCU_ADC_TypeDef*) MCU_ADC_BASE)
#define MCU_DAC               ((MCU_DAC_TypeDef*) MCU_DAC_BASE)
#define MCU_SPI1              ((MCU_SPI_TypeDef*) MCU_SPI1_BASE)
#define MCU_SPI2              ((MCU_SPI_TypeDef*) MCU_SPI2_BASE)
#define MCU_I2C1              ((MCU_I2C_TypeDef*) MCU_I2C1_BASE)
#define MCU_I2C2              ((MCU_I2C_TypeDef*) MCU_I2C2_BASE)
