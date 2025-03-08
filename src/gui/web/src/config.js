export const GAME_BOARD_WIDTH = 10;
export const GAME_BOARD_HEIGHT = 20;

export const rootStyles = {
    '--tile-size': '20px',
    '--tile-color': '#eee',
    '--tile-active-color': '#222',
    '--game-board-width': GAME_BOARD_WIDTH,
    '--game-board-height': GAME_BOARD_HEIGHT,
    '--game-board-gap': '2px',
    '--game-board-background': '#333',
};

export const keyCodes = {
    up: ['ArrowUp', 'KeyW', 'KeyI'],
    right: ['ArrowRight', 'KeyD', 'KeyL'],
    down: ['ArrowDown', 'KeyS', 'KeyK'],
    left: ['ArrowLeft', 'KeyA', 'KeyJ'],
    enter: ['Enter'],
    pause: ['KeyP'],
    terminate: ['KeyQ'],
    action: ['Space'],
};

async function sendKeyAction(action) {
    try {
        const response = await fetch('/api/actions', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({ action: action })
        });
        const data = await response.json();

        // Проверяем, если сервер прислал редирект
        if (data.status === 'redirect') {
            window.location.href = data.redirectUrl;
            return;
        }
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }

        // Обновляем состояние игры после действия
        gameBoard.fetchState();
    } catch (error) {
        console.error('Error sending key action:', error);
    }
};