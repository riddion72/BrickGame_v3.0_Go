import { applyRootStyles } from './src/utils.js';
import { GameBoard } from './src/game-board.js';
import { rootStyles, keyCodes } from './src/config.js';

applyRootStyles(rootStyles);
const gameBoard = new GameBoard(document.querySelector('#game-board'));

// Добавим расширенное логирование
console.log('Game Board Tiles:', gameBoard.tiles.length);
console.log('Game Board Element:', gameBoard.element);

// Явный вызов fetchState с расширенной отладкой
async function debugFetchState() {
    try {
        const response = await fetch('/api/state', {
            method: 'GET',
            headers: {
                'Accept': 'application/json'
            }
        });

        console.log('Fetch Response Status:', response.status);
        
        if (!response.ok) {
            const errorText = await response.text();
            console.error('Response Error:', errorText);
            throw new Error('Network response was not ok');
        }

        const gameState = await response.json();
        console.log('Received Game State:3', gameState.tiles);
        
        // Принудительный вызов updateState
        gameBoard.updateState(gameState);
    } catch (error) {
        console.error('Detailed Fetch Error:', error);
    }
}

// Первоначальный вызов с расширенной отладкой
document.addEventListener('DOMContentLoaded', () => {
    debugFetchState();

    // Периодическое обновление с отладкой
    setInterval(() => {
        debugFetchState();
    }, 100);
});

