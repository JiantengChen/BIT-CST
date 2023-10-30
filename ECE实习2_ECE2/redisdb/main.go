package main

import (
	"fmt"
	"os"

	"redisdb/config"
	"redisdb/lib/logger"
	"redisdb/lib/utils"
	RedisServer "redisdb/redis/server"
	"redisdb/tcp"
	// "redisdb/config"
	// "redisdb/lib/logger"
	// "redisdb/lib/utils"
	// RedisServer "redisdb/redis/server"
	// "redisdb/tcp"
)

var banner = `
 ____  _____ ____ ___ ____  ____  ____  
|  _ \| ____|  _ \_ _/ ___||  _ \| __ ) 
| |_) |  _| | | | | |\___ \| | | |  _ \ 
|  _ <| |___| |_| | | ___) | |_| | |_) |
|_| \_\_____|____/___|____/|____/|____/ 
`

var defaultProperties = &config.ServerProperties{
	Bind:           "0.0.0.0",
	Port:           6399,
	AppendOnly:     false,
	AppendFilename: "",
	MaxClients:     1000,
	RunID:          utils.RandString(40),
}

func fileExists(filename string) bool {
	info, err := os.Stat(filename)
	return err == nil && !info.IsDir()
}

func main() {
	print(banner)
	logger.Setup(&logger.Settings{
		Path:       "logs",
		Name:       "godis",
		Ext:        "log",
		TimeFormat: "2006-01-02",
	})
	configFilename := os.Getenv("CONFIG")
	if configFilename == "" {
		if fileExists("redis.conf") {
			config.SetupConfig("redis.conf")
		} else {
			config.Properties = defaultProperties
		}
	} else {
		config.SetupConfig(configFilename)
	}
	err := tcp.ListenAndServeWithSignal(&tcp.Config{
		Address: fmt.Sprintf("%s:%d", config.Properties.Bind, config.Properties.Port),
	}, RedisServer.MakeHandler())
	if err != nil {
		logger.Error(err)
	}
}
