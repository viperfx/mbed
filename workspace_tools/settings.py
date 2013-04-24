from os.path import join, abspath, dirname
import logging

ROOT = abspath(join(dirname(__file__), ".."))
BUILD_DIR = abspath(join(ROOT, "..", "build"))

# These default settings have two purposes:
#    1) Give a template for writing local "private_settings.py"
#    2) Give default initialization fields for the "toolchains.py" constructors

SERVER_PORT = 59432
SERVER_ADDRESS = "10.2.200.94"
LOCALHOST = "10.2.200.94"

MUTs = {
    "1" : {"mcu": "LPC1768",
        "port":"COM41", "disk":'E:\\',
        "peripherals": ["TMP102", "digital_loop", "port_loop", "analog_loop", "SD"]
    },
    "2": {"mcu": "LPC11U24",
        "port":"COM42", "disk":'F:\\',
        "peripherals":  ["TMP102", "digital_loop", "port_loop", "SD"]
    },
    "3" : {"mcu": "LPC2368",
        "port":"COM43", "disk":'G:\\',
        "peripherals":  ["TMP102", "digital_loop", "port_loop", "analog_loop", "SD"]
    },
    "4" : {"mcu": "KL25Z",
        "port":"COM44", "disk":'H:\\',
        "peripherals":  ["TMP102", "digital_loop", "port_loop", "analog_loop", "SD"]
    },
}

# ARM
armcc = "standalone" # "keil", or "standalone", or "ds-5"

if armcc == "keil":
    ARM_PATH = "C:/Keil_4_54/ARM"
    
    ARM_BIN = join(ARM_PATH, "BIN40")
    
    ARM_INC = join(ARM_PATH, "INC")
    
    ARM_LIB    = join(ARM_PATH, "RV31", "LIB")

elif armcc == "standalone":
    ARM_PATH = "/media/sf_ARM/armcc"
    
    ARM_BIN = join(ARM_PATH, "bin")
    
    ARM_INC = join(ARM_PATH, "include")
    
    ARM_LIB    = join(ARM_PATH, "lib")

elif armcc == "ds-5":
    ARM_PATH = "C:/Program Files (x86)/DS-5"
    
    ARM_BIN = join(ARM_PATH, "bin")
    
    ARM_INC = join(ARM_PATH, "include")
    
    ARM_LIB    = join(ARM_PATH, "lib")

ARM_CPPLIB = join(ARM_LIB, "cpplib")
MY_ARM_CLIB = join(ARM_PATH, "lib", "microlib")

# GCC ARM
GCC_ARM_PATH = "C:/arm-none-eabi-gcc-4_7/bin"

# GCC CodeSourcery
GCC_CS_PATH = "C:/Program Files (x86)/CodeSourcery/Sourcery_CodeBench_Lite_for_ARM_EABI/bin"

# GCC CodeRed
GCC_CR_PATH = "C:/code_red/RedSuite_4.2.0_349/redsuite/Tools/bin"

# IAR
IAR_PATH = "C:/Program Files (x86)/IAR Systems/Embedded Workbench 6.0/arm"

try:
    # Allow to overwrite the default settings without the need to edit the
    # settings file stored in the repository
    from workspace_tools.private_settings import *
    logging.debug("Loaded user settings")
except ImportError:
    logging.debug("[WARNING] Using default settings. Define you settings in the file private_settings.py")