KeyboardState	= function()
{
    // to store the current state
    this.keyCodes	= {};
    
    for (var key in KeyboardState.ALIAS)
    {
        this.keyCodes[ key ] = false;
    }

    // create callback to bind/unbind keyboard events
    var self	= this;
    this._onKeyDown	= function(event){ self._onKeyChange(event, true); };
    this._onKeyUp	= function(event){ self._onKeyChange(event, false);};

    // bind keyEvents
    document.addEventListener("keydown", this._onKeyDown, false);
    document.addEventListener("keyup", this._onKeyUp, false);
}

/**
 * To stop listening of the keyboard events
 */
KeyboardState.prototype.destroy	= function()
{
    // unbind keyEvents
    document.removeEventListener("keydown", this._onKeyDown, false);
    document.removeEventListener("keyup", this._onKeyUp, false);
}

KeyboardState.ALIAS	= {
    '1'         : 1,
    '2'         : 2,
    '3'         : 3,
    'n'         : 3,
    'h'         : 3,
    'c'         : 3,
    's'         : 3,
    'ArrowLeft'		: 37,
    'ArrowUp'		: 38,
    'ArrowRight'		: 39,
    'ArrowDown'		: 40,
    'space'		: 32,
    'pageup'	: 33,
    'pagedown'	: 34,
    'tab'		: 9
};

/**
 * to process the keyboard dom event
 */
KeyboardState.prototype._onKeyChange	= function(event, pressed)
{
    // log to debug
    //console.log("onKeyChange", event, pressed, event.keyCode);

    // update this.keyCodes
    var keyCode		= event.key;

    // If we receive an event that key was pressed but wasn't pressed previously, means it's a one time press
    // console.log("PRESSED VALUE: " + pressed);
    // console.log("KEY CODES VALUE: " + this.keyCodes[keyCode]);
    if (pressed == true && this.keyCodes[keyCode] == false)
    {
        // console.log("KEY CODE: " + keyCode);
        switch (keyCode)
        {
            // change camera
            case '1':
                console.log("CHANGE CAMERA TO 1");
                //Application::getInstance()->changeCamera(1);
                break;
            case '2':
                console.log("CHANGE CAMERA TO 2");
                //Application::getInstance()->changeCamera(2);
                break;
            case '3':
                console.log("CHANGE CAMERA TO 3");
                //Application::getInstance()->changeCamera(3);
                break;
            case 'n':
                console.log("TOGGLE DIRECTIONAL LIGHT");
                //Application::getInstance()->renderer->directionalLightOn = !Application::getInstance()->renderer->directionalLightOn;
                break;
            case 'c':
                console.log("TOGGLE POINT LIGHTS");
                //Application::getInstance()->renderer->pointLightsOn = !Application::getInstance()->renderer->pointLightsOn;
                break;
            case 'h':
                console.log("TOGGLE SPOT LIGHTS");
                //Application::getInstance()->renderer->spotLightsOn = !Application::getInstance()->renderer->spotLightsOn;
                break;
            case 's':
                console.log("TOGGLE PAUSE");
                gameState.paused = !gameState.paused;
                break;
            case 'ArrowUp' :
                console.log("Acelerar");
                //Application::getInstance()->getGameState().paused = !Application::getInstance()->getGameState().paused;
                break;

                
        }
    }

    this.keyCodes[keyCode]	= pressed;
}

/**
 * query keyboard state to know if a key is pressed of not
 *
 * @param {String} keyDesc the description of the key. format : modifiers+key e.g shift+A
 * @returns {Boolean} true if the key is pressed, false otherwise
 */
KeyboardState.prototype.pressed	= function(keyDesc)
{
    var keys	= keyDesc.split("+");
    for(var i = 0; i < keys.length; i++)
    {
        var key	= keys[i];
        var pressed;
        if( Object.keys(KeyboardState.ALIAS).indexOf( key ) != -1 )
        {
            pressed	= this.keyCodes[ KeyboardState.ALIAS[key] ];
        }
        else
            {
            pressed	= this.keyCodes[key.toUpperCase().charCodeAt(0)]
        }
        if(!pressed)
        {
            return false;
        }
    };
    return true;
}