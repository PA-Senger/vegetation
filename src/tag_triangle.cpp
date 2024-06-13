#include "../include/randomnumber.hpp"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/IO/Color.h>
#include <CGAL/IO/STL.h>
#include <CGAL/IO/polygon_soup_io.h>
#include <CGAL/Polygon_mesh_processing/IO/polygon_mesh_io.h>
#include <CGAL/Polygon_mesh_processing/corefinement.h>
#include <CGAL/Polygon_mesh_processing/fair.h>
#include <CGAL/Polygon_mesh_processing/orient_polygon_soup_extension.h>
#include <CGAL/Polygon_mesh_processing/orientation.h>
#include <CGAL/Polygon_mesh_processing/polygon_soup_to_polygon_mesh.h>
#include <CGAL/Polygon_mesh_processing/repair.h>
#include <CGAL/Polygon_mesh_processing/repair_polygon_soup.h>
#include <CGAL/Polygon_mesh_processing/triangulate_faces.h>
#include <CGAL/Real_timer.h>
#include <CGAL/Surface_mesh.h>
#include <filesystem>
#include <iostream>
#include <string>

using K = CGAL::Exact_predicates_inexact_constructions_kernel;
using Point_3 = K::Point_3;
using Mesh = CGAL::Surface_mesh<Point_3>;

void tag_triangles(Mesh &mesh) {
    typedef boost::graph_traits<Mesh>::face_descriptor face_descriptor;
    std::map<face_descriptor, std::string> face_tags;
    std::srand(std::time(0)); // Seed for random number generation

    for (face_descriptor fd : faces(mesh)) {
        int coin_flip = std::rand() % 4; //
        switch (coin_flip) {
        case 0:
            face_tags[fd] = "A";
            break;
        case 1:
            face_tags[fd] = "B";
            break;
        case 2:
            face_tags[fd] = "C";
            break;
        case 3:
            face_tags[fd] = "D";
            break;
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_mesh_file.off>"
                  << std::endl;
        return EXIT_FAILURE;
    }

    Mesh mesh;
    const std::string filename = CGAL::data_file_path(argv[1]);

    if (!CGAL::IO::read_STL(filename, mesh)) {
        std::cerr << "ERROR: cannot read the input file!" << std::endl;
        return EXIT_FAILURE;
    }

    tag_triangles(mesh);

    // Write the tagged mesh to a file
    if (!CGAL::IO::write_STL("tagged_" + filename, mesh)) {
        std::cerr << "ERROR: cannot write the output file!" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
