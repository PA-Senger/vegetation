SetFactory("OpenCASCADE");

// Define parameters
lc = 7;      // Characteristic mesh size
L = 0.7;        // Length of the trunk
R_base = 0.02;  // Radius of the trunk
R_ball = 0.3;   // Radius of the ball (foliage)
cone_height = 0.1; // Additional height for rounding the top
apex_radius = 0.01; // Radius at the apex for rounding

// Define the trunk geometry
// Point(1) = {0, 0, 0, lc};       // Bottom center point of the trunk
// Point(2) = {0, 0, L, lc};       // Top center point of the trunk
// Cylinder(1) = {0, 0, 0, 0, 0, L, R_base};  // Trunk

// Define the cone geometry (foliage)
Cone(2) = {0, 0, 0.2, 0, 0, L + cone_height, R_ball, apex_radius}; // Cone with rounded top

// Define physical groups
// Physical Volume("Trunk") = {1};  // Assigning a physical name to the trunk
Physical Volume("Foliage") = {2};  // Assigning a physical name to the cone

// Define the mesh size
Mesh.CharacteristicLengthMax = lc;
Mesh.CharacteristicLengthMin = lc/10;