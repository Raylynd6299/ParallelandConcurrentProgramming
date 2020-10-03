PROY=muestreo
ARCHF=archivos
PROCF=procesamiento
DSTPATH=/usr/local/bin
CFLAGS=-Wall
COBJ=-c
LINKF=-lm
CC=gcc

all:${PROY}

${PROY}.o:${PROY}.c
	@${CC} ${COBJ} ${PROY}.c ${CFLAGS}
${PROCF}.o:${PROCF}.c
	@${CC} ${COBJ} ${PROCF}.c ${CFLAGS}
${ARCHF}.o:${ARCHF}.c
	@${CC} ${COBJ} ${ARCHF}.c ${CFLAGS}
${PROY}:${PROY}.o ${PROCF}.o ${ARCHF}.o
	@${CC} ${PROY}.o ${PROCF}.o ${ARCHF}.o -o ${PROY} ${LINKF} 

.PHONY:clean

install: all
	@if [ ! -d ${DSTPATH} ]; then\
		sudo mkdir ${DSTPATH}; \
	fi
	@sudo cp ${PROY} ${DSTPATH}

uninstall:
	@sudo rm ${DSTPATH}/${PROY}

clean:
	@rm -f *.o ${PROY}
