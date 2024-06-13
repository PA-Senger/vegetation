SetFactory("OpenCASCADE");  // Switch to OpenCASCADE geometry kernel

// Define parameters
lc = 1; // Characteristic mesh size
R = 0.02;  // Radius of the cylinder
L = 0.7;   // Length of the cylinder

// Define the geometry
Cylinder(1) = {0, 0, 0, 0, 0, L, R};  // Create a cylinder trunk

// Define physical groups
Physical Volume("Trunk") = {1};  // Assigning a physical name to the trunk

// Define the mesh size
Mesh.CharacteristicLengthMax = lc;
Mesh.CharacteristicLengthMin = lc/10;