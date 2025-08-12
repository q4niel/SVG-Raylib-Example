import os
import math
import svgwrite

def squash_stretch(frame):
    """
Calculate rx and ry for the ellipse based on frame to simulate squash/stretch.
We'll simulate:
- Squash (wider and shorter) at frames 0 and 9 (touching ground)
- Stretch (narrower and taller) mid-air (around frame 4-5)
- Normal shape otherwise
    """
    # Normalize frame to 0..1 bounce cycle (0 and 1 = ground contact)
    t = frame / (NUM_FRAMES - 1)

    # Use sine wave to simulate bounce timing
    bounce = abs(math.sin(t * math.pi))  # 0 at ground, 1 at top

    # Squash factor at ground (t=0 or 1)
    squash = 1 + (1 - bounce) * 0.2  # wider horizontally near ground
    stretch = 1 - (1 - bounce) * 0.5  # shorter vertically near ground

    # Stretch factor mid-air (t=0.5)
    stretch_factor = 1 + bounce * 0.5  # taller vertically mid-air
    squash_factor = 1 - bounce * 0.2  # narrower horizontally mid-air

    # Blend squash/stretch smoothly
    rx = NORMAL_RX * (squash if bounce < 0.5 else squash_factor)
    ry = NORMAL_RY * (stretch if bounce < 0.5 else stretch_factor)

    return rx, ry

def y_position(frame):
    """
Simple parabola for vertical bounce movement from ground (y=GROUND_Y)
to peak height (y=GROUND_Y - 40).
    """
    t = frame / (NUM_FRAMES - 1)
    height = 40
    # Parabolic arc: y = ground - 4 * height * t * (1 - t)
    y = GROUND_Y - 4 * height * t * (1 - t)
    return y

if __name__ == "__main__":
    os.chdir(os.path.abspath(os.path.dirname(__file__)))
    buildDir: str = "./circle_anim"
    os.mkdir(buildDir)

    # Canvas size
    WIDTH, HEIGHT = 100, 100
    # Ground level (y coordinate)
    GROUND_Y = 80
    # Normal radius for the circle
    NORMAL_RX, NORMAL_RY = 20, 20

    # Number of frames
    NUM_FRAMES = 60

    for frame in range(NUM_FRAMES):
        dwg = svgwrite.Drawing(f'{buildDir}/{frame+1}.svg', size=(WIDTH, HEIGHT))

        rx, ry = squash_stretch(frame)
        cy = y_position(frame)

        dwg.add(dwg.ellipse(center=(WIDTH/2, cy), r=(rx, ry), fill='red'))
        dwg.save()