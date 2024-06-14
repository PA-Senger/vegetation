#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/IO/STL.h>
#include <CGAL/Surface_mesh.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_3 Point_3;
typedef CGAL::Surface_mesh<Point_3> Mesh;
typedef boost::graph_traits<Mesh>::face_descriptor face_descriptor;
typedef boost::graph_traits<Mesh>::vertex_descriptor vertex_descriptor;

void tag_triangles(Mesh &mesh,
                   std::map<face_descriptor, std::string> &face_tags) {
    std::srand(static_cast<unsigned int>(
        std::time(0))); // Seed for random number generation

    for (face_descriptor fd : faces(mesh)) {
        int coin_flip = std::rand() % 4;
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
        std::cerr << "Usage: " << argv[0] << " <input_mesh_file.stl>"
                  << std::endl;
        return EXIT_FAILURE;
    }

    Mesh mesh;
    std::map<face_descriptor, std::string> face_tags;
    std::string filename = argv[1];

    if (!CGAL::IO::read_STL(filename, mesh)) {
        std::cerr << "ERROR: cannot read the input file!" << std::endl;
        return EXIT_FAILURE;
    }

    tag_triangles(mesh, face_tags);

    // Write the tagged mesh to a file
    for (const auto &tag : {"A", "B", "C", "D"}) {
        Mesh tagged_mesh;
        for (face_descriptor fd : faces(mesh)) {
            if (face_tags[fd] == tag) {
                std::vector<vertex_descriptor> vertices;
                for (auto vd : vertices_around_face(halfedge(fd, mesh), mesh)) {
                    vertices.push_back(vd);
                }
                if (vertices.size() == 3) {
                    tagged_mesh.add_face(vertices[0], vertices[1], vertices[2]);
                } else {
                    std::cerr
                        << "WARNING: Face with unexpected number of vertices: "
                        << vertices.size() << std::endl;
                }
            }
        }

        std::cout << "test0" << std::endl;

        std::string output_filename = std::string(tag) + "_" + filename;
        std::cout << "test1" << std::endl;

        if (!CGAL::IO::write_STL(output_filename, tagged_mesh)) {
            std::cerr << "ERROR: cannot write the output file!" << std::endl;
            return EXIT_FAILURE;
        }
        std::cout << "test2" << std::endl;
    }

    return EXIT_SUCCESS;
}
