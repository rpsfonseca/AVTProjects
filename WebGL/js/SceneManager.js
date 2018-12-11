/*class SceneManager
{
    constructor(canvas)
    {
        this.screenDimensions =
        {
            width: canvas.width,
            height: canvas.height
        };

        this.clock = new THREE.Clock();

        this.scene = this.buildScene();
        this.renderer = this.buildRender(this.screenDimensions);
        this.camera = this.buildCamera(this.screenDimensions);
        this.sceneSubjects = this.createSceneSubjects(this.scene);
    }

    buildScene()
    {
        const scene = new THREE.Scene();
        scene.background = new THREE.Color("#000");

        return scene;
    }

    buildRender({ width, height })
    {
        const _renderer = new THREE.WebGLRenderer( {canvas: this.canvas, antialias: true, alpha: true});
        const DPR = (window.devicePixelRatio) ? window.devicePixelRatio : 1;
        _renderer.setPixelRatio(DPR);
        _renderer.setSize(this.screenDimensions.width, this.screenDimensions.height);

        _renderer.gammaInput = true;
        _renderer.gammaOutput = true;

        return _renderer;
    }

    buildCamera({ width, height })
    {
        const aspectRatio = this.screenDimensions.width / this.screenDimensions.height;
        const fieldOfView = 60;
        const nearPlane = 1;
        const farPlane = 100;
        const camera = new THREE.PerspectiveCamera(fieldOfView, aspectRatio, nearPlane, farPlane);

        return camera;
    }

    createSceneSubjects(scene)
    {
        const sceneSubjects =
            [
                //new SceneNode(scene),
                new SceneNode("car_with_wheels", this.scene)
            ];

        return sceneSubjects;
    }

    update()
    {
        const elapsedTime = this.clock.getElapsedTime();

        for(let i=0; i < this.sceneSubjects.length; i++)
        {
            this.sceneSubjects[i].update(elapsedTime);
        }

        this.renderer.render(this.scene, this.camera);
    }

    onWindowResize(canvas)
    {
        const { width, height } = canvas;

        this.screenDimensions.width = width;
        this.screenDimensions.height = height;

        this.camera.aspect = width / height;
        this.camera.updateProjectionMatrix();

        this.renderer.setSize(this.screenDimensions.width, this.screenDimensions.height);
    }
}*/

class SceneManager
{
    constructor(canvas) {
        this.canvas = canvas;
        this.clock = new THREE.Clock();

        this.screenDimensions =
        {
            width: canvas.width,
            height: canvas.height
        }

        this.scene = this.buildScene();
        this.renderer = this.buildRender(this.screenDimensions);

        // setup cameras
        this.orthoScale = 5;
        this.topOrthoCamera = new THREE.OrthographicCamera(1, -1, 1, -1, 0, 1000);
        this.updateOrthoCamera(this.screenDimensions);

        this.topPerspectiveCamera = this.buildCamera(this.screenDimensions);
        this.topPerspectiveCamera.position.y = 100;
        this.topPerspectiveCamera.position.z = 100;
        this.topPerspectiveCamera.lookAt(0, 0, 0);

        this.followCamera = this.buildCamera(this.screenDimensions);

        this.camera = this.followCamera;

        //this.sceneSubjects = this.createSceneSubjects(this.scene);
        this.createEntities(this.scene);
        this.controls = new THREE.OrbitControls(this.followCamera, this.renderer.domElement);
        //camera.position.set( 0, 0, 0 );
        //camera.lookAt(0,0,-20);
        this.controls.enableDamping = true; // an animation loop is required when either damping or auto-rotation are enabled
        this.controls.dampingFactor = 0.25;
        this.controls.screenSpacePanning = false;
        this.controls.minDistance = 15;
        this.controls.maxDistance = 500;
        this.controls.maxPolarAngle = Math.PI / 2;
        this.controls.mouseButtons = {
            LEFT: THREE.MOUSE.LEFT,
            MIDDLE: THREE.MOUSE.MIDDLE,
        }
        this.controls.update();

        // configure lens flare
        this.mainLight = new THREE.PointLight(0xFFFFFF, 1.5, 2000);
        this.mainLight.position.set(1, 5, 0);
        var textureLoader = new THREE.TextureLoader();
        var lensFlare = new THREE.Lensflare();
        lensFlare.addElement(new THREE.LensflareElement(textureLoader.load("textures/flare0.png"), 120, 0.2));
        lensFlare.addElement(new THREE.LensflareElement(textureLoader.load("textures/flare1.png"), 70, 0.6));
        lensFlare.addElement(new THREE.LensflareElement(textureLoader.load("textures/flare2.png"), 185, 0.75));
        this.mainLight.add(lensFlare);
        this.scene.add(this.mainLight);

        // configure fog
        this.fog = new THREE.Fog(0xaaaaaa, 1, 80);
        this.scene.fog = this.fog;

        document.addEventListener("keydown", e => this.onKeyDown(e));
    }

    onKeyDown(e) {
        if(e.keyCode == TECLA_F) {
            if(this.scene.fog == null)
                this.scene.fog = this.fog;
            else
                this.scene.fog = null;
        }
    }

    buildScene()
    {
        const scene = new THREE.Scene();
        scene.background = new THREE.Color("#000");

        return scene;
    }

    buildRender({ width, height })
    {
        const renderer = new THREE.WebGLRenderer( {canvas: this.canvas, antialias: true, alpha: true});
        const DPR = (window.devicePixelRatio) ? window.devicePixelRatio : 1;
        renderer.setPixelRatio(DPR);
        renderer.setSize(width, height);

        renderer.gammaInput = true;
        renderer.gammaOutput = true;

        return renderer;
    }

    buildCamera({ width, height })
    {
        const aspectRatio = width / height;
        const fieldOfView = 70;
        const nearPlane = 1;
        const farPlane = 1000;
        const camera = new THREE.PerspectiveCamera(fieldOfView, aspectRatio, nearPlane, farPlane);

        return camera;
    }

    updateOrthoCamera({width, height}) {
        /*this.topOrthoCamera.left = width / -2 / this.orthoScale;
        this.topOrthoCamera.right = width / 2 / this.orthoScale;
        this.topOrthoCamera.top = height / 2 / this.orthoScale;
        this.topOrthoCamera.bottom = height / -2 / this.orthoScale;
        this.topOrthoCamera.position.y = 15;
        this.topOrthoCamera.position.z = 3;
        this.topOrthoCamera.lookAt(0, 0, 0);
        this.topOrthoCamera.updateProjectionMatrix();*/
        this.topOrthoCamera.left = width / -2 / this.orthoScale;
        this.topOrthoCamera.right = width / 2 / this.orthoScale;
        this.topOrthoCamera.top = height / 2 / this.orthoScale;
        this.topOrthoCamera.bottom = height / -2 / this.orthoScale;
        this.topOrthoCamera.position.y = 200;
        this.topOrthoCamera.position.z = 0;
        this.topOrthoCamera.lookAt(0, 0, 0);
        this.topOrthoCamera.updateProjectionMatrix();
    
    }

    //TODO
    updateFollowCamera(){
        //Usar o sceneObjects[0] (carro), retirar de lá a posição do carro e colocar na camara
        var orientation = this.sceneObjects[0].getOrientation();
        var position = this.sceneObjects[0].getPosition();
            
        // a camera move-se 30 unidades para tras do carro
        orientation.multiplyScalar(-30);
        // e eleva-se 20 unidades para cima
        orientation.add(new THREE.Vector3(0,20,0));
        
        var resultingVector = orientation;
        var cameraPosition = position.clone().add(resultingVector);

        this.followCamera.position.copy(cameraPosition);
        this.followCamera.lookAt(position);
    }


    createEntities(scene)
    {
        var table = new SceneNode("table", new THREE.MeshBasicMaterial({color:new THREE.Color(0xDDDD00)}), scene);

        var tree = new Tree();
        var tree_node = new SceneNode("billboard", tree.material, scene);

        var carNode = new SceneNode("car_with_wheels", new THREE.MeshBasicMaterial({color:new THREE.Color(0x0000ff)}), scene);
        var startPosition = new THREE.Vector3(0, 1, 0);
        var car = new Car(carNode, startPosition, 0);
        console.log("Car created");

        var orangeNode = new SceneNode("orange", new THREE.MeshBasicMaterial({color:new THREE.Color(0xff0000)}), scene);
        var orange = new Orange(orangeNode, LEVEL_WIDTH, LEVEL_HEIGHT);
        console.log("Orange created");

        this.sceneObjects =
        [
            car,
            //orange
        ];

        this.sceneNodes = 
        [
            table,
            //tree_node,
            carNode,
            //orangeNode
        ];

        console.log("Scene Entities Created");
    }


    update()
    {
        const elapsedTime = this.clock.getDelta();
        this.controls.update();
        this.handleInput();

        for(let i=0; i < this.sceneNodes.length; i++)
        {
            //this.sceneNodes[i].dirty = true;

            if(i==0){ //Increase table size
                this.sceneNodes[i].obj.scale.set(10,1,10);
            }


            this.sceneNodes[i].update(elapsedTime, this.camera);
            //console.log(this.sceneNodes[i]);
        }
        

        for(let w=0; w < this.sceneObjects.length; w++)
        {
            this.sceneObjects[w].update(elapsedTime);
        }


        //TODO collision detection

        if(this.camera == this.followCamera){
            this.updateFollowCamera();
        }
        
        
        //controls.center = new THREE.Vector3(0,0,-20);
        this.renderer.render(this.scene, this.camera);
    }

    onWindowResize()
    {
        const { width, height } = this.canvas;

        this.screenDimensions.width = width;
        this.screenDimensions.height = height;

        this.camera.aspect = width / height;
        this.camera.updateProjectionMatrix();
        this.updateOrthoCamera(this.screenDimensions);

        this.renderer.setSize(width, height);
    }

    handleInput(){
        /*if(keyboard.isKeyPressed(TECLA_S)){
            keyboard.unpressKey(TECLA_S);
            if(!this.restartIsAllowed){
                this.togglePause();
            }

        }*/

        if(keyboard.isKeyPressed(TECLA_1)){
            keyboard.unpressKey(TECLA_1);
            this.camera = this.topOrthoCamera;
            this.updateOrthoCamera(this.screenDimensions);
        } 
        else if(keyboard.isKeyPressed(TECLA_2)){
            keyboard.unpressKey(TECLA_2);
            this.camera = this.topPerspectiveCamera;
        } 
        else if(keyboard.isKeyPressed(TECLA_3)){
            keyboard.unpressKey(TECLA_3);
            this.camera = this.followCamera;
        }
        /*if(keyboard.isKeyPressed(TECLA_N)){
            keyboard.unpressKey(TECLA_N);
            if(LIGHT.light == false){
                LIGHT.light = true;
                this.createLight();
            }
            else{
                LIGHT.light = false;
                this.createLight();
            }
        } else if(keyboard.isKeyPressed(TECLA_G)){
            keyboard.unpressKey(TECLA_G);
            this.changeShadow();

        } else if(keyboard.isKeyPressed(TECLA_L)){
            keyboard.unpressKey(TECLA_L);
            this.undoLight();

        } else if(keyboard.isKeyPressed(TECLA_C)){
            keyboard.unpressKey(TECLA_C);
            this.ligaVelas();
        } else if(keyboard.isKeyPressed(TECLA_R)){
            keyboard.unpressKey(TECLA_R);
            if(this.restartIsAllowed){
                this.restart();
            }
        }      
        */ 
    }
}
