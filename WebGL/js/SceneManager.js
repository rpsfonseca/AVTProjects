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

function SceneManager(canvas)
{
    const clock = new THREE.Clock();

    const screenDimensions =
    {
        width: canvas.width,
        height: canvas.height
    }

    const scene = buildScene();
    const renderer = buildRender(screenDimensions);
    const camera = buildCamera(screenDimensions);
    const sceneSubjects = createSceneSubjects(scene);

    function buildScene()
    {
        const scene = new THREE.Scene();
        scene.background = new THREE.Color("#000");

        return scene;
    }

    function buildRender({ width, height })
    {
        const renderer = new THREE.WebGLRenderer( {canvas: canvas, antialias: true, alpha: true});
        const DPR = (window.devicePixelRatio) ? window.devicePixelRatio : 1;
        renderer.setPixelRatio(DPR);
        renderer.setSize(width, height);

        renderer.gammaInput = true;
        renderer.gammaOutput = true;

        return renderer;
    }

    function buildCamera({ width, height })
    {
        const aspectRatio = width / height;
        const fieldOfView = 60;
        const nearPlane = 1;
        const farPlane = 100;
        const camera = new THREE.PerspectiveCamera(fieldOfView, aspectRatio, nearPlane, farPlane);

        return camera;
    }

    function createSceneSubjects(scene)
    {
        //var car = new SceneNode("car_with_wheels", null, scene);
        var table = new SceneNode("table", null, scene);
        var tree = new Tree();
        var tree_node = new SceneNode("billboard", tree.material, scene);
        const sceneSubjects =
        [
            //car,
            table,
            tree_node
        ];
        console.log("JDJDJDJD: " + table.object);
        return sceneSubjects;
    }

    this.update = function()
    {
        const elapsedTime = clock.getElapsedTime();

        for(let i=0; i < sceneSubjects.length; i++)
        {
            sceneSubjects[i].update(elapsedTime);
        }

        renderer.render(scene, camera);
    }

    this.onWindowResize = function ()
    {
        const { width, height } = canvas;

        screenDimensions.width = width;
        screenDimensions.height = height;

        camera.aspect = width / height;
        camera.updateProjectionMatrix();

        renderer.setSize(width, height);
    }
}
