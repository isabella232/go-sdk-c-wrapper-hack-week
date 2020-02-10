/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Demo of the Optimizely SDK in C
 *
 *        Version:  1.0
 *        Created:  02/04/2020 15:31:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ola Nordstrom (ola.nordstrom@optimizely.com), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "local-go-sdk-c-wrapper.h" // TODO rename this to something like "optimizely-sdk.h"

int main() {
    /* initialization variables */
    char *sdkkey = "***REMOVED***";
    char *user_id = "0x123SomeUserId00";

    /* the feature we're checking */
    char *feature_name = "is_it_on_feature_key";

    OptimizelySDKInit(sdkkey, user_id);

    if (OptimizelySDKIsFeatureEnabled(feature_name)) {
        printf("The feature: %s is enabled\n", feature_name);
    }
}
