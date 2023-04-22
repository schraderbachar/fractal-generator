# How it works

- Program renders fractals (Mandelbrot/Julia)
- Option for standard grayscale output or random colors
- Option for setting image height, width, min/max real/imaginary values (Mandelbrot), max iterations (Mandelbrot/Julia), and real/imaginary offsets (Julia)
- Outputs a `.ppm` image file

# Function Overviews

**mandelbrot**
_Params_: Scaled Real Value, Scaled Imaginary value, Max Iterations
_Description_: Performs a Mandelbrot algorithm to calculate iterations per each point across the image file

**julia**
_Params_: Real Offset, Imaginary Offset, Scaled Real Value, Scaled Imaginary Value, Max Iterations, Escape Radius
_Description_: Calculates iterations per each point based on Julia algorithm

**scaleReal**
_Params_: Real Value, Image Width, Minimum Range, Maximum Range
_Description_: Takes a point and it's image width to scale it to fit a given range.

**scaleImaginary**
_Params_: Imaginary Value, Image Width, Minimum Range, Maximum Range
_Description_: Takes a point and it's image width to scale it to fit a given range.

### How to run

in the terminal type `make`

Then type `./fractal` and then follow the command prompts. If you want to use default values just hit enter
