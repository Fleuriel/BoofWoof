
#include "Header.h"

#include "Model.h"
#include <fstream>




bool fileExistsInDirectory(const std::string& directoryPath, const std::string& fileName);
std::vector<std::string> processDescriptorFile(const std::string& descriptorFilePath);
void saveMeshToBin(std::vector<Mesh> meshes, const std::string& binFilePath);

namespace fs = std::filesystem;

int main(int argc, char** argv) {

    std::cout << "MeshCompiler executed\n";
    
    for (int i = 0; i < argc; ++i)
    {
        std::cout << argv[i] << '\n';
    }

    // [1] Descriptor File [TXT]
    // [2] Filepath of Descriptor
    // [3] [1][2] combined



    if (argc < 2) {
        std::cerr << "Usage: MeshCompiler <path_to_directory_with_descriptors>" << std::endl;
        return -1;
    }

    std::string directoryPath = argv[2];
    if (!fs::is_directory(directoryPath)) {
        std::cerr << "Provided path is not a directory: " << directoryPath << std::endl;
        return -1;
    }

    std::vector<std::string> descriptorFileInformation;



    descriptorFileInformation = processDescriptorFile(argv[3]);


    for (int i = 0; i < descriptorFileInformation.size(); ++i)
    {
        std::cout << i << '\t' << descriptorFileInformation[i] << '\n';
    }



    std::string objFilePath, binFilePath;

    objFilePath = descriptorFileInformation[1] + "\\" + descriptorFileInformation[0];
    binFilePath = descriptorFileInformation[2];

    // Iterate over all descriptor files in the directory
    for (const auto& entry : fs::directory_iterator(directoryPath)) {
        std::cout << "it entered first loop\n";

        if (fileExistsInDirectory(argv[2], argv[1])) {
            std::cout << "it entered second loop\n";
            // Read paths from descriptor file
           

            // Load and convert the .obj file
            Model model;
            model.loadModel(objFilePath, GL_TRIANGLES);

            std::cout << "it parsed finished\n";

            std::cout << model.meshes.size() << "\tsize\n";

            // Save the mesh data into a single .bin file
            if (!model.meshes.empty()) {
                saveMeshToBin(model.meshes, binFilePath);
                std::cout << "Converted " << objFilePath << " to " << binFilePath << std::endl;
            }
            else {
                std::cerr << "No mesh data found in " << objFilePath << std::endl;
            }
        }
    }
    return 0;
}



void saveMeshToBin(std::vector<Mesh> meshes, const std::string& binFilePath) {
    std::ofstream binFile(binFilePath, std::ios::binary);
    if (!binFile.is_open()) {
        std::cerr << "Failed to create binary file at saveAllMeshesToBin: " << binFilePath << std::endl;
        return;
    }

    // Step 1: Write the number of meshes
    size_t meshCount = meshes.size();
    binFile.write(reinterpret_cast<const char*>(&meshCount), sizeof(size_t));

    // Step 2: For each mesh, write vertex and index data
    for (const auto& mesh : meshes) {
        // Write vertex data
        size_t vertexCount = mesh.vertices.size();
        binFile.write(reinterpret_cast<const char*>(&vertexCount), sizeof(size_t));
        binFile.write(reinterpret_cast<const char*>(mesh.vertices.data()), vertexCount * sizeof(Vertex));

        // Write index data
        size_t indexCount = mesh.indices.size();
        binFile.write(reinterpret_cast<const char*>(&indexCount), sizeof(size_t));
        binFile.write(reinterpret_cast<const char*>(mesh.indices.data()), indexCount * sizeof(unsigned int));
    }

    binFile.close();
}



std::vector<std::string> processDescriptorFile(const std::string& descriptorFilePath) {
    std::ifstream file(descriptorFilePath);

    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Unable to open descriptor file: " << descriptorFilePath << std::endl;
        return {};
    }

    std::string line;
    std::string fileName;
    std::string objFilePath;
    std::string binFilePath;

    // Read the file line by line
    while (std::getline(file, line)) {
        // Check for "File Name" and extract the value
        if (line.find("File Name") != std::string::npos) {
            fileName = line.substr(line.find(":") + 2); // Extract name after ": "
            fileName += ".obj"; // Append .obj extension
        }
        // Check for "Source File Path" and extract the value
        else if (line.find("Source File Path") != std::string::npos) {
            objFilePath = line.substr(line.find(":") + 2); // Extract path after ": "
            objFilePath = objFilePath.substr(0, objFilePath.find_last_of("\\/")); // Get directory path
        }
        // Check for "Output File Path" and extract the value
        else if (line.find("Output File Path") != std::string::npos) {
            binFilePath = line.substr(line.find(":") + 2); // Extract path after ": "
        }
    }

    file.close(); // Close the file
    return { fileName, objFilePath, binFilePath }; // Return the extracted information
}


bool fileExistsInDirectory(const std::string& directoryPath, const std::string& fileName) {
    fs::path dirPath(directoryPath);
    fs::path filePath(fileName);

    // Iterate over the directory to check for the exact file
    for (const auto& entry : fs::directory_iterator(dirPath)) {
        if (entry.path().filename() == filePath.filename()) {
            return true; // The file exists in the directory
        }
    }

    return false; // The file does not exist in the directory
}