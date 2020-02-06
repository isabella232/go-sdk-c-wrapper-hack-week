LIB:=go-sdk-c-wrapper.so
SRC:=main.go
CC:=go build
CC_OPTS:=-buildmode=c-shared

all: ${LIB}

${LIB}: ${SRC}
	#GOOS=linux ${CC} ${CC_OPTS} -o $@ $^
	${CC} ${CC_OPTS} -o $@ $^

clean:
	rm -rf *.so
