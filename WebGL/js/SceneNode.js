class SceneNode
{
    constructor(meshFileName, material, scene) {
        this.geometry = new THREE.BoxGeometry(1, 1, 1);
        this.material = material;

        var tag = "object";
        // instantiate a loader
        var loader = new THREE.OBJLoader();

        // load a resource
        loader.load(
            // resource URL
            'models/'+ meshFileName +'.obj',
            // called when resource is loaded
            obj =>
            {
                obj.position.set(0, 0, 0);

                this.mesh = obj.children[0];
                this.mesh.material = this.material;

                scene.add(this.mesh);

            },
            // called when loading is in progresses
            xhr =>
            {
                console.log( ( xhr.loaded / xhr.total * 100 ) + '% loaded' );
            },
            // called when loading has errors
            error => {
                console.log( 'An error happened: ' + error );
            }
        );
    }

    update(time, camera)
    {
        // const scale = Math.sin(time)+2;
        // this.mesh.scale.set(scale, scale, scale);
    }
}