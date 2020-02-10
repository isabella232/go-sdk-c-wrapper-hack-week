# README

This repository gives an example of how the Optimizely GO SDK can be compiled and used in native C/C++ code.

In this example an Nginx module is built that dynamically loads the Optimizely SDKs and changes it's behavior depending
on some feature flags.

The nginx module is based on <https://github.com/perusio/nginx-hello-world-module>

This was done as part of Winter Hackweek 2020.

## Build

First compile nginx on a Linux VM.

```
ssh LINUX_HOST
cd <pathtodir with nginx>
./configure --with-debug --add-dynamic-module=/home/ec2-user/go-sdk-c-wrapper/nginx-hello-world-module
make
```

Copy this directory over to the linux box and `make` to build the shared library. Golang cross compiling still can't
compile native code. See `Makefile` for `cp` target that does this.

The following didn't work. Only dynamically loading the module seems to work.

```
./configure --with-debug --add-module=/home/ec2-user/go-sdk-c-wrapper/nginx-hello-world-module --with-ld-opt=/home/ec2-user/go-sdk-c-wrapper/go-sdk-c-wrapper.so
./configure --add-module=/home/ec2-user/nginx-hello-world-module
./configure --add-dynamic-module=/home/ec2-user/nginx-hello-world-module
```

## Local builds

For a local test, that will build an run on any architecture try the following.

```
make localtest
./test
```

Key and feature names may need to be adjusted.
