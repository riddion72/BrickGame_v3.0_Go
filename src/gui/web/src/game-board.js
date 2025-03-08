const GAME_BOARD_WIDTH = 10; // или любое другое значение
const GAME_BOARD_HEIGHT = 20; 

import { keyCodes } from './config.js'; 

async function sendKeyAction(action) {
    try {
        const response = await fetch('/api/actions', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ action: action })
        });

        if (!response.ok) {
            throw new Error('Network response was not ok');
        }

        // Обновляем состояние игры после действия
        // Используем this.gameBoard, если это метод класса
        gameBoard.fetchState();
    } catch (error) {
        console.error('Error sending key action:', error);
    }
}

export class GameBoard {
    constructor($gameBoard) {
        this.element = $gameBoard;
        this.tiles = [];
        this.nextTiles = [];
    
        // Создание основного игрового поля
        for (let y = 0; y < GAME_BOARD_HEIGHT; y++) {
            for (let x = 0; x < GAME_BOARD_WIDTH; x++) {
                const $tile = document.createElement('div');
                $tile.classList.add('tile');
                $tile.id = `position-${x}-${y}`;
                this.tiles.push($tile);
                this.element.append($tile);
            }
        }
    
        // Создание поля следующего элемента
        const nextFieldElement = document.querySelector('.next-field');
        this.nextTiles = []; // Очистим массив перед созданием
        for (let y = 0; y < 5; y++) {
            for (let x = 0; x < 5; x++) {
                const $tile = document.createElement('div');
                $tile.classList.add('tile');
                $tile.id = `next-position-${x}-${y}`;
                this.nextTiles.push($tile);
                nextFieldElement.append($tile);
            }
        }
    }

    updateState(gameState) {
        console.log('UpdateState Called');
        console.log('Received Game State:', gameState);

        // Обновляем основное поле
        if (!gameState || !gameState.field) {
            console.error('Некорректное состояние игры');
            return;
        }

        // Обновляем существующие тайлы основного поля
        for (let y = 0; y < GAME_BOARD_HEIGHT; y++) {
            for (let x = 0; x < GAME_BOARD_WIDTH; x++) {
                const tileIndex = y * GAME_BOARD_WIDTH + x;
                const tile = this.tiles[tileIndex];
                
                if (!tile) {
                    console.error(`Tile not found for index ${tileIndex}`);
                    continue;
                }

                if (gameState.field[y][x] !== 0) {
                    tile.classList.add('active');
                } else {
                    tile.classList.remove('active');
                }
            }
        }
    
        // Обновляем поле следующего элемента
        const nextFieldElement = document.querySelector('.next-field');
        
        // Обновляем существующие тайлы следующего поля
        for (let y = 0; y < 5; y++) {
            for (let x = 0; x < 5; x++) {
                const tileIndex = y * 5 + x;
                const tile = this.nextTiles[tileIndex];
                
                if (!tile) {
                    console.error(`Next tile not found for index ${tileIndex}`);
                    continue;
                }

                if (gameState.next[y][x] !== 0) {
                    tile.classList.add('active');
                } else {
                    tile.classList.remove('active');
                }
            }
        }
    }

    async fetchState() {
        console.group('Fetch State');
        try {
            console.log('Fetching from:', 'http://localhost:8080/api/state');
            
            const response = await fetch('http://localhost:8080/api/state', {
                method: 'GET',
                headers: {
                    'Accept': 'application/json',
                    'Cache-Control': 'no-cache'
                }
            });

            console.log('Response Status:', response.status);
            console.log('Response Headers:', Object.fromEntries(response.headers.entries()));

            if (!response.ok) {
                const errorText = await response.text();
                console.error('Response Error:', errorText);
                throw new Error(`HTTP error! status: ${response.status}`);
            }

            const contentType = response.headers.get('content-type');
            console.log('Content Type:', contentType);

            if (!contentType || !contentType.includes('application/json')) {
                const text = await response.text();
                console.error('Non-JSON response:', text);
                throw new Error('Response is not JSON');
            }

            const gameState = await response.json();
            console.log('Received Game State:2', gameState.tiles);
            
            this.updateState(gameState);
        } catch (error) {
            console.error('Fetch Error Details:', {
                message: error.message,
                name: error.name,
                stack: error.stack
            });
        } finally {
            console.groupEnd();
        }
    }
    
    getTile(x, y) {
        return this.tiles[y * GAME_BOARD_WIDTH + x];
    }

    enableTile(x, y) {
        this.getTile(x, y).classList.add('active');
    }

    disableTile(x, y) {
        this.getTile(x, y).classList.remove('active');
    }


    updateState(gameState) {
        console.log('UpdateState Called');
        console.log('Received Game State:', gameState);
        // Обновляем основное поле
        if (!gameState || !gameState.field) {
            console.error('Некорректное состояние игры');
            return;
        }
            for (let y = 0; y < GAME_BOARD_HEIGHT; y++) {
                for (let x = 0; x < GAME_BOARD_WIDTH; x++) {
                    const tileIndex = y * GAME_BOARD_WIDTH + x;
                    const tile = this.tiles[tileIndex];
                    
                    if (!tile) {
                        console.error(`Tile not found for index ${tileIndex}`);
                        continue;
                    }
    
                    if (gameState.field[y][x] !== 0) {
                        tile.classList.add('active');
                    } else {
                        tile.classList.remove('active');
                    }

                }
            }
        
    
        // Обновляем поле следующего элемента
        const nextField = document.querySelector('.next-field');
        
            // Очищаем предыдущее состояние
            nextField.innerHTML = '';
    
            // Создаем новые тайлы для следующего поля
            for (let y = 0; y < 5; y++) {
                for (let x = 0; x < 5; x++) {
                    const $tile = document.createElement('div');
                    $tile.classList.add('tile');
                    
                    if (gameState.next[y][x] !== 0) {
                        $tile.classList.add('active');
                    } else {
                        $tile.classList.remove('active');
                    }
                    
                    nextField.appendChild($tile);
                }
            }
        
    }
}

// В main скрипте
document.addEventListener('DOMContentLoaded', () => {
    const gameBoard = new GameBoard(document.querySelector('#game-board'));
    gameBoard.innerHTML = '';
    // Первоначальная загрузка состояния игры
    gameBoard.fetchState();

    // Обработчик нажатий клавиш
    document.addEventListener('keydown', (event) => {
        // Предотвращаем стандартное поведение клавиш
        document.body.focus();

        console.log('Key pressed:', event.code);
    
        event.preventDefault();

        // Обработка направлений
        if (keyCodes.up.includes(event.code)) {
            console.log('up');
            sendKeyAction('up');
        }
        if (keyCodes.right.includes(event.code)) {
            console.log('right');
            sendKeyAction('right');
        }
        if (keyCodes.down.includes(event.code)) {
            console.log('down');
            sendKeyAction('down');
        }
        if (keyCodes.left.includes(event.code)) {
            console.log('left');
            sendKeyAction('left');
        }
        if (keyCodes.enter.includes(event.code)) {
            console.log('enter');
            sendKeyAction('enter');
        }
        if (keyCodes.pause.includes(event.code)) {
            console.log('pause');
            sendKeyAction('pause');
        }
        if (keyCodes.action.includes(event.code)) {
            console.log('action');
            sendKeyAction('action');
        }
        if (keyCodes.terminate.includes(event.code)) {
            console.log('terminate');
            handleGameAction('terminate');
        }
        if (keyCodes.exit.includes(event.code)) {
            console.log('exit');
            handleGameAction('exit');
        }
    });
});

function handleGameAction(action) {
    fetch('/api/actions', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({ action: action })
    })
    .then(response => response.json())
    .then(data => {
        // Проверяем, если пришел редирект
        if (data.status === 'redirect') {
            window.location.href = data.url;
        }
    });
}

// Обработчики клавиш остаются прежними
// document.addEventListener('keydown', function(event) {
//     switch(event.key) {
//         case 'q':
//             handleGameAction('terminate');
//             break;
//         case 'e':
//             handleGameAction('exit');
//             break;
//         // Другие существующие обработчики клавиш
//     }
// });