var scene = new THREE.Scene();
var camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);

var renderer = new THREE.WebGLRenderer();
renderer.setSize(window.innerWidth, window.innerHeight);
document.body.appendChild(renderer.domElement);

var geometry = new THREE.BoxBufferGeometry(1, 1, 1);

var uniforms = {
    color: {value: new THREE.Color(0xFFFF00)},
    baseTexture: {value: new THREE.TextureLoader().load("bump.png")},
    normalTexture: {value: new THREE.TextureLoader().load("bump.png")},
    LightSource: {value:
        {pos: new THREE.Vector3(2, 2, 2),
         ambient: new THREE.Color(0x111111),
         diffuse: new THREE.Color(0xeeeeee),
         specular: new THREE.Color(0xffffff)}},
    Material: {value:
        {diffuse: new THREE.Vector3(1, 0, 0),
         specular: new THREE.Vector3(1, 0, 1),
         shininess: 25}},
};
var material = new THREE.ShaderMaterial({
    uniforms: uniforms,
    vertexShader: document.getElementById('bumpMappingVertexShader').textContent,
    fragmentShader: document.getElementById('bumpMappingFragmentShader').textContent
});

spotLight = new THREE.SpotLight( 0xffffbb, 2 );
spotLight.position.set( 0.5, 0, 1 );
spotLight.position.multiplyScalar( 700 );
scene.add( spotLight );

THREE.BufferGeometryUtils.computeTangents(geometry); // compute tangents for bump mapping shader
var cube = new THREE.Mesh(geometry, material);
scene.add(cube);

camera.position.z = 5;

function animate() {
    requestAnimationFrame(animate);
    
    cube.rotation.x += 0.01;
    cube.rotation.y += 0.01;

	renderer.render(scene, camera);
}
animate();