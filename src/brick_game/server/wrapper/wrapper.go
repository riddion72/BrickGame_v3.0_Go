package wrapper

/*
#cgo CXXFLAGS: -std=c++11
#cgo LDFLAGS: -L../../../obj -lwrapper
#include "../../controller/wrapper/wrapper.h"
*/
import "C"
import (
	"unsafe"
)

type GameController struct {
	ptr unsafe.Pointer
}

type GameName int

const (
	Snake GameName = iota
	Tetris
)

func NewGameController(gameName GameName) *GameController {
	ptr := C.createGameController(C.gameName_t(gameName))
	return &GameController{ptr: ptr}
}

func (g *GameController) Destroy() {
	C.destroyGameController(g.ptr)
}

func (g *GameController) GetUserInput() {
	C.getUserInput(g.ptr)
}

func (g *GameController) UpdateState() {
	C.updateState(g.ptr)
}

func (g *GameController) MakeStep() {
	C.makeStep(g.ptr)
}

func (g *GameController) UpdateUserAction(action int, hold bool) {
	holdInt := 0
	if hold {
		holdInt = 1
	}
	C.updateUserAction(g.ptr, C.int(action), C.int(holdInt))
}

type GameInfo struct {
	Field     [][]int `json:"field"`
	Next      [][]int `json:"next"`
	Score     int     `json:"score"`
	HighScore int     `json:"high_score"`
	Level     int     `json:"level"`
	Speed     int     `json:"speed"`
	Pause     int     `json:"pause"`
}

func (g *GameController) GetGameInfo(gg *GameInfo, game int) GameInfo {
	cInfo := C.getGameInfo(g.ptr)
	if cInfo.field != nil {
		for row := C.int(0); row < C.int(20); row++ {
			rowPtr := *(**C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(cInfo.field)) + uintptr(row*C.int(unsafe.Sizeof((*C.int)(nil))))))
			for col := C.int(0); col < C.int(10); col++ {
				gg.Field[row][col] = int(*(*C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(rowPtr)) + uintptr(col*C.int(unsafe.Sizeof(C.int(0)))))))
				// log.Println(int(*(*C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(rowPtr)) + uintptr(col*C.int(unsafe.Sizeof(C.int(0))))))))
			}
		}
		if game == 0 {
			for row := C.int(0); row < C.int(5); row++ {
				rowPtr := *(**C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(cInfo.next)) + uintptr(row*C.int(unsafe.Sizeof((*C.int)(nil))))))
				for col := C.int(0); col < C.int(5); col++ {
					gg.Next[row][col] = int(*(*C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(rowPtr)) + uintptr(col*C.int(unsafe.Sizeof(C.int(0)))))))
				}
			}
		}
	}
	gg.Score = int(cInfo.score)
	gg.HighScore = int(cInfo.high_score)
	gg.Level = int(cInfo.level)
	gg.Speed = int(cInfo.speed)
	gg.Pause = int(cInfo.pause)
	// cInfo.field
	// Конвертируем C структуру в Go структуру
	// Здесь нужно будет добавить код для корректного копирования массивов
	return *gg
}

// func main() {
// 	controller := NewGameController(1)
// 	defer controller.Destroy()

// 	controller.UpdateUserAction(1, true)
// 	info := controller.GetGameInfo()
// 	fmt.Printf("Score: %d\n", info.Score)
// }
