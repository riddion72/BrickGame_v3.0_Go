/*
 * BrickGame
 *
 * BrickGame 3.0 REST API
 *
 * API version: 1.0
 * Generated by: Swagger Codegen (https://github.com/swagger-api/swagger-codegen.git)
 */
package main

import (
	"log"
	"net/http"

	// WARNING!
	// Change this to a fully-qualified import path
	// once you place this file into your project.
	// For example,
	//
	//    sw "github.com/myname/myrepo/go"
	//
	sw "server/swagger"
)

func main() {
	log.SetFlags(log.LstdFlags | log.Lshortfile)
	log.Println("Starting server...")

	router := sw.NewRouter()

	log.Println("Server will start on :8080")
	log.Fatal(http.ListenAndServe(":8080", router))
}
