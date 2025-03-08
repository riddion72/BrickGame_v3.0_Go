/*
 * BrickGame
 *
 * BrickGame 3.0 REST API
 *
 * API version: 1.0
 * Generated by: Swagger Codegen (https://github.com/swagger-api/swagger-codegen.git)
 */

package swagger

import (
	"html/template"
	"log"
	"net/http"
	"runtime/debug"

	"github.com/gorilla/mux"
)

type Route struct {
	Name        string
	Method      string
	Pattern     string
	HandlerFunc http.HandlerFunc
}

type Routes []Route

var templates *template.Template

func NewRouter() *mux.Router {
	router := mux.NewRouter().StrictSlash(true)

	// Добавьте явную отладку роутинга
	router.Use(func(next http.Handler) http.Handler {
		return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
			log.Printf("Incoming Request: %s %s", r.Method, r.URL.Path)
			next.ServeHTTP(w, r)
		})
	})

	// CORS middleware
	router.Use(func(next http.Handler) http.Handler {
		return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
			w.Header().Set("Access-Control-Allow-Origin", "*")
			w.Header().Set("Access-Control-Allow-Methods", "GET, POST, OPTIONS")
			w.Header().Set("Access-Control-Allow-Headers", "Content-Type")

			if r.Method == "OPTIONS" {
				w.WriteHeader(http.StatusOK)
				return
			}

			next.ServeHTTP(w, r)
		})
	})

	// Статические файлы
	staticHandler := http.StripPrefix("/static/",
		http.FileServer(http.Dir("gui/web/")))
	router.PathPrefix("/static/").Handler(staticHandler)
	router.Use(globalRecoveryMiddleware)
	// Загрузка шаблонов
	templates = template.Must(template.ParseGlob("gui/web/html/*.html"))

	// Логирование загруженных шаблонов
	if templates != nil {
		for _, tmpl := range templates.Templates() {
			log.Printf("Loaded template: %s", tmpl.Name())
		}
	}

	// Регистрация всех маршрутов с логированием
	for _, route := range routes {
		handler := route.HandlerFunc

		log.Printf("Registering route: %s %s", route.Method, route.Pattern)

		router.
			Methods(route.Method).
			Path(route.Pattern).
			Name(route.Name).
			Handler(handler)
	}

	return router
}

func Index(w http.ResponseWriter, r *http.Request) {
	log.Print("Im here")
}

var routes = Routes{
	Route{
		"Index",
		"GET",
		"/api/",
		Index,
	},

	Route{
		"ActionsPost",
		"POST",
		"/api/actions",
		ActionsPost,
	},

	Route{
		"GamesGet",
		"GET",
		"/api/games",
		GamesGet,
	},

	Route{
		"GamesGameIdPost",
		"POST",
		"/api/games/{gameId}",
		GamesGameIdPost,
	},

	Route{
		"GetID",
		"GET",
		"/api/games/{gameId}",
		GamesGameIdPost,
	},

	Route{
		"StateGet",
		"GET",
		"/api/state",
		StateGet,
	},
}

func globalRecoveryMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		defer func() {
			if err := recover(); err != nil {
				log.Printf("PANIC RECOVERED: %v", err)
				debug.PrintStack()
				http.Error(w, "Internal Server Error", http.StatusInternalServerError)
			}
		}()
		next.ServeHTTP(w, r)
	})
}
