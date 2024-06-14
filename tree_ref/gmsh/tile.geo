SetFactory("OpenCASCADE");

lc = 50; // Characteristic mesh size

// Define the corner points of the square
Point(1) = {0, 0, 0, lc};      // Bottom-left corner
Point(2) = {256, 0, 0, lc};    // Bottom-right corner
Point(3) = {256, 256, 0, lc};  // Top-right corner
Point(4) = {0, 256, 0, lc};    // Top-left corner

// Define the edges of the square
Line(1) = {1, 2};  // Bottom edge
Line(2) = {2, 3};  // Right edge
Line(3) = {3, 4};  // Top edge
Line(4) = {4, 1};  // Left edge

// Define a curve loop for the edges
Curve Loop(1) = {1, 2, 3, 4};

// Define the surface enclosed by the curve loop
Plane Surface(1) = {1};


Mesh.CharacteristicLengthMax = lc;
Mesh.CharacteristicLengthMin = lc/10;