class HUD
{
    step() {
        let el = document.getElementById("hudText");
        el.textContent = `Lives: ${gameState.lives} | Score: ${gameState.score}`;
        let pauseText = document.getElementById("pauseText");
        pauseText.style.visibility = gameState.paused ? "visible" : "hidden";
    }
}