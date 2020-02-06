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
#include "optimizely-sdk.h"
/*
 * extern void Init(GoString p0, GoString p1);
 * extern GoUint8 IsFeatureEnabled(GoString p0);
 */

int main() {
    /*
    GoInt a = 12;
    GoInt b = 99;
    printf("awesome.Add(12,99) = %d\n", Add(a, b));
    printf("awesome.Cosine(1) = %f\n", (float)(Cosine(1.0)));
    GoInt data[6] = {77, 12, 5, 99, 28, 23};
    GoSlice nums = {data, 6, 6};
    Sort(nums);
    for (int i = 0; i < 6; i++){
        printf("%d,", ((GoInt *)nums.data)[i]);
    }
      */

    /* initialization variables */
    char *sdkkey = "***REMOVED***";
    GoString key = {sdkkey, strlen(sdkkey)};
    char *user_id = "0x123SomeUserId00";
    GoString user = {user_id, strlen(user_id)};

    /* the feature we're checking */
    char *feature_name = "is_it_on_feature_key";
    GoString name = {feature_name, strlen(feature_name)};

    Init(key, user);

    if (IsFeatureEnabled(name)) {
        printf("The feature: %s is enabled\n", feature_name);
    }
}
