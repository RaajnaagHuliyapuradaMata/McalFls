PROJECT_NAME = FlashDrv

#------------------------------------------------------------------------------
# More static settings placed inside separate file
#------------------------------------------------------------------------------
include Makefile.static

#------------------------------------------------------------------------------
#define Compiler path
# E.g.: COMPILER_BASE = D:\uti\%vendor%\%platform%\%version%
#       COMPILER_BIN  = $(COMPILER_BASE)\bin
#       COMPILER_INC  = $(COMPILER_BASE)\inc
#       COMPILER_LIB  = $(COMPILER_BASE)\lib
#------------------------------------------------------------------------------
COMPILER_BASE = D:\uti\Compiler\RH850\GHS\comp_201517
COMPILER_BIN  = $(COMPILER_BASE)
COMPILER_INC  = $(COMPILER_BASE)\ansi $(COMPILER_BASE)\include\v800
COMPILER_LIB  = $(COMPILER_BASE)\lib\rh850

#For SafeCtx-support, the path of the Elf-Converter has to be set
ELFCONVERTER_BIN = $(ROOT)\Misc\OsElfConverter\ElfConverter.exe

#------------------------------------------------------------------------------
# Select the path of the Devicefile
#------------------------------------------------------------------------------
DEVICE_FILE_FOLDER = $(COMPILER_BASE)\rh850

#------------------------------------------------------------------------------
# Select the path of the multi
#------------------------------------------------------------------------------
MULTI_BASE = D:\uti\Compiler\RH850\GHS\multi_616

#------------------------------------------------------------------------------
# Build Options Selection: VECTOR / CUSTOMER
#------------------------------------------------------------------------------
ASFLAGS_SELECTOR = VECTOR
CFLAGS_SELECTOR  = CUSTOMER
LDFLAGS_SELECTOR = VECTOR

#------------------------------------------------------------------------------
# Default License server and port for the Multi IDE
#------------------------------------------------------------------------------
LICENSE_SERVER = vistrlic1.vi.vector.int
LICENSE_SERVER_PORT = 2009

#------------------------------------------------------------------------------
#define Emulator path
# E.g.: EMU_PATH = C:\UTI\HITOPWIN\P6811
#------------------------------------------------------------------------------
ifeq ($(EMU_PATH),)
EMU_PATH = $(COMPILER_BASE)
endif

#------------------------------------------------------------------------------
# Set NANT_USED to '1', to enable the usage of NAnt support within
# Global Makefile. If this is enabled, the Makesupport will include the
# NAnt support from a intranel link and the NAnt build-targets can be used.
#------------------------------------------------------------------------------
#NANT_USED=1

#------------------------------------------------------------------------------
# Set MKVERBOSE to a various value, to enable enhanced debug output from
# Makesupport. To disable this afterwards, set MKVERBOSE to nothing
# (comment out this line and type "set MKVERBOSE=" in command window)
#------------------------------------------------------------------------------
#MKVERBOSE=1

#------------------------------------------------------------------------------
# Set BRSVINFO_USED to '1', to enable the generation of BrsVInfo.h within the
# GenData folder by the Makesupport.
# The BrsVInfo.h will contain e.g. kBrsCompilerVersion, to use this
# information within the embedded code.
#------------------------------------------------------------------------------
#BRSVINFO_USED=1

#------------------------------------------------------------------------------
# Turn off strict c setting for dependency generation
#------------------------------------------------------------------------------
#STRICT_C_OFF=1

#------------------------------------------------------------------------------
# Set DELETE_DLD to '1', to enable the deleting of previously
# generated/outdated Linker-script file, before every new linkage request.
#------------------------------------------------------------------------------
#DELETE_DLD=1

#------------------------------------------------------------------------------
# Set NEW_DEPENDENCY_FORMAT to '1' to enable parallel creation of dependencies.
# You have to ensure that you call m.bat with -jX to use this feature.
#------------------------------------------------------------------------------
#NEW_DEPENDENCY_FORMAT=1

#------------------------------------------------------------------------------
#if you want to use code analysis tools like PC-Lint or QAC,
# configure them within Makefile.analysis (part of global-make-package)
# and include this file here
#------------------------------------------------------------------------------
#include Makefile.analysis

#------------------------------------------------------------------------------
# Dependency defines
# These defines are used for the GNU-Preprocessor,
# e.g.: BRS_TIMEBASE_CLOCK=$(TIMEBASE_CLOCK)
#------------------------------------------------------------------------------
ifeq ($(DERIVATIVE_GROUP_$(DERIVATIVE)),$(filter $(DERIVATIVE_GROUP_$(DERIVATIVE)),F1H C1H C1M_AZ P1H F1KH))
  BRS_STARTUP_RAM_DEFINES_DEP =  BRS_CPU_LOCAL_RAM_SIZE_CORE0=$(LOCAL_RAM_SIZE_CORE0_$(DERIVATIVE)) \
                                 BRS_CPU_LOCAL_RAM_SIZE_CORE1=$(LOCAL_RAM_SIZE_CORE1_$(DERIVATIVE)) \
                                 BRS_CPU_RAM_START_CORE0=$($(DERIVATIVE_GROUP_$(DERIVATIVE))_LOCAL_RAM_START_ADDRESS_CORE0_$(LOCAL_RAM_SIZE_CORE0_$(DERIVATIVE))) \
                                 BRS_CPU_RAM_START_CORE1=$($(DERIVATIVE_GROUP_$(DERIVATIVE))_LOCAL_RAM_START_ADDRESS_CORE1_$(LOCAL_RAM_SIZE_CORE1_$(DERIVATIVE)))

else
  ifeq ($(DERIVATIVE_GROUP_$(DERIVATIVE)),$(filter $(DERIVATIVE_GROUP_$(DERIVATIVE)),F1KM_S4))
    BRS_STARTUP_RAM_DEFINES_DEP =  BRS_CPU_LOCAL_RAM_SIZE_CORE0=$(LOCAL_RAM_SIZE_CORE0_$(DERIVATIVE)) \
                                   BRS_CPU_RAM_START_CORE0=$($(DERIVATIVE_GROUP_$(DERIVATIVE))_LOCAL_RAM_START_ADDRESS_CORE0_$(LOCAL_RAM_SIZE_CORE0_$(DERIVATIVE)))

  else
    BRS_STARTUP_RAM_DEFINES_DEP =  BRS_CPU_LOCAL_RAM_SIZE_CORE0=$(GLOBAL_RAM_SIZE_$(DERIVATIVE)) \
                                   BRS_CPU_RAM_START_CORE0=$($(DERIVATIVE_GROUP_$(DERIVATIVE))_RAM_START_ADDRESS_$(GLOBAL_RAM_SIZE_$(DERIVATIVE)))
  endif
endif

DEP_DEFINES = BRS_DERIVATIVE_$(DERIVATIVE)                           \
              BRS_OSC_CLK=$(MAIN_OSC_CLK)                            \
              BRS_TIMEBASE_CLOCK=$(TIMEBASE_CLOCK)                   \
              BRS_OS_USECASE_$(OS_USECASE)                           \
              BRS_EVA_BOARD_$(EVA_BOARD)                             \
              BRS_DERIVATIVE_GROUP_$(DERIVATIVE_GROUP_$(DERIVATIVE)) \
              BRS_PLATFORM_$(PLATFORM)                               \
              BRS_COMP_$(COMPILER_MANUFACTURER)                      \
              $(BRS_STARTUP_RAM_DEFINES_DEP)

#------------------------------------------------------------------------------
# $(AS_ENV) is the environment necessary to run the assembler
# $(AS) defines the path to the assembler
# $(ASFLAGS_VECTOR_MAKESUPPORT) defines all assembler switches, mandatory for
#                               the Vector build environment (Makesupport/BrsHw)
# $(ASFLAGS_VECTOR_OPTIONS) defines the Vector default assembler switches
# $(ASFLAGS_CUSTOMER_OPTIONS) defines the customer requested assembler switches
# Depending of ASFLAGS_SELECTOR, ASFLAGS_VECTOR_OPTIONS or ASFLAGS_CUSTOMER_OPTIONS
# are used together with ASFLAGS_VECTOR_MAKESUPPORT for Build.
#------------------------------------------------------------------------------
# Available Assembler-flags could be posted here
#------------------------------------------------------------------------------
AS_ENV  = $(CC_ENV)
AS      = $(CC)

#Please add only absolutely mandatory options below
ASFLAGS_VECTOR_MAKESUPPORT =

#Please add any other option below (vector default options)
ASFLAGS_VECTOR_OPTIONS = -cpu=$(GHS_CPU_SWITCH_$(DERIVATIVE_GROUP_$(DERIVATIVE)))

#Please enter all customer options below
ASFLAGS_CUSTOMER_OPTIONS =

#------------------------------------------------------------------------------
# $(ASVERSION) defines the assembler switch for version report
# E.g.: ASVERSION = -V
#------------------------------------------------------------------------------
ASVERSION = test.asm -V

#------------------------------------------------------------------------------
# $(AS_LC) defines the number of lines used for assembler version information
# in BrsVinfo.h and Deliverydescription (default is 5)
#------------------------------------------------------------------------------
AS_LC = 5

#------------------------------------------------------------------------------
#------------------------- MUST be filled out ---------------------------------
# $(CC_ENV) is the environment necessary to run the compiler
# $(CC) defines the path to the C-Compiler
# $(CFLAGS_VECTOR_MAKESUPPORT) defines all compiler switches, mandatory for
#                               the Vector build environment (Makesupport/BrsHw)
# $(CFLAGS_VECTOR_OPTIONS) defines the Vector default compiler switches
# $(CFLAGS_CUSTOMER_OPTIONS) defines the customer requested compiler switches
# Depending of CFLAGS_SELECTOR, CFLAGS_VECTOR_OPTIONS or CFLAGS_CUSTOMER_OPTIONS
# are used together with CFLAGS_VECTOR_MAKESUPPORT for Build.
#------------------------------------------------------------------------------
# Options: (Not all options apply to all languages or targets).
#   -a              Compile for code coverage analysis by Multi.
#   -archive        Create a library archive for use with linker.
#   -asm=<args>     Pass <args> directly to the assembler.
#   -c              Produce object files, but do not link.
#   -check=XXX      none,all,[no]bound,[no]nilderef,[no]switch,[no]assignbound,[no]zerodivide.
#                   The compiler generates runtime checks for the items requested.
#   -D<name>[=<val>] In C, C++: define <name> with value <val>.
#    -delete        Removes unused functions from the executable program.
#   -E              In C, C++: preprocess file and send result to stdout.
#   -entry=symbol   Set the entry point in the linker output.
#   -fsoft          Use software floating point.
#   -fnone          In C, C++: Give syntax errors for floating point usage
#   -G              Generate information for MULTI debugger.
#   -H              Print names of included headers to stderr.
#   -I<dir>         Passed to compiler to add <dir> to include search path.
#   -L<dir>         Passed to linker to add <dir> to library search path.
#   -l<name>        Passed to linker to look for library lib<name>.a.
#   -lnk=<arg>      Pass <arg> directly to linker.
#   -list[=name]    Assembler will produce a listing file.
#   -list/<type>    For Ada95, generate the requested listing.
#   -map[=name]     Linker will produce a map file.
#   --no_commons    Disable handling of global variables as common data.
#                   Common data are not counted to the object file resources!!
#   -nofloatio      Use printf, scanf without %e %f %g in libansi.
#   -noobj          Turn off direct object file creation.
#   -nostartfiles   Do not add start-up files to link
#   -nostdlib       Do not add start-up files or libraries to link
#   -obj            Turn on direct object file creation.
#   -o name         Name final output file.
#   -Ospeed         Optimize for speed, even if code is larger.
#   -Ospace         Optimize for smaller code, even if it is slower.
#   -O              Turn on general optimizations
#   -OI             Expand routines inline rather than generating calls.
#   -OI=name,...    Inline only the named routines.
#   -OL             Optimize loops, including loop unrolling.
#   -Onopeep        Turn off peephole optimization.
#   -P              In C, C++: preprocess into file.i and stop.
#   -p              Compile for call count profiling.
#   -pg             Compile for call count and call graph profiling.
#   -passsource     Pass compiler source lines into assembly file.
#   -r20has255      During startup, crt0.800 places the value 255 in r20.
#   -r21has65535    During startup, crt0.800 places the value 65535 in r21.
#   -registermode=XX  Enable 22, 26, or 32-register mode.
#   -S              Produce assembly files, and stop. (implies -noobj)
#   -sda=val        Put objects <= val bytes into Small Data Area
#   -zda=val        Put objects <= val bytes into Zero Data Area
#   -syntax         Compilers will check syntax but not generate code.
#   -U<name>        In C, C++: undefine the macro <name>.
#   -v              Print all commands before they are executed.
#   -w              Suppress compiler, assembler, and linker warning messages.
#   -Wundef         Warning undefined symbols in preprocessor expressions.
#   -#              Print all commands INSTEAD of executing them.
#   -needprototype  Check for correct function prototypes; if not correct an error is detected!
#   --prototype_xxx  Alternative prototype checking configuration.
#                    Controls the treatment of functions that are referenced or called when no prototype
#                    has been provided. Possible values for xxx are
#                    errors
#                    warnings
#                    silent (default)
#------------------------------------------------------------------------------
CC_ENV = export GHS_LMHOST=@$(LICENSE_SERVER);\
         export GHS_LMPORT=$(LICENSE_SERVER_PORT);
CC     = $(COMPILER_BIN)\ccrh850.exe

#Please add only absolutely mandatory options below

ifeq ($(DERIVATIVE_GROUP_$(DERIVATIVE)),$(filter $(DERIVATIVE_GROUP_$(DERIVATIVE)),F1H C1H C1M_AZ P1H F1KH))
  BRS_STARTUP_RAM_DEFINES = -DBRS_CPU_LOCAL_RAM_SIZE_CORE0=$(LOCAL_RAM_SIZE_CORE0_$(DERIVATIVE)) \
                            -DBRS_CPU_LOCAL_RAM_SIZE_CORE1=$(LOCAL_RAM_SIZE_CORE1_$(DERIVATIVE)) \
                            -DBRS_CPU_RAM_START_CORE0=$($(DERIVATIVE_GROUP_$(DERIVATIVE))_LOCAL_RAM_START_ADDRESS_CORE0_$(LOCAL_RAM_SIZE_CORE0_$(DERIVATIVE))) \
                            -DBRS_CPU_RAM_START_CORE1=$($(DERIVATIVE_GROUP_$(DERIVATIVE))_LOCAL_RAM_START_ADDRESS_CORE1_$(LOCAL_RAM_SIZE_CORE1_$(DERIVATIVE)))

else
  ifeq ($(DERIVATIVE_GROUP_$(DERIVATIVE)),$(filter $(DERIVATIVE_GROUP_$(DERIVATIVE)),F1KM_S4))
    BRS_STARTUP_RAM_DEFINES =  -DBRS_CPU_LOCAL_RAM_SIZE_CORE0=$(LOCAL_RAM_SIZE_CORE0_$(DERIVATIVE)) \
                               -DBRS_CPU_RAM_START_CORE0=$($(DERIVATIVE_GROUP_$(DERIVATIVE))_LOCAL_RAM_START_ADDRESS_CORE0_$(LOCAL_RAM_SIZE_CORE0_$(DERIVATIVE)))

  else
    BRS_STARTUP_RAM_DEFINES = -DBRS_CPU_LOCAL_RAM_SIZE_CORE0=$(GLOBAL_RAM_SIZE_$(DERIVATIVE)) \
                              -DBRS_CPU_RAM_START_CORE0=$($(DERIVATIVE_GROUP_$(DERIVATIVE))_RAM_START_ADDRESS_$(GLOBAL_RAM_SIZE_$(DERIVATIVE)))
  endif
endif

CFLAGS_VECTOR_MAKESUPPORT = -DBRS_DERIVATIVE_$(DERIVATIVE)         \
                            -DBRS_OSC_CLK=$(MAIN_OSC_CLK)          \
                            -DBRS_TIMEBASE_CLOCK=$(TIMEBASE_CLOCK) \
                            -DBRS_EVA_BOARD_$(EVA_BOARD)           \
                            -DBRS_DERIVATIVE_GROUP_$(DERIVATIVE_GROUP_$(DERIVATIVE)) \
                            -DBRS_OS_USECASE_$(OS_USECASE)         \
                            -DBRS_PLATFORM_$(PLATFORM)             \
                            -DBRS_COMP_$(COMPILER_MANUFACTURER)    \
                            $(BRS_STARTUP_RAM_DEFINES)             \
                            -list=$(LST_PATH)/$*.lst               \
                            -object_dir=$(OBJ_PATH)                \
                            -stderr=$(ERR_PATH)\$*.$(ERR_SUFFIX)   \
                            -c

# Some MCAL and old OS formerly required mode 22.
REGISTERMODE = 32

#Please add any other option below (vector default options)
# vismkk: Either use -sda=all and -large_sda (all variables into SDA and 8 MB SDA) or
#         do not use SDA at all. -nothreshold (default) + -no_large_sda (default)
#         Tiny data and zero data (.tdata / .zdata) are not supported by OsGen7
CFLAGS_VECTOR_OPTIONS = -cpu=$(GHS_CPU_SWITCH_$(DERIVATIVE_GROUP_$(DERIVATIVE))) \
                        -needprototype     \
                        -Wundef            \
                        --no_commons       \
                        -G                 \
                        -dual_debug        \
                        -noobj             \
                        -pragma_asm_inline \
                        -inline_prologue   \
                        --long_long        \
                        -fsoft             \
                        -sda=all           \
                        -large_sda         \
                        -Ogeneral          \
                        -registermode=$(REGISTERMODE)

#Please enter all customer options below
CFLAGS_CUSTOMER_OPTIONS =-cpu=rh850                \
                         -sda=all                  \
                         -registermode=32          \
                         -prepare_dispose          \
                         -no_callt                 \
                         -inline_prologue          \
                         -notda                    \
                         -reserve_r2               \
                         -fsoft                    \
                         --unknown_pragma_warnings \
                         -list                     \
                         -g                        \
                         -shortenum

#------------------------------------------------------------------------------
# $(CVERSION) defines the compiler switch for version report
# E.g.: CVERSION = -V
#------------------------------------------------------------------------------
CVERSION = -V dummy.c

#------------------------------------------------------------------------------
# $(CC_LC) defines the number of lines used for compiler version information
# in BrsVinfo.h and Deliverydescription (default is 5)
#------------------------------------------------------------------------------
CC_LC = 5

#------------------------------------------------------------------------------
# $(CINC) defines the include switch of the used compiler.
# E.g.: COSMIC Compiler use: CINC = -i
#------------------------------------------------------------------------------
CINC = -I

#------------------------------------------------------------------------------
#------------------------- MUST be filled out ---------------------------------
# $(LD_ENV) is the environment necessary to run the linker
# $(LD) defines the path linker
# $(LDFLAGS_VECTOR_MAKESUPPORT) defines all linker switches, mandatory for
#                               the Vector build environment (Makesupport/BrsHw)
# $(LDFLAGS_VECTOR_OPTIONS) defines the Vector default linker switches
# $(LDFLAGS_CUSTOMER_OPTIONS) defines the customer requested linker switches
# Depending of LDFLAGS_SELECTOR, LDFLAGS_VECTOR_OPTIONS or LDFLAGS_CUSTOMER_OPTIONS
# are used together with LDFLAGS_VECTOR_MAKESUPPORT for Build.
#------------------------------------------------------------------------------
# Available Linker-flags could be posted here
#------------------------------------------------------------------------------
LD_ENV  = $(CC_ENV)
LD      = $(CC)

#Please add only absolutely mandatory options below
LDFLAGS_VECTOR_MAKESUPPORT = -o $*.$(BINARY_SUFFIX)        \
                             -map=$*.map                   \
                             -cpu=$(GHS_CPU_SWITCH_$(DERIVATIVE_GROUP_$(DERIVATIVE))) \
                             --preprocess_linker_directive_full \
                             -nostartfiles                                            \
                              -nostdlib                                                \
                              -delete                                                  \
                              -nofloatio

ifeq ($(USER_LINKER_COMMAND_FILE),)
LDFLAGS_VECTOR_MAKESUPPORT += $(PROJECT_NAME).$(LNK_SUFFIX)
else
LDFLAGS_VECTOR_MAKESUPPORT += $(USER_LINKER_COMMAND_FILE)
endif

#Please add any other option below (vector default options)
LDFLAGS_VECTOR_OPTIONS = -Manx       \
                         -G          \
                         -dual_debug \
                         -sda=all    \
                         -large_sda  \
                         -Ogeneral

#Please enter all customer options below
LDFLAGS_CUSTOMER_OPTIONS =

#------------------------------------------------------------------------------
# $(LDVERSION) defines the linker switch for version report
# E.g.: LDVERSION = -v
#------------------------------------------------------------------------------
LDVERSION = $(CVERSION)

#------------------------------------------------------------------------------
# $(LD_LC) defines the number of lines used for linker version information
# in BrsVinfo.h and Deliverydescription (default is 5)
#------------------------------------------------------------------------------
LD_LC = $(CC_LC)

#------------------------- MUST be filled out ---------------------------------
# $(HEX_ENV) is the environment necessary to run the hexfile generator
# $(HEX) defines the path linker
# $(HEXFLAGS)
#------------------------------------------------------------------------------
HEX_ENV    = $(CC_ENV)
HEX        = $(COMPILER_BIN)\gsrec.exe

HEXFLAGS = -nos5 -skip .tdata $(PROJECT_NAME).$(BINARY_SUFFIX)  -o

#------------------------------------------------------------------------------
#------------------------- MUST be filled out ---------------------------------
# $(LB_ENV) is the environment necessary to run the librarian
# $(LB) defines the path to the C-librarian
# $(LBFLAGS) defines all librarian switches
#------------------------------------------------------------------------------
# Available Librarian-flags could be posted here
#------------------------------------------------------------------------------
LB_ENV  = $(LD_ENV)
LB      = $(LD)

LBFLAGS = :archiver.args=-c \
          -archive          \
          -o $@

#------------------------------------------------------------------------------
# $(LBVERSION) defines the archiver switch for version report
# E.g.: LBVERSION = -v
#------------------------------------------------------------------------------
LBVERSION = $(LDVERSION)

#------------------------------------------------------------------------------
# $(LB_LC) defines the number of lines used for librarian version information
# in BrsVinfo.h
#------------------------------------------------------------------------------
LB_LC = $(LD_LC)

#------------------------------------------------------------------------------
# Additional includes essentially for compilation
#------------------------------------------------------------------------------
ADDITIONAL_INCLUDES +=

#------------------------------------------------------------------------------
# Additional objects essentially for linking
# E.g.: ADDITIONAL_OBJECTS = $(OBJ_PATH)\myobject.$(OBJ_SUFFIX)
#------------------------------------------------------------------------------
ADDITIONAL_OBJECTS +=

#------------------------------------------------------------------------------
# List of assembler source files
# E.g.: ASM_SOURCES = source\startup.$(ASM_SUFFIX)
#------------------------------------------------------------------------------
ASM_SOURCES += ..\FlashLib\r_fcl_hw_access_asm.850

#------------------------------------------------------------------------------
# Add Startup code to application source list
# E.g.: APP_SOURCE_LST += source\startup.c
#------------------------------------------------------------------------------
APP_SOURCE_LST +=

hex: $(PROJECT_NAME).$(BINARY_SUFFIX)
	$(subst \,/,$(HEX) $(HEXFLAGS) $(PROJECT_NAME).hex)

#------------------------------------------------------------------------------
# Check if all necessary variables are set
# (Checks that are not possible to be performed within Makefile.static)
#------------------------------------------------------------------------------

###############################################################################
######### DO NOT remove these lines from the end of the Makefile!!!###########
###############################################################################

#------------------------------------------------------------------------------
# Platform/compiler/derivative/emulator dependant makefile is included here
# It defines a rule to generate the linker and a rule to generate the
# symbol preprocessor command file.
# A template for this Makefile can be found under
#     R:\Can_Base\CANtate\BRS\PlatformSpecific\...\OrganiAndMake\...
#------------------------------------------------------------------------------
include Makefile.$(PLATFORM).$(COMPILER_MANUFACTURER).$(EMULATOR).make

#------------------------------------------------------------------------------
#include the main makefile where all the targets are defined
#------------------------------------------------------------------------------
include $(MAKESUPPORT_DIR)\Global.Makefile.target.make.$(VERSION)

#End of Makefile
