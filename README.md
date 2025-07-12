# 3D Raytracer

A modern C++ raytracer implementation with support for multiple geometric primitives, lighting, and material systems.

## Features

### Geometric Primitives
- **Sphere**: Configurable radius and center position
- **Plane**: Defined by a point and two direction vectors
- **Triangle**: Three-point triangle mesh support
- **Cube**: Axis-aligned box with configurable size
- **Blob**: Metaball implementation using marching cubes algorithm

### Lighting System
- **Point Light**: Omnidirectional light source with position and intensity
- **Ambient lighting**: Global illumination support
- **Multiple light sources**: Support for complex lighting setups

### Materials and Textures
- **Uniform Texture**: Solid color materials
- **Plastic Materials**: Realistic plastic shading
- **Metal Materials**: Metallic surface properties
- **Configurable material properties**: Ambient, diffuse, and specular coefficients

### Rendering Features
- **Ray-object intersection**: Precise mathematical intersection calculations
- **Surface normals**: Accurate normal computation for all primitives
- **Camera system**: Configurable camera position, target, and field of view
- **Anti-aliasing**: Multi-sampling for smooth edges
- **PPM output**: Standard image format output

## Project Structure

```
raytracer/
├── include/                 # Header files
│   ├── geometry/           # Mathematical primitives
│   ├── image/              # Image handling and color management
│   ├── light/              # Lighting system
│   ├── logger/             # Logging utilities
│   ├── motor/              # Rendering engine
│   ├── object/             # Geometric objects
│   ├── scene/              # Scene management
│   └── texture/            # Material system
├── src/                    # Source implementations
│   ├── geometry/           # Vector, point, and matrix math
│   ├── image/              # Image processing
│   ├── light/              # Light source implementations
│   ├── logger/             # Debug and logging
│   ├── motor/              # Core rendering algorithms
│   ├── object/             # Object intersection and normal calculations
│   ├── scene/              # Scene graph and camera
│   └── texture/            # Material definitions
├── main.cc                 # Example scene setup
├── CMakeLists.txt          # Build configuration
└── README.md               # This file
```

## Building the Project

### Prerequisites
- CMake 3.21.2 or higher
- C++20 compatible compiler (GCC 10+, Clang 12+, MSVC 19.29+)

### Build Instructions

1. **Clone the repository**:
   ```bash
   git clone <repository-url>
   cd raytracer
   ```

2. **Create build directory**:
   ```bash
   mkdir build
   cd build
   ```

3. **Configure and build**:
   ```bash
   cmake ..
   make
   ```

4. **Run the raytracer**:
   ```bash
   ./raytracing
   ```

This will generate an `image.ppm` file in the current directory.

## Usage Example

```cpp
#include "scene/camera.hh"
#include "light/point_light.hh"
#include "object/sphere.hh"
#include "object/plane.hh"
#include "texture/uniform_texture.hh"
#include "motor/motor.hh"

int main() {
    // Create camera
    Camera camera(Point3(10, 0, 10), Point3(0, 0, 0), 
                  Vector3(Point3(0, 1, 0)), 46.5, 46.5, 2.8);
    
    // Create lights
    PointLight* light = new PointLight(Color(255, 255, 255), 
                                      Point3(0, 2, 3), 1);
    
    // Create objects
    Sphere* sphere = new Sphere(2.0, Point3(0, 0, 0), 
                               UniformTexture::Plastic(Color(255, 0, 0)));
    Plane* plane = new Plane(Point3(0, -1, 0), Vector3(1, 0, 0), 
                            Vector3(0, 0, 1), 
                            UniformTexture::Metal(Color(200, 200, 200)));
    
    // Setup scene
    std::list<Object*> objects = {sphere, plane};
    std::list<Light*> lights = {light};
    Scene scene(objects, lights, camera);
    
    // Render
    Motor motor(scene);
    Image image = motor.render();
    image.image_to_ppm("output.ppm");
    
    return 0;
}
```

## Key Classes

### Core Rendering
- **Motor**: Main rendering engine that handles ray generation and casting
- **Scene**: Container for objects, lights, and camera
- **Camera**: Defines viewpoint and projection parameters

### Geometry
- **Point3**: 3D point representation
- **Vector3**: 3D vector with mathematical operations
- **Matrix**: Matrix operations for transformations

### Objects
- **Object**: Base class for all renderable objects
- **Sphere**: Sphere primitive with radius and center
- **Plane**: Infinite plane defined by point and two vectors
- **Triangle**: Triangle mesh primitive
- **Cube**: Axis-aligned box primitive
- **Blob**: Metaball using marching cubes

### Materials
- **TextureMaterial**: Base material class
- **UniformTexture**: Solid color materials with different properties

## Algorithms

### Ray-Object Intersection
- **Sphere**: Quadratic equation solving for ray-sphere intersection
- **Plane**: Line-plane intersection using dot products
- **Triangle**: Möller-Trumbore algorithm for ray-triangle intersection
- **Cube**: Ray-AABB intersection testing

### Lighting Model
- **Phong Illumination**: Ambient + Diffuse + Specular lighting
- **Shadow Rays**: Occlusion testing for realistic shadows
- **Multiple Light Sources**: Accumulative lighting from multiple sources

### Marching Cubes
- **Blob Rendering**: Procedural surface generation using marching cubes
- **Potential Field**: Scalar field evaluation for metaball surfaces
- **Triangle Mesh Generation**: Automatic mesh creation from implicit surfaces

## Configuration

The raytracer can be configured through:
- **Camera parameters**: Position, target, up vector, field of view
- **Material properties**: Ambient, diffuse, specular coefficients
- **Light properties**: Color, intensity, position
- **Rendering quality**: Anti-aliasing samples, resolution

## Output Format

The raytracer outputs images in PPM (Portable Pixmap) format, which can be viewed with most image viewers or converted to other formats using tools like ImageMagick:

```bash
convert image.ppm image.png
```

## Performance Considerations

- **Spatial Data Structures**: Consider implementing BVH or octree for complex scenes
- **Parallel Rendering**: Multi-threading support for faster rendering
- **Memory Management**: Efficient memory usage for large scenes
- **Optimization**: Compiler optimizations enabled in release builds

## License

This project is part of an academic assignment. Please respect academic integrity policies when using this code.

## Acknowledgments

- Based on classical raytracing algorithms from computer graphics literature
- Marching cubes implementation follows the original Lorensen-Cline algorithm
- Phong lighting model implementation
