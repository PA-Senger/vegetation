SetFactory("OpenCASCADE");

// Define parameters
lc = 2;      // Characteristic mesh size
L = 0.7;        // Length of the trunk
R_base = 0.02;  // Radius of the trunk
R_ball = 0.3;   // Radius of the ball (foliage)

// Define the trunk geometry
// Point(1) = {0, 0, 0, lc};       // Bottom center point of the trunk
// Point(2) = {0, 0, L, lc};       // Top center point of the trunk
// Cylinder(1) = {0, 0, 0, 0, 0, L, R_base};  // Trunk

// Define the ball geometry (using the same point for the trunk top to avoid duplication)
Sphere(2) = {0, 0, 0.5, R_ball};  // Ball at the top of the trunk

// Define physical groups
Physical Volume("Trunk") = {1};  // Assigning a physical name to the trunk
Physical Volume("Foliage") = {2};  // Assigning a physical name to the ball


// Define the mesh size
Mesh.CharacteristicLengthMax = lc;
Mesh.CharacteristicLengthMin = lc/10;
