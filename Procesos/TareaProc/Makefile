PROY=procesos
DSTPATH=/usr/local/bin
CFLAGS=-Wall
COBJ=-c
LINKF=-lm
CC=gcc
ORIGFILES=$(wildcard *.c)
OBJFILES=$(ORIGFILES:.c=.o)

all:${PROY}

# % es cualaquier archivo en la carpeta 
%.o:%.c
	${CC} ${COBJ} $<  ${CFLAGS}
# $< regresa la primer dependencia

${PROY}:${OBJFILES}
	${CC} $^ -o $@ ${LINKF}  
# $^ Regresa la lista de dependencias completa

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
