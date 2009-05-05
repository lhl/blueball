size(500, 500)
speed(20)

try:
    boids = ximport("boids")
except:
    boids = ximport("__init__")
    reload(boids)

def setup():     
    
    # Create 3 flocks each with 10 boids.
    # Each flock crowds around the center of the canvas.
    global flocks
    flocks = []
    for i in range(3):
        flock = boids.flock(5, 0, 0, WIDTH, HEIGHT)
        flock.goal(WIDTH/2, HEIGHT/2, 0)
        flocks.append(flock)
    
def draw():

    background(0.2)
    
    fill(0.8)
    fontsize(20)
    w = textwidth("STATUE")
    text("STATUE", WIDTH/2-w/2, HEIGHT/2)

    # Update each flock.
    global flocks
    for flock in flocks:
        flock.update(goal=40)
        
        # Draw a grey arrow for each boid in a block.
        # Radius and opacity depend on the boids z-position.
        for boid in flock:
            r = 10 + boid.z * 0.25
            alpha = 0.5 + boid.z*0.01
            fill(0.6, 0.6, 0.6, alpha)
            rotate(-boid.angle)
            arrow(boid.x-r/2, boid.y-r/2, r)
            reset()