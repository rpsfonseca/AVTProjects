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


//Global variables for entities and entity nodes
var cars = [];
var carNodes = [];
var cheerios = [];
var cheerioNodes = [];
var butters = [];
var butterNodes = [];
var oranges = [];
var orangeNodes = [];
var walls = []
var entities = [];
var entityNodes = [];

class SceneManager
{
    constructor(canvas) {
        this.canvas = canvas;

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
        this.controls.minDistance = 20;
        this.controls.maxDistance = 30;
        this.controls.maxPolarAngle = Math.PI / 2;
        this.controls.mouseButtons = {
            LEFT: THREE.MOUSE.LEFT,
            MIDDLE: THREE.MOUSE.MIDDLE,
        }
        this.controls.update();
        this.scene.add(this.camera);

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

        // configure particle system
        this.particleSystem = new ParticleSystem(this.scene, this.car.position);
  
        window.addEventListener('deviceorientation', e => this.setOrientationControls(e), true);

        // configure stereo vision
        this.stereoEffect = new THREE.StereoEffect(this.renderer);
        this.stereoEffect.setSize(this.screenDimensions.width, this.screenDimensions.height);
        this.useStereoEffect = false;

        this.createLight();
        this.createSpotLights();
        document.addEventListener("keydown", e => this.onKeyDown(e));
    }

    setOrientationControls(e) {
        console.log("setOrientationControls called");
        if (!e.alpha) {
          return;
        }

        console.log("Changing to deviceorientation controls");
        this.controls = new THREE.DeviceOrientationControls(camera, true);
        this.controls.connect();
        this.controls.update();

        element.addEventListener('click', fullscreen, false);

        window.removeEventListener('deviceorientation', setOrientationControls, true);
    }

    onKeyDown(e) {
        if(e.keyCode == TECLA_F) {
            if(this.scene.fog == null)
                this.scene.fog = this.fog;
            else
                this.scene.fog = null;
        } else if(e.keyCode == TECLA_V) {
            this.useStereoEffect = !this.useStereoEffect;
            this.onWindowResize();
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
        const nearPlane = 0.001;
        const farPlane = 1000;
        const camera = new THREE.PerspectiveCamera(fieldOfView, aspectRatio, nearPlane, farPlane);

        return camera;
    }

    updateOrthoCamera({width, height}) {
        this.topOrthoCamera.left = width / -2 / this.orthoScale;
        this.topOrthoCamera.right = width / 2 / this.orthoScale;
        this.topOrthoCamera.top = height / 2 / this.orthoScale;
        this.topOrthoCamera.bottom = height / -2 / this.orthoScale;
        this.topOrthoCamera.position.y = 200;
        this.topOrthoCamera.position.z = 0;
        this.topOrthoCamera.lookAt(0, 0, 0);
        this.topOrthoCamera.updateProjectionMatrix();
    }

    updateFollowCamera() {
        this.controls.target = this.car.position;
    }

    createEntities(scene)
    {
        var loader = new THREE.TextureLoader();
        var table = new SceneNode("table", new THREE.MeshPhongMaterial(
            {
                color: new THREE.Color(0xDDDD00),
                map: loader.load("textures/lightwood.png"),
                transparent: true,
                opacity: 0.5
            }),
            scene);
        var geometry = new THREE.PlaneBufferGeometry( 160, 132 );
        var mirrorSurface = new THREE.Reflector(geometry, {
            clipBias: 0.003,
            textureWidth: 1024,
            textureHeight: 1024,
            recursion: 1,
            color: 0xaaaaaa
        });
        mirrorSurface.position.y = 0.25;
        mirrorSurface.rotateX( - Math.PI / 2 );
        scene.add(mirrorSurface);

        //TODO trees
        var tree = new Tree();
        var tree_node = new SceneNode("billboard", tree.material, scene);

        //Car creation
        //this.createCar(scene, 0, 1, 0);
        var startPos = new THREE.Vector3(0, 1, -50);
        var carNode = new SceneNode("car_with_wheels", new THREE.MeshPhongMaterial({color:new THREE.Color(0x2222aa)}), scene);
        var car = new Car(carNode, startPos, 0);
        cars.push(car);
        console.log("Car created");

        //Track creation
        //Outer lines
        this.createStraightLine(scene, -70, 70, -60, -60, 1);
        this.createStraightLine(scene, -70, 70, 60, 60, 1);
        this.createStraightLine(scene, -70, -70, -60, 60, 0);
        this.createStraightLine(scene, 70, 70, -60, 60, 0);
        
        //Inner Lines
        this.createStraightLine(scene, -50, 50, -40, -40, 1);
        this.createStraightLine(scene, -50, 50, 40, 40, 1);
        this.createStraightLine(scene, -50, -50, -40, 40, 0);
        this.createStraightLine(scene, 50, 50, -40, 40, 0);
        console.log("Track created");
        
        //Butters
        this.createButter(scene, 10, 2, 10);
        this.createButter(scene, -20, 2, -30);
        this.createButter(scene, -20, 2, 30);
        this.createButter(scene, 20, 2, -30);
        this.createButter(scene, 20, 2, 30);
        console.log("Butters created");

        //Wall creation
        this.createWalls(LEVEL_WIDTH, LEVEL_HEIGHT);
        console.log("Walls created");

        //Oranges
        this.createOranges(scene, LEVEL_WIDTH, LEVEL_HEIGHT);
        console.log("Oranges created");

        this.sceneObjects =
        [
            car,
        ];
        this.car = car;

        this.sceneNodes = 
        [
            table,
            //tree_node
            carNode
        ];

        //Colidable entities
        entities = entities.concat(cars);
        entities = entities.concat(cheerios);
        entities = entities.concat(butters);
        entities = entities.concat(walls);
        entities = entities.concat(oranges);

        console.log("Scene Entities Created");
    }


    update(elapsedTime)
    {
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

        //carNodes[0].update(elapsedTime, this.camera);
        //cars[0].update(elapsedTime);
        
        for(let k=0; k < cheerios.length; k++)
        {   
            cheerioNodes[k].update(elapsedTime, this.camera);
            //cheerios[k].update(elapsedTime);
        }

        for(let f=0; f < butters.length; f++)
        {   
            butterNodes[f].obj.scale.set(1.8,2,3);  
            butterNodes[f].update(elapsedTime, this.camera);
            //butters[f].update(elapsedTime);
        }

        for(let h=0; h < oranges.length; h++)
        {   
            //orangeNodes[f].obj.scale.set(1.8,2,3);  
            orangeNodes[h].update(elapsedTime, this.camera);
            //butters[f].update(elapsedTime);
        }

        if(this.camera == this.followCamera){
            this.updateFollowCamera();
            this.controls.update(elapsedTime);
        }


        
        this.particleSystem.setPosition(this.car.position);
        this.particleSystem.step(elapsedTime);
        //COLLISION DETECTION
        // Por cada entidade
        for(let entity of entities){
            if(entity.isDisabled()){                // nao fazemos nada se foi disativada (ex: laranja fora do campo)
                continue;
            }

            var oldPos = entity.getPosition();      // Guardamos a sua posicao anterior
            entity.update(elapsedTime);                   // e atualizamos a sua posicao 
            
            if(oldPos == entity.getPosition()){     // Se a entidade nao se moveu nao precisamos de computar colisoes
                continue;                           // pois uma colisao tem de ter sempre 1 entidade a mover-se
            }

            var bounds = entity.getBoundingVolume();

            for(let collided of entities){
                if(collided.isDisabled()){          // nao fazemos nada se foi disativada 
                    continue;
                }
                if(entity == collided){ // Nao se pode colidir consigo propria
                    continue;
                }

                var bounds2 = collided.getBoundingVolume();

                // Se deteta uma colisao
                if(detectCollision(bounds,bounds2)){
                    // resolve a colisao 
                    this.handleCollision(oldPos,entity,collided);   // resolve colisao
                    //console.log("Colisao entre " + entity + "e " + collided);
                }
            }
        }
        
        
        //controls.center = new THREE.Vector3(0,0,-20);
        
        if(this.useStereoEffect)
            this.stereoEffect.render(this.scene, this.camera);
        else
            this.renderer.render(this.scene, this.camera);


        this.updateSpotLights();
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
        this.stereoEffect.setSize(width, height);
    }

    handleInput(){
        /*if(keyboard.isKeyPressed(TECLA_S)){
            keyboard.unpressKey(TECLA_S);
            if(!this.restartIsAllowed){
                this.togglePause();
            }

        }*/

        /***** CAMERA INPUTS *****/
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

        /***** LIGHT INPUTS *****/
        if(keyboard.isKeyPressed(TECLA_N)){
            keyboard.unpressKey(TECLA_N);
            if(LIGHT.light == false){
                LIGHT.light = true;
                this.createLight();
            }
            else{
                LIGHT.light = false;
                this.createLight();
            }
        }
        else if(keyboard.isKeyPressed(TECLA_C)){
            keyboard.unpressKey(TECLA_C);
            this.ligaVelas();
        }
        else if(keyboard.isKeyPressed(TECLA_H)){
            keyboard.unpressKey(TECLA_H);
            this.ligaSpotLights();
        }

        /*else if(keyboard.isKeyPressed(TECLA_G)){
            keyboard.unpressKey(TECLA_G);
            this.changeShadow();

        } else if(keyboard.isKeyPressed(TECLA_L)){
            keyboard.unpressKey(TECLA_L);
            this.undoLight();
        }

         else if(keyboard.isKeyPressed(TECLA_R)){
            keyboard.unpressKey(TECLA_R);
            if(this.restartIsAllowed){
                this.restart();
            }
        }      
        */ 
    }


    /****** ENTITY CREATION FUNCTIONS *****/
    createStraightLine(scene, xin, xfin, zin, zfin, dir) {       
        var z = zin;
        var x = xin;

        if (dir) { //De -x para +x
            for (x = xin; x< xfin; x += 4) {
                this.createCheerio(scene, x, 1, z);
            }
        }
        else { //De -z para +z
            for (z = zin; z < zfin; z += 4) {
                this.createCheerio(scene, x, 1, z);
            }
        }
    }

    createCheerio(scene, x, y, z)
    {
        var startPos = new THREE.Vector3(x,y,z);
        var cheerioNode = new SceneNode("torus", new THREE.MeshPhongMaterial({color:new THREE.Color(LIGHT_YELLOW)}), scene);
        var cheerio = new Cheerio(cheerioNode, startPos);

        cheerios.push(cheerio);
        cheerioNodes.push(cheerioNode);
    }

    createButter(scene, x, y, z)
    {
        var startPos = new THREE.Vector3(x,y,z);
        var butterNode = new SceneNode("untitled", new THREE.MeshPhongMaterial({color:new THREE.Color(WHITE)}), scene);
        var butter = new Butter(butterNode, startPos);

        butters.push(butter);
        butterNodes.push(butterNode);
    }

    /*createCar(scene, x, y, z)
    {
        var startPos = new THREE.Vector3(x,y,z);
        var carNode = new SceneNode("car_with_wheels", new THREE.MeshBasicMaterial({color:new THREE.Color(DARK_BLUE)}), scene);
        var car = new Car(carNode, startPos);
        console.log("Car created");

        cars.push(car);
        carNodes.push(carNode);
    }*/

    createOranges(scene, levelWidth, levelHeight)
    {
        for(let i=0; i<NUM_ORANGES; i++){
            var orangeNode = new SceneNode("orange", new THREE.MeshPhongMaterial({color:new THREE.Color(ORANGE)}), scene);
            var orange = new Orange(orangeNode, levelWidth, levelHeight);
            oranges.push(orange);
            orangeNodes.push(orangeNode);
            //console.log("criei laranja");
        }
    }

    createWalls(levelWidth, levelHeight)
    {
        var halfWidth = levelWidth/2;
        var halfHeight = levelHeight/2;
        walls.push(new Wall(-halfWidth-1000,-halfWidth,-1000,1000,-halfHeight-1000,halfHeight+1000));
        walls.push(new Wall(halfWidth,halfWidth+1000,-1000,1000,-halfHeight-1000,halfHeight+1000));
        walls.push(new Wall(-halfWidth-1000,halfWidth+1000,-1000,1000,halfHeight,halfHeight+1000));
        walls.push(new Wall(-halfWidth-1000,halfWidth+1000,-1000,1000,-halfHeight-1000,-halfHeight))
    }

    /*
    int wallId = 0;
    void Scene::createWall(int minX_, int minY_, int minZ_, int maxX_, int maxY_, int maxZ_)
    {
        Wall* wall = new Wall(minX_, minY_, minZ_, maxX_, maxY_, maxZ_);

        std::string id = "wall" + std::to_string(wallId);
        wallId++;

        walls.insert(std::pair<std::string, Wall*>(id, wall));
    }
    */
    

    /***** COLLISION DETECTION FUNCTIONS *****/

    // funcao que chama a funcao de tratamento de colisao certa
    handleCollision(oldPos,entity1,entity2){
        if(entity1.type == TYPE.CAR){
            if(entity2.type == TYPE.CHEERIO){
                this.handleCarCheerioCollision(oldPos,entity1,entity2);
            }
            else if(entity2.type == TYPE.ORANGE || entity2.type == TYPE.WALL){
                this.handleCarOrangeWallCollision(entity1,entity2);
            } 
            else if(entity2.type == TYPE.BUTTER){
                this.handleCarButterCollision(oldPos,entity1,entity2);
            }
            // else if(entity2.type == TYPE.WALL){
            //  this.handleCarWallCollision(oldPos,entity1,entity2);
            // }
        } 
        if(entity1.type == TYPE.CHEERIO && entity2.type == TYPE.CHEERIO){
            this.handleCheerioCheerioCollision(oldPos,entity1,entity2);
        }
        if(entity1.type == TYPE.ORANGE && entity2.type == TYPE.WALL){
            this.handleOrangeWallCollision(oldPos,entity1,entity2);
        }

        if(entity2.type == TYPE.CAR){
            if(entity1.type == TYPE.CHEERIO){
                this.handleCheerioCarCollision(oldPos,entity1,entity2);
            }
        }
    }


    handleOrangeWallCollision(oldPos,orange,wall){
        orange.kill();
    }

    // Lida colisao entre cheerios
    handleCheerioCheerioCollision(oldPos,cheerio1,cheerio2){
        cheerio1.velocity /= 2;                 // cheerio que embateu perde metade da velocidade
        cheerio2.velocity = cheerio1.velocity;  // cheerio que sofreu o choque ganha metade da velocidade
        cheerio2.orientation = cheerio1.orientation.clone(); // e movimenta-se na direcao que o cheerio 1 andava 
        cheerio1.orientation.multiplyScalar(-1); // o cheerio 1 passa o mover-se na direção oposta

        // calcula a posicao valida para cheerio 1
        var newPos = this.calculateNewPos(oldPos,cheerio1,cheerio2.getBoundingVolume());
        cheerio1.setPosition(newPos);
    }

    // Lida colisao entre cheerio e carro
    handleCheerioCarCollision(oldPos,cheerio,car){
        cheerio.orientation.multiplyScalar(-1);
        cheerio.velocity;

        // calcula posicao valida para o cheerio
        var newPos = this.calculateNewPos(oldPos,cheerio,car.getBoundingVolume());
        cheerio.setPosition(newPos);
    }

    // 
    // Nota a diferenca destas funcoes bem do facto de oldPos pode referir-se ao carro ou ao cheerio
    // Ou seja temos que validar a posicao do cheerio numa, e na outra temos que validar a posicao do carro
    // Alem disso, a handleCheerioCarCollision e a funcao chamada quando o cheerio "embate" no carro, ou seja, quando o cheerio tem uma velocidade muito superior ao do carro
    // 

    // Lida colisao entre caro e cheerio
    handleCarCheerioCollision(oldPos,car,cheerio){
        cheerio.orientation = car.orientation.clone();
        cheerio.velocity = car.velocity;
        car.velocity = car.velocity/2;

        // calcula a posicao valida para o carro
        var newPos = this.calculateNewPos(oldPos,car,cheerio.getBoundingVolume());
        car.setPosition(newPos);
    }

    // Lida com a colisao do carro e a manteiga
    handleCarButterCollision(oldPos,car,butter){
        car.velocity = 0;   // O carro perde a velocidade toda

        // calcula a posicao valida para o carro
        var newPos = this.calculateNewPos(oldPos,car,butter.getBoundingVolume());
        car.setPosition(newPos);    
    }

    // Lida com a colisao do carro e a manteiga
    handleCarOrangeWallCollision(car,orangeOrWall){
        if(orangeOrWall.type == TYPE.ORANGE && orangeOrWall.dead){
            return;
        }

        //var startingPos = this.level.getCarStartingPosition();
        //var startingOrientation = this.level.getCarStartingOrientation();

        //var startingPos = car.getInitialPosition();
        //var startingOrientation = this.level.getCarStartingOrientation();


        car.reset();    // faz reset da posicao e orientacao
        //car.setPosition(startingPos);   // mete a posicao de inicio
        car.object.position.setY(1);  // eleva o carro para estar em cima da pista
        //car.rotate(startingOrientation);// roda no direcao certa
        

        //Handling number of lifes
        /*nVidasPerdidas++;
        if(nVidasPerdidas >= 4){
            this.scene2.remove(this.hud.getCar(nVidasPerdidas).object);
            this.toggleGameOver();
        }
        else{
            this.scene2.remove(this.hud.getCar(nVidasPerdidas).object);
        }
        */
    }


    // Funcao que dada a posicao antiga, a nova posicao (entity.getPosition()) e a
    // caixa de volume que originou a colisao, calcula a posicao valida (ou seja onde nao ocorre colisao)
    // O algoritmo funciona por aproximacao, este pega no ponto inicial, no ponto final e calcula o ponto medio
    // de seguida verifica se a entidade nesse ponto sofre colisao. 
    // Se sofrer vai repetir o algoritmo entre o ponto inicial e o ponto medio, se nao sofrer vai repetir o algoritmo
    // entre o ponto medio e o ponto final
    // O algoritmo repete um numero finito de vezes, aproximando cada vez mais o ponto pretendido
    // Por exemplo, para 10 repeticoes, o erro entre o ponto ideal e o ponto pretendido sera ~0.1% (Calculo: (1/2)^n_repeticoes)
    calculateNewPos(oldPos,entity,bounds2){
        const REPETITIONS = 10;
        var tentativePos = entity.getPosition();
        var passes = 0;
        var high = 1;
        var low = 0;
        var boundingVolume;
        var alpha;
        var pos;
        var goodPoint = low;    // Mantemos sempre uma variavel que aponta para o ultimo valor em que nao ha colisao, assumindo que entiy nao sofre colisao em
        
        while(passes < REPETITIONS){
            alpha = (high + low) / 2;
            pos = oldPos.clone().lerp(tentativePos,alpha);

            entity.setPosition(pos);
            boundingVolume = entity.getBoundingVolume();

            if(detectCollision(boundingVolume,bounds2)){
                high = alpha;
            } else {
                goodPoint = low;
                low = alpha;
            }

            passes += 1;
        }

        // Se houver colisao neste ponto 
        if(detectCollision(boundingVolume,bounds2)){
            alpha = goodPoint;  // Voltamos atras e usamos a variavel em que garantidamente nao ha colisao
            pos = oldPos.clone().lerp(tentativePos,alpha);

            entity.setPosition(pos);
        }


        return pos; // Posicao valida que nao colide com bounds2
    }

    /***** LIGHT FUNCTIONS *****/
    createLight(){
        if(LIGHT.light == true){
            this.scene.add(light1);
        }
        else if(LIGHT.light == false){
            this.scene.remove(light1);
        }
    }

    ligaVelas(){
        if(LIGHT.velas == false){
            LIGHT.velas = true;
            for(var i = 0; i<NUM_VEL; i++){
                this.scene.add(velas[i]);
            }
        }
        else{
            for(var i = 0; i<NUM_VEL; i++){
                this.scene.remove(velas[i]);
            }
            LIGHT.velas = false;
        }   
    }

    createSpotLights(){
        //Car spotlights
        this.spotLight1Target = new THREE.Object3D();
        this.spotLight2Target = new THREE.Object3D();
        this.spotLight1Target.position.set(0.25,1.25,2);
        this.spotLight2Target.position.set(0.25,1.25,-2);
        
        this.spotLight1 = new THREE.SpotLight(0xa0a0a0);
        this.spotLight2 = new THREE.SpotLight(0xa0a0a0);
        this.spotLight1.position.set(0,2,2);
        this.spotLight2.position.set(0,2,-2);
        this.spotLight1.target = this.spotLight1Target;
        this.spotLight2.target = this.spotLight2Target;
        this.spotLight1.angle = 0.6;
        this.spotLight2.angle = 0.6;

        this.scene.add(this.spotLight1);
        this.scene.add(this.spotLight2);
        this.scene.add(this.spotLight1Target);
        this.scene.add(this.spotLight2Target);
    }

    ligaSpotLights(){
        if(LIGHT.spotLight == false){
            LIGHT.spotLight = true;
            this.scene.add(this.spotLight1);
            this.scene.add(this.spotLight2);
            this.scene.add(this.spotLight1Target);
            this.scene.add(this.spotLight2Target);
        }
        else{
            this.scene.remove(this.spotLight1);
            this.scene.remove(this.spotLight2);
            this.scene.remove(this.spotLight1Target);
            this.scene.remove(this.spotLight2Target);
            LIGHT.spotLight = false;
        }   
    }

    updateSpotLights() {
        var rot = new THREE.Quaternion(0, 0, 0, 0);
        this.car.object.getWorldQuaternion(rot);

        var x = this.car.position.x;
        var y = this.car.position.y;
        var z = this.car.position.z;

        this.spotLight1.position.copy(this.car.position);
        this.spotLight2.position.copy(this.car.position);

        this.spotLight1Target.position.set(x+0.1, y, z+0.1);
        this.spotLight2Target.position.set(x+0.1, y, z-0.1);

        this.spotLight1Target.setRotationFromQuaternion(rot); //Update rotation 

                
        
        //this.spotLight1.target = this.car.object.spotLight1Target;
        //this.spotLight2.target = this.car.object.spotLight2Target;
                   

                    
    }

        

}
