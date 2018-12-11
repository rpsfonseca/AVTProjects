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
        this.orthoScale = 50;
        this.topOrthoCamera = new THREE.OrthographicCamera(1, -1, 1, -1, 1, 1000);
        this.updateOrthoCamera(this.screenDimensions);

        this.topPerspectiveCamera = this.buildCamera(this.screenDimensions);
        this.topPerspectiveCamera.position.y = 15;
        this.topPerspectiveCamera.position.z = 3;
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

        this.mainLight = new THREE.PointLight(0xFFFFFF, 1.5, 2000);
        this.mainLight.position.set(1, 5, 0);
        var textureLoader = new THREE.TextureLoader();
        var lensFlare = new THREE.Lensflare();
        lensFlare.addElement(new THREE.LensflareElement(textureLoader.load("textures/flare0.png"), 120, 0.2));
        lensFlare.addElement(new THREE.LensflareElement(textureLoader.load("textures/flare1.png"), 70, 0.6));
        lensFlare.addElement(new THREE.LensflareElement(textureLoader.load("textures/flare2.png"), 185, 0.75));
        this.mainLight.add(lensFlare);
        this.scene.add(this.mainLight);
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
        const fieldOfView = 60;
        const nearPlane = 1;
        const farPlane = 100;
        const camera = new THREE.PerspectiveCamera(fieldOfView, aspectRatio, nearPlane, farPlane);

        return camera;
    }

    updateOrthoCamera({width, height}) {
        this.topOrthoCamera.left = width / -2 / this.orthoScale;
        this.topOrthoCamera.right = width / 2 / this.orthoScale;
        this.topOrthoCamera.top = height / 2 / this.orthoScale;
        this.topOrthoCamera.bottom = height / -2 / this.orthoScale;
        this.topOrthoCamera.position.y = 15;
        this.topOrthoCamera.position.z = 3;
        this.topOrthoCamera.lookAt(0, 0, 0);
        this.topOrthoCamera.updateProjectionMatrix();
    }

    createSceneSubjects(scene)
    {
        //var car = new SceneNode("car_with_wheels", null, scene);
        var table = new SceneNode("table", new THREE.MeshBasicMaterial({color:new THREE.Color(0xDDDD00)}), scene);
        var tree = new Tree();
        var tree_node = new SceneNode("billboard", tree.material, scene);



        const sceneSubjects =
        [
            //car,
            table,
            tree_node
        ];

        //console.log("JDJDJDJD: " + table.object);
        return sceneSubjects;
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
            //table,
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

        for(let i=0; i < this.sceneNodes.length; i++)
        {
            //this.sceneNodes[i].dirty = true;
            this.sceneNodes[i].update(elapsedTime, this.camera);
            //console.log(this.sceneNodes[i]);
        }
        

        for(let w=0; w < this.sceneObjects.length; w++)
        {
            this.sceneObjects[w].update(elapsedTime);
        }

        /*
        for(let i=0; i < this.sceneEntities.length; i++)
        {
            this.sceneEntities[i].update(elapsedTime, camera);
        }
        
        
        for(let w=0; w < this.sceneObjects.length; w++)
        {
            this.sceneObjects[w].update(elapsedTime);
        }
        */
        
        
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
}
