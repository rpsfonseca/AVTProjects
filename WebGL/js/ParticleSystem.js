class Particle {
    constructor(pos, vel, accel, life, fadeRate, tint) {
        this.position = pos;
        this.velocity = vel;
        this.acceleration = accel;
        this.life = life;
        this.fadeRate = fadeRate;
        this.tint = tint;

        var geometry = new THREE.BufferGeometry();
        var vertices = new Float32Array([0.0, 0.0, 0.0]);
        geometry.addAttribute('position', new THREE.BufferAttribute(vertices, 3));
        this.material = new THREE.PointsMaterial({color: 0x333333, map: new THREE.TextureLoader().load("textures/particle.png"), transparent: true});
        this.mesh = new THREE.Points(geometry, this.material);
    }

    step(time) {
        this.velocity.add(this.acceleration.clone().multiplyScalar(time));
        this.position.add(this.velocity.clone().multiplyScalar(time));
        this.life -= time * this.fadeRate;
        this.mesh.position.copy(this.position);
        this.material.opacity = Math.min(1.0, this.life / 2);
    }
}

class ParticleSystem
{
    constructor(scene, position) {
        this.scene = scene;
        this.position = position.clone();

        this.maxLife = 3; // seconds
        this.particles = [];
        this.particleCount = 15;
        for(let i = 0; i < this.particleCount; i++) {
            this.particles[i] = this.generateParticle();
            this.scene.add(this.particles[i].mesh);
        }
    }

    generateParticle() {
        return new Particle(
            this.position,
            new THREE.Vector3(Math.random() * 0.5, 0.2 + Math.random() * 0.5, Math.random() * 0.5),
            new THREE.Vector3(0.04, 0.01, -0.02),
            1 + Math.random() * this.maxLife,
            1, // real time
            new THREE.Color(0xFFFFFF));
    }

    setPosition(pos) {
        this.position = pos.clone();
    }

    step(time) {
        for(let i = 0; i < this.particleCount; i++) {
            let p = this.particles[i];
            p.step(time);

            if(p.life <= 0) {
                this.scene.remove(p.mesh);
                this.particles[i] = this.generateParticle();
                this.scene.add(this.particles[i].mesh);
            }
        }
    }
}