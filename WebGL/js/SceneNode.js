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