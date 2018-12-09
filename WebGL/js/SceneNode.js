function SceneNode(scene)
{
    //const radius = 2;
    //const mesh = new THREE.Mesh(new THREE.IcosahedronBufferGeometry(radius, 2), new THREE.MeshStandardMaterial({ flatShading: true }));
    var geometry = new THREE.BoxGeometry(1, 1, 1);
    var material = new THREE.MeshBasicMaterial({color: 0x00ff00});
    const mesh = new THREE.Mesh(geometry, material);

    mesh.position.set(0, 0, -20);

    scene.add(mesh);

    this.update = function(time, camera)
    {
        const scale = Math.sin(time)+2;
        mesh.scale.set(scale, scale, scale);
    }
}

function SceneNode(meshFileName, material, scene)
{
    var object = null;
    var tag = "object";
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
            obj.position.set(0, 0, 0);
            if (material != null)
            {
                _material = material;
                tag = "billboard";
                obj.position.set(0, 1.35, 0);
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

    this.update = function(time, camera)
    {
        const scale = Math.sin(time) + 2;
        if (object != null)
        {
            if (tag == "billboard")
            {
                //object.lookAt(new THREE.Vector3(camera.position.x, 0, -camera.position.z));
                //object.setRotationFromQuaternion(camera.quaternion);
                //object.rotateOnWorldAxis(new THREE.Vector3(0,1,0), 45 * Math.degToRad);
                /*var lookAt = new THREE.Vector3(0,0,1);
                var objToCamProj = new THREE.Vector3();
                var upAux = new THREE.Vector3();
                var angleCosine;

                var pos = new THREE.Vector3(0,0,0);
                //console.log(object);
                pos = pos.setFromMatrixPosition(object.matrixWorld);
                var auxMatrix  = new THREE.Matrix4();
                var tempPos = new THREE.Vector3(pos.x, 0, pos.z);
                auxMatrix = auxMatrix.setPosition(tempPos);
                // objToCamProj is the vector in world coordinates from the local origin to the camera
                // projected in the XZ plane
                objToCamProj.x = camera.position.x - pos.x;
                objToCamProj.y = 0;
                objToCamProj.z = camera.position.z - pos.z;


                // normalize both vectors to get the cosine directly afterwards
                objToCamProj = objToCamProj.normalize();

                // easy fix to determine wether the angle is negative or positive
                // for positive angles upAux will be a vector pointing in the
                // positive y direction, otherwise upAux will point downwards
                // effectively reversing the rotation.

                upAux = lookAt.cross(objToCamProj);

                // compute the angle
                angleCosine = lookAt.dot(objToCamProj);

                // perform the rotation. The if statement is used for stability reasons
                // if the lookAt and v vectors are too close together then |aux| could
                // be bigger than 1 due to lack of precision
                if ((angleCosine < 0.99990) && (angleCosine > -0.9999))
                {
                    //rotate(MODEL, acos(angleCosine) * 180 / 3.14, upAux[0], upAux[1], upAux[2]);
                    var matTemp = new THREE.Matrix4();
                    matTemp = matTemp.makeRotationAxis(upAux, Math.acos(angleCosine));
                    //command->transform = glm::rotate(command->transform, glm::acos(angleCosine), upAux);
                    auxMatrix = auxMatrix.multiply(matTemp);
                }
                //command->transform = glm::mat4(1);
                //command->transform[3] = pos;
                auxMatrix = auxMatrix.setPosition(pos);
                //console.log(auxMatrix);
                object.applyMatrix(auxMatrix);*/
            }
        }
    }
}