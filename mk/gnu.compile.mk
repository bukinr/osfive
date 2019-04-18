INCS += -I${OBJDIR}
INCS += -I${CURDIR}
INCS += -I${OSDIR}/include
INCS += -I${OSDIR}/sys
INCS += -I${OSDIR}/lib

CFLAGS += ${INCS} ${CFLAGS_$@} -D__OSFIVE__

#
# Add ${OBJDIR} prefix to each member of OBJECTS.
# Since this file is loaded before gnu.library.mk
# the list does not include libraries objects.
#
OBJECTS := $(addprefix $(OBJDIR)/,${OBJECTS})

${OBJDIR}/%.o: %.c GNUmakefile
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c -o $@ $<

${OBJDIR}/%.o: %.S GNUmakefile
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} -c -o $@ $<

__compile: __objdir __machine ${OBJECTS}

include ${OSDIR}/mk/gnu.objdir.mk
include ${OSDIR}/mk/gnu.machine.mk
