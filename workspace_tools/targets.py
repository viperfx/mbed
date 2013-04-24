
class Target:
    def __init__(self):
        # ARM Core
        self.core = None
        
        # The silicon vendor of this chip
        self.vendor = None
        
        # How much time (in seconds) it takes to the interface chip to flash a
        # new image and reset the target chip
        self.program_cycle_s = 1.5
        
        # list of toolchains that are supported by the mbed SDK for this target
        self.supported_toolchains = None
        
        self.name = self.__class__.__name__


class LPC2368(Target):
    def __init__(self):
        Target.__init__(self)
        
        self.core = "ARM7TDMI-S"
        self.vendor = "nxp"
        
        self.supported_toolchains = ["ARM"]


class LPC1768(Target):
    def __init__(self):
        Target.__init__(self)
        
        self.core = "Cortex-M3"
        self.vendor = "nxp"
        
        self.supported_toolchains = ["ARM", "GCC_ARM", "GCC_CS", "GCC_CR", "IAR"]


class LPC11U24(Target):
    def __init__(self):
        Target.__init__(self)
        
        self.core = "Cortex-M0"
        self.vendor = "nxp"
        
        self.supported_toolchains = ["ARM", "uARM"]


class KL25Z(Target):
    def __init__(self):
        Target.__init__(self)
        
        self.core = "Cortex-M0+"
        self.vendor = "freescale"
        
        self.supported_toolchains = ["ARM", "GCC_CW"]
        
        self.program_cycle_s = 4


class LPC812(Target):
    def __init__(self):
        Target.__init__(self)
        
        self.core = "Cortex-M0+"
        self.vendor = "nxp"
        
        self.supported_toolchains = ["uARM"]
        
        self.program_cycle_s = 4


class SIM(Target):
    def __init__(self):
        Target.__init__(self)

        self.core = "Cortex-M0+"
        self.vendor = "mbed"

        self.supported_toolchains = ["ARM"]

# Get a single instance for each target
TARGETS = [
    LPC2368(),
    LPC1768(),
    LPC11U24(),
    KL25Z(),
    LPC812(),
    SIM()
]

# Map each target name to its unique instance
TARGET_MAP = {}
for t in TARGETS:
    TARGET_MAP[t.name] = t

TARGET_NAMES = TARGET_MAP.keys()
