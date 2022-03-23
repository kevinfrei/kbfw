# TODO: Need to turn this off for Windows GNUmake :(
# TODO: Make instead, use WSL for build, then Windows for flashing maybe?
ifeq ($(OS),Windows_NT)
flags=
else
flags=-j
endif
# Now the default target
all: test

allclean:
ifeq ($(OS),Windows_NT)
	-rd /s /q out
else
	-rm -rf out
endif

ifeq ($(OS),Windows_NT)
# Decide if we've got VC++ around, which on Windows is preferred
ifeq ($(VisualStudioVersion),)
CXX=clang
else
CXX=cl.exe
endif
SFX=.exe
else
SFX=
endif

# Make the directory, the binary, then run it
test: out out/testbinary${SFX}
	out/testbinary${SFX}

build: out out/testbinary${SFX}

out:
	-mkdir out

# Size is larger than -O3 lame lame lame, clang
# OPTFLAGS=-flto -Oz
# Speed:
# OPTFLAGS=-flto -O3
# Debug:
ifeq (${CXX},cl.exe)
OBJFLAG=/FS /Fo
IMGFLAG=/FS /Fe
OPTFLAGS=/Od /ZI /EHsc
STDNUM=/std:c++20
OSUFFIX=obj
else
OBJFLAG=-o
IMGFLAG=-o
OPTFLAGS=-g
STDNUM=-std=c++20
OSUFFIX=o
endif

# Set up rules for local binaries
out/%.${OSUFFIX}: ../%.cpp
	${CXX} ${OPTFLAGS} -c -DTESTING -I.. -Imock_sys ${STDNUM} $< ${OBJFLAG}$@

out/%.${OSUFFIX} : %.cpp
	${CXX} ${OPTFLAGS} -c -I.. -Imock_sys ${STDNUM} $< ${OBJFLAG}$@

MOCKSRC = \
	testwrapper.cpp \
	mock_mpu.cpp \
	mock_hwserial.cpp

FWSRC = \
	../serial_dual.cpp \
	../split_34.cpp
 
MOCKOBJS = $(addprefix out/, $(patsubst %.cpp, %.${OSUFFIX}, ${MOCKSRC}))
FWOBJS = $(addprefix out/, $(patsubst ../%, %, $(patsubst %.cpp, %.${OSUFFIX}, ${FWSRC})))

OBJS = ${MOCKOBJS} ${FWOBJS}

out/testbinary${SFX}: ${OBJS}
	${CXX} ${OPTFLAGS} ${IMGFLAG}$@ $^
