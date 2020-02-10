# README

This repository gives an example of how the Optimizely GO SDK can be compiled and used in native C/C++ code.

In this example and Nginx module is built that dynamically loads the Optimizely SDKs and changes it's behavior depending
on some feature flags.

The nginx module is based on <https://github.com/perusio/nginx-hello-world-module>

This was done as part of Winter Hackweek 2020.

## Build

Copy this directory over to the linux box and `make` to build the shared library. Golang cross compiling still can't
compile native code.

First compile nginx

```
ssh LINUX_HOST
cd <pathtodir with nginx>
./configure --with-debug --add-dynamic-module=/home/ec2-user/go-sdk-c-wrapper/nginx-hello-world-module
make
```

The following didn't work. Only dynamically loading the module seems to work.

```
./configure --with-debug --add-module=/home/ec2-user/go-sdk-c-wrapper/nginx-hello-world-module --with-ld-opt=/home/ec2-user/go-sdk-c-wrapper/go-sdk-c-wrapper.so
./configure --add-module=/home/ec2-user/nginx-hello-world-module
./configure --add-dynamic-module=/home/ec2-user/nginx-hello-world-module
```

## Local builds

Key and feature names may need to be adjusted.

```
make localtest
./test
```
