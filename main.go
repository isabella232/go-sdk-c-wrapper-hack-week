package main

import "C"

import (
	"fmt"
	optly "github.com/optimizely/go-sdk"
	"github.com/optimizely/go-sdk/pkg/client"
	"github.com/optimizely/go-sdk/pkg/entities"
	"os"
)

var optimizelyFactory *client.OptimizelyFactory

var optlyClient *client.OptimizelyClient

//var optlyClient *client.OptimizelyClient
var user *entities.UserContext

// initalizes the Optimizely SDK
//export Init
func Init(sdkkey, userId string) {
	optimizelyFactory = &client.OptimizelyFactory{SDKKey: "***REMOVED***"}
	var err error
	optlyClient, err = optly.Client("***REMOVED***")
	//optlyClient, err = client.OptimizelyClient("***REMOVED***")
	if err != nil {
		fmt.Printf("err: %s\n", err)
		os.Exit(1)
	}
	user = &entities.UserContext{ID: userId}
	//user := optly.UserContext(userId, nil)
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
	fmt.Println("vim-go")

	Init("***REMOVED***", "0x123SomeUserId00")
	enabled := IsFeatureEnabled("is_it_on_feature_key")
	if enabled == true {
		fmt.Printf("is_feature_enabled: %b\n", enabled)
	}

	/*
		optimizelyFactory := &client.OptimizelyFactory{SDKKey: "***REMOVED***"}

		optlyClient, err := optimizelyFactory.Client()
		if err != nil {
			fmt.Printf("err: %s\n", err)
			os.Exit(1)
		}

		user := entities.UserContext{ID: "0x123SomeUserId00"}

		enabled, _ := optlyClient.IsFeatureEnabled("is_it_on_feature_key", user)
		if enabled == true {
			fmt.Printf("is_feature_enabled: %b\n", enabled)
		}
	*/
}
