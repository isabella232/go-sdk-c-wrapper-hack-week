LIB:=go-sdk-c-wrapper.so
HEADER:=go-sdk-c-wrapper.h
SRC:=main.go
CFILE:=nginx-hello-world-module/ngx_http_hello_world_module.c
CC:=go build
CC_OPTS:=-buildmode=c-shared
CWD:=$(shell pwd)
REMOTE_HOST:=passrole

all: ${LIB}

run:
	go run ${SRC}

${LIB}: ${SRC}
	${CC} ${CC_OPTS} -o $@ $^
	cp ${LIB} ${HEADER} nginx-hello-world-module/

# Note: cross compiling still doesn't work for native generation
#GOOS=linux ${CC} ${CC_OPTS} -o $@ $^

.PHONY: cp
cp: 
	rsync -avz -e ssh ${CWD} ${REMOTE_HOST}:~/
	ssh ${REMOTE_HOST} '(cd /home/ec2-user/go-sdk-c-wrapper && make)'
	ssh ${REMOTE_HOST} '(cd /home/ec2-user/go-sdk-c-wrapper && cp go-sdk-c-wrapper.h ./nginx-hello-world-module/)'
	ssh ${REMOTE_HOST} '(cd /home/ec2-user/go-sdk-c-wrapper && sudo cp go-sdk-c-wrapper.so /usr/local/nginx/sbin/)'
	ssh ${REMOTE_HOST} '(cd /home/ec2-user/nginx-1.16.1 && make && sudo make install)'

.PHONY: restart
restart: cp
	ssh ${REMOTE_HOST} '(cd /usr/local/nginx && sudo killall nginx && sudo ./sbin/nginx)'

.PHONY: localtest
localtest:
	go build -o local-go-sdk-c-wrapper.so -buildmode=c-shared main.go
	gcc -o test main.c go-sdk-c-wrapper.so

.PHONY: clean
clean:
	rm -rf *.so *.h
