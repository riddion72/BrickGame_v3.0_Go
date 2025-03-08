package main

// #include <stdlib.h>
// #include <string.h>
// #include <stdint.h>
// #include "../../common/header.h"
import "C"

import (
	"bufio"
	"math"
	"math/rand"
	"os"
	"strconv"
	"unsafe"
)

type Status uint8

const (
	StatusSTART Status = iota
	StatusMOVE
	StatusPAUSE
	StatusEND
)

const SCORE_FILE_RACE = "race_score.txt"
const PLAYER_CAR_POS = 16
const CAR_WIDTH = 3
const DEFAULT_SPEED = 10

var Game *C.GameInfo_t

var State Status

var RaceCar [4][3]uint8 = [4][3]uint8{
	{0, 1, 0},
	{5, 1, 5},
	{0, 1, 0},
	{5, 1, 5}}

var RivalCar [4][3]uint8 = [4][3]uint8{
	{0, 2, 0},
	{3, 2, 3},
	{0, 2, 0},
	{3, 2, 3}}

var CarPos int8

var TakeHold bool = false

var StateTable [4][10]func()

var RivalCarCoords [15][3]int8

//export InitRace
func InitRace() {
	Game = createGameInfo()
	State = StatusSTART
	CarPos = 0
	initializeStateTable()
}

//export UpdateGameInfo
func UpdateGameInfo() *C.GameInfo_t {
	return Game
}

//export UserInput
func UserInput(action C.int, hold C.int) {
	if hold == C.int(0) {
		TakeHold = false
	} else {
		TakeHold = true
	}
	if StateTable[State][action] != nil {
		StateTable[State][action]()
	}
}

func createGameInfo() *C.GameInfo_t {

	game := (*C.GameInfo_t)(C.malloc(C.size_t(unsafe.Sizeof(C.GameInfo_t{}))))
	if game == nil {
		return nil
	}

	game.field = nil
	game.next = nil
	game.score = 0
	game.level = 0
	game.high_score = 0
	game.speed = 0
	game.pause = 0

	return game
}

func initializeStateTable() {
	// START
	StateTable[StatusSTART][C.Start] = func() { start() }
	StateTable[StatusSTART][C.Terminate] = func() { exitGame() }
	StateTable[StatusSTART][C.Exit_game] = func() { exitGame() }
	// MOVE
	StateTable[StatusMOVE][C.Pause] = func() { pause() }
	StateTable[StatusMOVE][C.Terminate] = func() { exitGame() }
	StateTable[StatusMOVE][C.Exit_game] = func() { exitGame() }
	StateTable[StatusMOVE][C.Left] = func() { turnLeft() }
	StateTable[StatusMOVE][C.Right] = func() { turnRight() }
	StateTable[StatusMOVE][C.Action] = func() { nextStep() }
	StateTable[StatusMOVE][C.Up] = func() { forward() }
	// PAUSE
	StateTable[StatusPAUSE][C.Pause] = func() { pause() }
	StateTable[StatusPAUSE][C.Terminate] = func() { exitGame() }
	StateTable[StatusPAUSE][C.Exit_game] = func() { exitGame() }
	// END
	StateTable[StatusEND][C.Start] = func() { start() }
	StateTable[StatusEND][C.Terminate] = func() { exitGame() }
	StateTable[StatusEND][C.Exit_game] = func() { exitGame() }
}

func start() {
	if Game == nil {
		Game = createGameInfo()
	}
	CarPos = 0
	Game.field = (**C.int)(C.calloc(C.H_SIZE, C.size_t(unsafe.Sizeof((*C.int)(nil)))))
	Game.next = (**C.int)(C.calloc(C.H_SIZE, C.size_t(unsafe.Sizeof((*C.int)(nil)))))

	for i := C.int(0); i < C.H_SIZE; i++ {
		row := (*C.int)(C.calloc(C.W_SIZE, C.size_t(unsafe.Sizeof(C.int(0)))))
		ptr := (**C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(Game.field)) + uintptr(i*C.int(unsafe.Sizeof((*C.int)(nil))))))
		*ptr = row
	}

	for i := C.int(0); i < 5; i++ {
		row := (*C.int)(C.calloc(5, C.size_t(unsafe.Sizeof(C.int(0)))))
		ptr := (**C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(Game.next)) + uintptr(i*C.int(unsafe.Sizeof((*C.int)(nil))))))
		*ptr = row
	}

	Game.score = 0
	Game.level = 1
	Game.speed = 10
	Game.pause = 0
	RivalCarCoords = [15][3]int8{{0}}

	State = StatusMOVE
	loadScore()
}

func exitGame() {
	saveRecord()
	FreeGameInfo()
	State = StatusEND
}

func forward() {
	if TakeHold {
		Game.speed = (Game.speed / 2) + 1
		printField()
	}
}

func turnLeft() {
	if Game != nil {
		shiftPos(-1)
		printField()
	}
}

func turnRight() {
	if Game != nil {
		shiftPos(1)
		printField()
	}
}

func nextStep() {
	if Game.field != nil {
		shiftRivalCar()
		printField()
		Game.speed = (DEFAULT_SPEED - C.int(math.Sqrt(float64(Game.score/100)))) + 1
	}
}

func pause() {
	if Game.pause == C.int(1) {
		Game.pause = C.int(0)
		State = StatusMOVE
	} else {
		Game.pause = C.int(1)
		State = StatusPAUSE
	}
}

func printField() {
	clearField()
	checkHighScore()
	printRivalCar()
	putAndCheckCar(C.int(CarPos), PLAYER_CAR_POS, true, RaceCar)
}

func spawnRivalCar(coord int8) {
	if coord > 4 {
		for i := 0; i < 15; i++ {
			if RivalCarCoords[i][2] == 0 {
				RivalCarCoords[i][0] = int8(rand.Intn(CAR_WIDTH) * (C.W_SIZE / CAR_WIDTH))
				RivalCarCoords[i][1] = -4
				RivalCarCoords[i][2] = 1
				return
			}
		}
	}

}

func shiftRivalCar() {
	var ForvardRivalCarCoord int8 = C.H_SIZE
	for i := 0; i < 15; i++ {
		if RivalCarCoords[i][2] == 1 {
			RivalCarCoords[i][1] += 1
			if ForvardRivalCarCoord > RivalCarCoords[i][1] {
				ForvardRivalCarCoord = RivalCarCoords[i][1]
			}
			if RivalCarCoords[i][1] >= C.H_SIZE {
				RivalCarCoords[i][2] = 0
				Game.score += 100
			}
		}
	}
	spawnRivalCar(ForvardRivalCarCoord)
}

func printRivalCar() {
	for i := 0; i < 15; i++ {
		if RivalCarCoords[i][2] == 1 {
			putAndCheckCar(C.int(RivalCarCoords[i][0]), C.int(RivalCarCoords[i][1]), false, RivalCar)
		}
	}
}

func putAndCheckCar(col, row C.int, check bool, car [4][3]uint8) {
	for i := C.int(0); i < 3; i++ {
		for j := C.int(0); j < 4; j++ {
			if check && checkColision(row+j, i+col, (C.int)(car[j][i])) {
				State = StatusEND
				exitGame()
				return
			}
			if (C.int)(car[j][i]) != 0 {
				setFieldValue(row+j, i+col, (C.int)(car[j][i]))
			}
		}
	}
}

func checkColision(row, col, car C.int) bool {
	if row < 0 || row >= C.H_SIZE || col < 0 || col >= C.W_SIZE {
		return true
	}

	rowPtr := *(**C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(Game.field)) + uintptr(row*C.int(unsafe.Sizeof((*C.int)(nil))))))

	value := *(*C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(rowPtr)) + uintptr(col*C.int(unsafe.Sizeof(C.int(0))))))
	if value != 0 && car != 0 {
		return true
	}
	return false
}

func shiftPos(del int8) {
	if (CarPos+del) >= 0 && (CarPos+del) <= C.W_SIZE-CAR_WIDTH {
		CarPos = CarPos + del
	}
}

func loadScore() {
	file, err := os.Open(SCORE_FILE_RACE)
	defer file.Close()
	if err != nil {
		Game.high_score = 0
		return
	}
	scanner := bufio.NewScanner(file)
	scanner.Scan()
	score, err := strconv.Atoi(scanner.Text())
	if err != nil {
		Game.high_score = 0
		return
	}
	Game.high_score = (C.int)(score)
}

func checkHighScore() {
	if Game.high_score < Game.score {
		Game.high_score = Game.score
	}
}

func saveRecord() {
	file, err := os.OpenFile(SCORE_FILE_RACE, os.O_WRONLY, 0666)
	defer file.Close()
	if err != nil {
		Game.high_score = 0
		return
	}
	_, err = file.WriteString(strconv.Itoa((int)(Game.high_score)) + "\n")
	if err != nil {
		Game.high_score = 0
	}
}

func clearField() {
	if Game.field != nil {
		for i := C.int(0); i < C.H_SIZE; i++ {
			rowPtr := *(**C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(Game.field)) + uintptr(i*C.int(unsafe.Sizeof((*C.int)(nil))))))
			for j := C.int(0); j < C.W_SIZE; j++ {
				*(*C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(rowPtr)) + uintptr(j*C.int(unsafe.Sizeof(C.int(0)))))) = C.int(0)
			}
		}
	}
}

func setFieldValue(row, col, value C.int) {
	if row < 0 || row >= C.H_SIZE || col < 0 || col >= C.W_SIZE {
		return
	}
	rowPtr := *(**C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(Game.field)) + uintptr(row*C.int(unsafe.Sizeof((*C.int)(nil))))))
	*(*C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(rowPtr)) + uintptr(col*C.int(unsafe.Sizeof(C.int(0)))))) = value
}

//export FreeGameInfo
func FreeGameInfo() {
	if Game.field != nil && Game.next != nil {
		for i := C.int(0); i < C.H_SIZE; i++ {
			row := *(**C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(Game.field)) + uintptr(i*C.int(unsafe.Sizeof((*C.int)(nil))))))
			C.free(unsafe.Pointer(row))
		}
		for i := C.int(0); i < 5; i++ {
			row := *(**C.int)(unsafe.Pointer(uintptr(unsafe.Pointer(Game.next)) + uintptr(i*C.int(unsafe.Sizeof((*C.int)(nil))))))
			C.free(unsafe.Pointer(row))
		}

		C.free(unsafe.Pointer(Game.field))
		C.free(unsafe.Pointer(Game.next))
		Game.next = nil
		Game.field = nil
	}

}

func main() {}
