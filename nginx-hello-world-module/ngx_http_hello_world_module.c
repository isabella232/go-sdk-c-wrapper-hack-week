/**
 * @file   ngx_http_hello_world_module.c
 * @author António P. P. Almeida <appa@perusio.net>
 * @date   Wed Aug 17 12:06:52 2011
 *
 * @brief  A hello world module for Nginx.
 *
 * @section LICENSE
 *
 * Copyright (C) 2011 by Dominic Fallows, António P. P. Almeida <appa@perusio.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
//#include "go-sdk-c-wrapper.h"

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

typedef long long go_int;
typedef double go_float64;
typedef struct {void *arr; go_int len; go_int cap;} go_slice;
typedef struct {const char *p; go_int len;} go_str;

#define HELLO_WORLD "hello world\r\n"

static char *ngx_http_hello_world(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_hello_world_handler(ngx_http_request_t *r);

static int is_feature_enabled(char *feature_name)
{
    void *handle;
    char *error;
    int enabled = 0;

    //handle = dlopen ("./go-sdk-c-wrapper.so", RTLD_LAZY);
    fprintf(stderr, "calling dlopen\n");
    handle = dlopen ("/usr/local/nginx/sbin/go-sdk-c-wrapper.so", RTLD_LAZY);
    if (!handle) {
        fputs (dlerror(), stderr);
        return 0;
    }
    fprintf(stderr, "dlopen succeded\n");

    fprintf(stderr, "calling OptimizelySDKInit\n");
    int (*sdkInit)(char *, char *) = dlsym(handle, "OptimizelySDKInit");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }
	sdkInit("EDmaiYBFz6LByqpm7yS9eJ", "0x123SomeUserId00");
    fprintf(stderr, "OptimizelySDKInit succeded\n");


    fprintf(stderr, "calling OptimizelySDKIsFeatureEnabled\n");
    int (*sdkFeatureEnabled)(char *) = dlsym(handle, "OptimizelySDKIsFeatureEnabled");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }
	enabled = sdkFeatureEnabled(feature_name);
    fprintf(stderr, "OptimizelySDKIsFeatureEnabled succeded and returned: %d\n", enabled);

    fprintf(stderr, "calling OptimizelySDKGetFeatureVariable\n");
    char * (*sdkGetFeatureVaruable)(char *, char *) = dlsym(handle, "OptimizelySDKGetFeatureVariable");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }
	char *message = sdkGetFeatureVaruable(feature_name, "greeting");
    fprintf(stderr, "sdkGetFeatureVaruable succeded and returned: %s\n", message);

    dlclose(handle);
    return enabled;
}

/*
 * returns the variable key if the feature is enabled
 */
static u_char *get_feature_variable(char *feature_name, char *variable_key)
{
    char *message;
    void *handle;
    char *error;
    int enabled = 0;

    //handle = dlopen ("./go-sdk-c-wrapper.so", RTLD_LAZY);
    fprintf(stderr, "calling dlopen\n");
    handle = dlopen ("/usr/local/nginx/sbin/go-sdk-c-wrapper.so", RTLD_LAZY);
    if (!handle) {
        fputs (dlerror(), stderr);
        return 0;
    }
    fprintf(stderr, "dlopen succeded\n");

    fprintf(stderr, "calling OptimizelySDKInit\n");
    int (*sdkInit)(char *, char *) = dlsym(handle, "OptimizelySDKInit");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }
	sdkInit("EDmaiYBFz6LByqpm7yS9eJ", "0x123SomeUserId00");
    fprintf(stderr, "OptimizelySDKInit succeded\n");


    fprintf(stderr, "calling OptimizelySDKIsFeatureEnabled\n");
    int (*sdkFeatureEnabled)(char *) = dlsym(handle, "OptimizelySDKIsFeatureEnabled");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }
	enabled = sdkFeatureEnabled(feature_name);
    fprintf(stderr, "OptimizelySDKIsFeatureEnabled succeded and returned: %d\n", enabled);

    fprintf(stderr, "calling OptimizelySDKGetFeatureVariable\n");
    char * (*sdkGetFeatureVaruable)(char *, char *) = dlsym(handle, "OptimizelySDKGetFeatureVariable");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }
	message = sdkGetFeatureVaruable(feature_name, "greeting");
    fprintf(stderr, "sdkGetFeatureVaruable succeded and returned: %s\n", message);

    dlclose(handle);
    return (u_char *)message;
}

/**
 * This module provided directive: hello world.
 *
 */
static ngx_command_t ngx_http_hello_world_commands[] = {

    { ngx_string("hello_world"), /* directive */
      NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS, /* location context and takes
                                            no arguments*/
      ngx_http_hello_world, /* configuration setup function */
      0, /* No offset. Only one context is supported. */
      0, /* No offset when storing the module configuration on struct. */
      NULL},

    ngx_null_command /* command termination */
};

/* The hello world string. */
static u_char ngx_hello_world[] = HELLO_WORLD;

/* The module context. */
static ngx_http_module_t ngx_http_hello_world_module_ctx = {
    NULL, /* preconfiguration */
    NULL, /* postconfiguration */

    NULL, /* create main configuration */
    NULL, /* init main configuration */

    NULL, /* create server configuration */
    NULL, /* merge server configuration */

    NULL, /* create location configuration */
    NULL /* merge location configuration */
};

/* Module definition. */
ngx_module_t ngx_http_hello_world_module = {
    NGX_MODULE_V1,
    &ngx_http_hello_world_module_ctx, /* module context */
    ngx_http_hello_world_commands, /* module directives */
    NGX_HTTP_MODULE, /* module type */
    NULL, /* init master */
    NULL, /* init module */
    NULL, /* init process */
    NULL, /* init thread */
    NULL, /* exit thread */
    NULL, /* exit process */
    NULL, /* exit master */
    NGX_MODULE_V1_PADDING
};

/**
 * Content handler.
 *
 * @param r
 *   Pointer to the request structure. See http_request.h.
 * @return
 *   The status of the response generation.
 */
static ngx_int_t ngx_http_hello_world_handler(ngx_http_request_t *r)
{
    ngx_buf_t *b;
    ngx_chain_t out;
    u_char *message;

    ngx_log_debug(NGX_LOG_DEBUG_HTTP, r->connection->log, 0, "==> about to check on feature");
    if (is_feature_enabled("is_it_on_feature_key")) {
        message = get_feature_variable("is_it_on_feature_key", "greeting");
    } else {
        message = ngx_hello_world;
    }

    /* Set the Content-Type header. */
    r->headers_out.content_type.len = sizeof("text/plain") - 1;
    r->headers_out.content_type.data = (u_char *) "text/plain";

    /* Allocate a new buffer for sending out the reply. */
    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));

    /* Insertion in the buffer chain. */
    out.buf = b;
    out.next = NULL; /* just one buffer */

    b->pos = message; /* first position in memory of the data */
    b->last = message + ((long int)ngx_strlen((const char *)message)); /* last position in memory of the data */
    
    //b->pos = ngx_hello_world; /* first position in memory of the data */
    //b->last = ngx_hello_world + sizeof(ngx_hello_world) - 1; /* last position in memory of the data */

    b->memory = 1; /* content is in read-only memory */
    b->last_buf = 1; /* there will be no more buffers in the request */

    /* Sending the headers for the reply. */
    r->headers_out.status = NGX_HTTP_OK; /* 200 status code */
    /* Get the content length of the body. */
    r->headers_out.content_length_n = ((long int)ngx_strlen((const char *)message));
    ngx_http_send_header(r); /* Send the headers */

    /* Send the body, and return the status code of the output filter chain. */
    return ngx_http_output_filter(r, &out);
} /* ngx_http_hello_world_handler */

/**
 * Configuration setup function that installs the content handler.
 *
 * @param cf
 *   Module configuration structure pointer.
 * @param cmd
 *   Module directives structure pointer.
 * @param conf
 *   Module configuration structure pointer.
 * @return string
 *   Status of the configuration setup.
 */
static char *ngx_http_hello_world(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t *clcf; /* pointer to core location configuration */

    /* Install the hello world handler. */
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_hello_world_handler;

    return NGX_CONF_OK;
} /* ngx_http_hello_world */
