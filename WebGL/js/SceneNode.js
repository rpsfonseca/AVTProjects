class SceneNode
{
    constructor(meshFileName, material, scene) {
        this.geometry = new THREE.BoxGeometry(1, 1, 1);
        this.material = material;
        this.scene = scene;

        this.position = new THREE.Vector3(0, 0, 0);
        this.rotation = new THREE.Quaternion(0, 0, 0, 0);
        this.scale = new THREE.Vector3(1, 1, 1);
        this.mirrorScale = new THREE.Vector3(1, -1, 1);

        this.dirty = false; //If the node needs update

        var tag = "object";
        // instantiate a loader
        var loader = new THREE.OBJLoader();

        // load a resource
        loader.load(
            // resource URL
            'models/'+ meshFileName +'.obj',
            // called when resource is loaded
            
            /*obj =>
            {
                obj.position.set(0, 0, 0);

                this.mesh = obj.children[0];
                this.mesh.material = this.material;

                scene.add(this.mesh);

            },*/


            obj =>
            {
                obj.position.set(0, 0, 0);
                obj.material = this.material;
                //obj.scale = this.scale;
                //obj.position = this.position;

                this.obj = obj;

                this.obj.children.forEach(element => {
                    element.material = this.material;
                });

                scene.add(this.obj);

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
        //if(this.dirty){
            this.obj.position.copy(this.position); //Update position
            this.obj.setRotationFromQuaternion(this.rotation); //Update rotation 
        //}
        
        //this.obj.scale.set(10,1,10);
        //console.log(this.obj.scale);
        //TODO update scale
    }


    /*
    void SceneNode::setScale(glm::vec3 _scale)
    {
        scale = _scale;
        dirty = true;
    }

    //Should object be reflected?
    void SceneNode::setMirrored(bool _mirrored)
    {
        mirrored = _mirrored;
        dirty = true;
    }
    */
}