SetFactory("OpenCASCADE");

// Define parameters
lc = 1;          // Characteristic mesh size
L = 0.7;            // Length of the trunk
R_base = 0.02;      // Increased radius of the trunk
R_ball = 0.7;

// Define the trunk geometry
// Point(1) = {0, 0, 0, lc};          // Bottom center point of the trunk
// Point(2) = {0, 0, L, lc};          // Top center point of the trunk
// Cylinder(1) = {0, 0, 0, 0, 0, L, R_base};  // Trunk

// Define the foliage as ellipsoids by scaling spheres
Sphere(2) = {0, 0, L+0.2 , R_ball}; // Increased radius for larger ellipsoids
Dilate {{0, 0, 0}, {0.2, 0.2, 0.5}} { Volume{2}; }

// Define physical groups
// Physical Volume("Trunk") = {1};     // Assigning a physical name to the trunk
Physical Volume("Foliage") = {2}; // Assigning a physical name to the foliage

// Define the mesh size
Mesh.CharacteristicLengthMax = lc;
Mesh.CharacteristicLengthMin = lc/10;
