package main

import "C"

import (
	"fmt"
	optly "github.com/optimizely/go-sdk"
	"github.com/optimizely/go-sdk/pkg/client"
	"github.com/optimizely/go-sdk/pkg/entities"
	"os"
)

var optlyClient *client.OptimizelyClient
var user *entities.UserContext

// initalizes the Optimizely SDK
func Init(sdkkey, userId string) {
	var err error
	optlyClient, err = optly.Client(sdkkey)
	if err != nil {
		fmt.Printf("err: %s\n", err)
		os.Exit(1)
	}
	user = &entities.UserContext{ID: userId}
}

//export OptimizelySDKInit
func OptimizelySDKInit(sdkkey *C.char, user_id *C.char) {
	Init(C.GoString(sdkkey), C.GoString(user_id))
}

// checks to see if a feature is Enabled
func IsFeatureEnabled(featureName string) bool {
	enabled, err := optlyClient.IsFeatureEnabled(featureName, *user)
	if err != nil {
		fmt.Printf("err: %s\n", err)
		os.Exit(1)
	}
	return enabled
}

//export OptimizelySDKIsFeatureEnabled
func OptimizelySDKIsFeatureEnabled(feature_name *C.char) int {
	if IsFeatureEnabled(C.GoString(feature_name)) {
		return 1
	} else {
		return 0
	}
}

func GetVariableString(featureName, variableKey string) string {
	s, err := optlyClient.GetFeatureVariableString(featureName, variableKey, *user)
	if err != nil {
		fmt.Printf("err: %s\n", err)
		os.Exit(1)
	}
	fmt.Printf("greeting: %s\n", s)
	return s
}

//export OptimizelySDKGetFeatureVariable
func OptimizelySDKGetFeatureVariable(feature_name *C.char, variable_key *C.char) *C.char {
	s := GetVariableString(C.GoString(feature_name), C.GoString(variable_key))
	return C.CString(s)
}

func main() {
	Init("EDmaiYBFz6LByqpm7yS9eJ", "0x123SomeUserId00")
	enabled := IsFeatureEnabled("is_it_on_feature_key")
	if enabled == true {
		fmt.Printf("is_feature_enabled: %b\n", enabled)
	}
	GetVariableString("is_it_on_feature_key", "greeting")
}
