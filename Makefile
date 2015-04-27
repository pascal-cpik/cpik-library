##############################################################################
#
#     Makefile for CPIK with gputils
#
##############################################################################

SHELL := /bin/bash

# target PIC processor (syntax: 16f84):
PROC = 18f4520

FILES := sim 
LOCALSLBS = memcpymove.slb strcmp.slb sort.slb bcd.slb

LIBS = $(LOCALSLBS:%=lib/%)

SOURCES := $(addsuffix .c, $(FILES))
HEADERS := $(shell ./Makefile.gen_deps.pl $(SOURCES))

# files to include in git repository
EXTRA_GIT_FILES := Makefile Makefile.gen_deps.pl funclen.pl

.PHONY: clean burn gitadd gitcommit memuse  \
        mnemonics cpik doc 

PROG    = $(firstword $(FILES)).hex
LISTING = $(PROG:.hex=.lst)
COD     = $(PROG:.hex=.cod)

# list of object files:
OBJS = $(SOURCES:.c=.slb) 

# final asm after link before hex
ASM     = $(PROG:.hex=.asm)
LST     = $(PROG:.hex=.lst)

CC = /usr/bin/cpik-0.7.4
AS = /usr/bin/cpik-0.7.4
LD = /usr/bin/cpik-0.7.4

CFLAGS = -p$(PROC) -I /usr/share/cpik/0.7.3/include/device
ASFLAGS = -a 
LDFLAGS = -p p$(PROC)


# top-level rule to compile everything.
all: $(PROG)

# rule for assembling the asm file and getting the hex, cod, and listing
$(PROG) $(LST) $(COD): $(ASM)
	$(AS) $(ASFLAGS) -o $(PROG) $(ASM)

# link rule getting the asm file
$(ASM): $(OBJS) $(LIBS)
	$(LD) $(LDFLAGS) -o $(ASM) $(OBJS) $(LIBS) 

# special rule for PICloops-generated delay.c	
delay.c: myhardware.h delay.h delay.c.template PICloops.pl Makefile.gen_delay_c
	./Makefile.gen_delay_c >delay.c
	
# meta-rule for compiling any C source file.into .slb
%.slb: %.c $(HEADERS)
	$(CC) $(CFLAGS) $<
	@rm $<.c

show:
	@echo "HEADERS:" $(HEADERS)
	@echo "SOURCES:" $(SOURCES)
	@echo "LIBS:   " $(LIBS)
	@echo "EXTRA_GIT_FILES:" $(EXTRA_GIT_FILES)


clean:
	$(RM) *.asm *.c.c *.lst *.hex *.cod *.slb

burn: $(PROG)
	piklab-prog -t usb --target-self-powered false -c program -p icd2 -d $(PROC) $(PROG)
	piklab-prog -c run -p icd2 -t usb --target-self-powered false -d $(PROC)

gitadd:	
	git add $(HEADERS) $(SOURCES) $(EXTRA_GIT_FILES)

gitcommit:
	git commit -a 
	
doxygen:
	doxygen
	
memuse: $(LST)
	@echo '---------------- ROM ----------------'
	@grep 'Program Memory Bytes'  $(LISTING)
	@echo '---------------- RAM ----------------'
	@echo -n 'Last RAM location used:      '
	@grep soft_stack_start:1  $(LISTING) | awk '{print $$1}'
	@echo -n 'Last RAM location available: 0000'
	@grep __BADRAM /usr/local/share/gputils/header/p$(PROC).inc | cut -d "'" -f 2 | sort | head -1
	@echo '(but space for software stack needed)'

funclen:
	@./funclen.pl $(LST)

	
doc:
	okular docs/PIC18F2680.pdf
	
cpik:
	okular /usr/share/cpik/0.7.3/doc/cpik-0.7.3-1-doc.pdf

mnemonics:	
	okular /data/_programming/PIC/assembler/instructions.pdf 
