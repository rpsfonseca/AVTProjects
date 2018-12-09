function SceneNode(scene)
{
    //const radius = 2;
    //const mesh = new THREE.Mesh(new THREE.IcosahedronBufferGeometry(radius, 2), new THREE.MeshStandardMaterial({ flatShading: true }));
    var geometry = new THREE.BoxGeometry(1, 1, 1);
    var material = new THREE.MeshBasicMaterial({color: 0x00ff00});
    const mesh = new THREE.Mesh(geometry, material);

    mesh.position.set(0, 0, -20);

    scene.add(mesh);

    this.update = function(time)
    {
        const scale = Math.sin(time)+2;
        mesh.scale.set(scale, scale, scale);
    }
}

function SceneNode(meshFileName, material, scene)
{
    var object = null;
    // instantiate a loader
    var loader = new THREE.OBJLoader();

    // load a resource
    loader.load(
        // resource URL
        'models/'+ meshFileName +'.obj',
        // called when resource is loaded
        function ( obj )
        {
            var _material = new THREE.MeshBasicMaterial({color: 0x00ff00});
            obj.position.set(0, 0, -50);
            if (material != null)
            {
                _material = material;

                obj.position.set(0, 0, -10);
                obj.rotation.set(0, 180, 0);
            }

            obj.traverse(function(child)
            {
                if (child instanceof THREE.Mesh)
                {
                    child.material = _material;
                }
            });

            object = obj;
            //object.position.set(0, 0, -20);

            console.log(object);

            scene.add(object);

        },
        // called when loading is in progresses
        function ( xhr )
        {
            console.log( ( xhr.loaded / xhr.total * 100 ) + '% loaded' );
        },
        // called when loading has errors
        function ( error ) {

            console.log( 'An error happened' );

        }
    );

    this.update = function(time)
    {
        const scale = Math.sin(time)+2;
        if (object != null)
        {
            //object.scale.set(scale, scale, scale);
        }
    }
}