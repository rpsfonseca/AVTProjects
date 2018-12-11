class Game
{
    constructor()
    {
        this.canvas = document.getElementById("canvas");
        this.sceneManager = new SceneManager(this.canvas);
        this.keyboard = new KeyboardState();
        this.hud = new HUD();
        this.bindEventListeners();
    }

    bindEventListeners()
    {
        window.onresize = () => this.resizeCanvas();
        this.resizeCanvas();
    }

    resizeCanvas()
    {
        this.canvas.style.width = '100%';
        this.canvas.style.height= '100%';

        this.canvas.width  = this.canvas.offsetWidth;
        this.canvas.height = this.canvas.offsetHeight;

        this.sceneManager.onWindowResize(this.canvas);
    }

    loop()
    {
        requestAnimationFrame(this.loop.bind(this));
        if( this.keyboard.pressed("left") )
        {
            console.log("Pressed left");
        }
        if(!gameState.paused)
            this.sceneManager.update();
        this.hud.step();

        return this;
    }
}