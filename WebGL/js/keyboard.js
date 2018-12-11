"use strict"

/* Variavel global keyboard, guarda informacao
sobre que teclas estao currentemente a serem pressionadas
*/
var keyboard = (function (){
	var keys = {};
	var stop_change = {};

	function onKeyUp(e){
		keys[e.keyCode] = false;
		stop_change[e.keyCode] = false;
	}

	function onKeyDown(e){
		if(stop_change[e.keyCode]){
			return;
		}
		keys[e.keyCode] = true;
	}

	window.addEventListener("keyup", onKeyUp);
	window.addEventListener("keydown", onKeyDown);		

	return {
		/*	
			Verifica se uma tecla esta currentemente a ser pressionada
		*/
		isKeyPressed: function(keyCode){
			var key;
			if((key = keyCode) in keys){
				return keys[key];
			} else {
				return false;
			}
		},

		unpressKey: function(keyCode){
			stop_change[keyCode] = true;
			keys[keyCode] = false;
		}
	};
}());