class Tree
{
    constructor()
    {
        // super(props);
        this.tag = "billboard";
        this.sprite = new THREE.TextureLoader().load('textures/tree.png');
        this.material = new THREE.MeshBasicMaterial({ alphaMap: new THREE.TextureLoader().load('textures/tree_alphamap.png'), map: this.sprite, alphaTest: 0.5, transparent: true });
    }

}