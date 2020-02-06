LIB:=go-sdk-c-wrapper.so
SRC:=main.go
CC:=go build
CC_OPTS:=-buildmode=c-shared

all: ${LIB}

run:
	go run ${SRC}

${LIB}: ${SRC}
	${CC} ${CC_OPTS} -o $@ $^

# Note: cross compiling still doesn't work for native generation
#GOOS=linux ${CC} ${CC_OPTS} -o $@ $^

clean:
	rm -rf *.so *.h
