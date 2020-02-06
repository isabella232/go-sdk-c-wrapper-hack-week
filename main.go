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
//export Init
func Init(sdkkey, userId string) {
	var err error
	optlyClient, err = optly.Client(sdkkey)
	if err != nil {
		fmt.Printf("err: %s\n", err)
		os.Exit(1)
	}
	user = &entities.UserContext{ID: userId}
}

// checks to see if a feature is Enabled
//export IsFeatureEnabled
func IsFeatureEnabled(featureName string) bool {
	enabled, err := optlyClient.IsFeatureEnabled(featureName, *user)
	if err != nil {
		fmt.Printf("err: %s\n", err)
		os.Exit(1)
	}
	return enabled
}

func main() {
	Init("***REMOVED***", "0x123SomeUserId00")
	enabled := IsFeatureEnabled("is_it_on_feature_key")
	if enabled == true {
		fmt.Printf("is_feature_enabled: %b\n", enabled)
	}
}
