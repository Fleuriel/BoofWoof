#pragma once
#include "Header.h"


class Model {

public:
    std::vector<Mesh>    meshes;
    std::vector<Texture> textures_loaded;
    std::string directory;

    void loadModel(std::string const& path, unsigned int draw_mode)
    {
#ifdef _DEBUG
        //std::cout << path << '\n';
#endif
        // read file via ASSIMP
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
        // check for errors

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
        {
            std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return;
        }
        // retrieve the directory path of the filepath
        directory = path.substr(0, path.find_last_of('/'));

        // process ASSIMP's root node recursively
        processNode(scene->mRootNode, scene, draw_mode);

    }

    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode* node, const aiScene* scene, unsigned int draw_mode)
    {


        // process each mesh located at the current node
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            // the node object only contains indices to index the actual objects in the scene. 
            // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene, draw_mode));
        }
        // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene, draw_mode);
        }

    }

    Mesh processMesh(aiMesh* mesh, const aiScene* scene, unsigned int draw_mode)
    {
        (void)scene;
        // data to fill
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;


        // walk through each of the mesh's vertices
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
            // positions
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
            // normals
            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;
            }
            // texture coordinates
            if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
            {
                 glm::vec2 vec;
                 // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
                 // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
                 vec.x = mesh->mTextureCoords[0][i].x;
                 vec.y = mesh->mTextureCoords[0][i].y;

                // std::cout << "Texture Coordinates: \t " << vec.x << '\t' << vec.y << '\n';

                 vertex.TexCoords = vec;
                 // tangent
                 vector.x = mesh->mTangents[i].x;
                 vector.y = mesh->mTangents[i].y;
                 vector.z = mesh->mTangents[i].z;
                 vertex.Tangent = vector;
                 // bitangent
                 vector.x = mesh->mBitangents[i].x;
                 vector.y = mesh->mBitangents[i].y;
                 vector.z = mesh->mBitangents[i].z;
                 vertex.Bitangent = vector;
            }
            else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }
        // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // retrieve all indices of the face and store them in the indices vector
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }




        if (mesh->mMaterialIndex >= 0)
        {
            //// process materials
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
            // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
            // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
            // Same applies to other texture as the following list summarizes:
            // diffuse: texture_diffuseN
            // specular: texture_specularN
            // normal: texture_normalN

            // 1. diffuse maps
            std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            // // 2. specular maps
            std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
            // 3. normal maps
            std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
            textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
            // 4. height maps
            std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
            textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
        }
        // return a mesh object created from the extracted mesh data
        //return Mesh(vertices, indices, textures);
        Mesh out(vertices, indices, textures);//, glm::vec3(1.0f,1.0f,1.0f));
        out.drawMode = draw_mode;
        return out;
    }


    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
    {
        std::vector<Texture> textures;

#ifdef _DEBUG
      //  std::cout << "Texture Count: " << mat->GetTextureCount(type) << " for " << typeName << '\n';
#endif
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
            bool skip = false;
            for (unsigned int j = 0; j < textures_loaded.size(); j++)
            {
                if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                    break;
                }
            }

            if (!skip) {
                Texture texture;

                // Get the texture ID from the resource manager
                std::string texturePath = this->directory + '/' + str.C_Str();

                std::cout << texturePath << '\n';

                std::string newString = str.C_Str();

                newString = newString.substr(0, newString.find_last_of("."));
                                

                texture.type = typeName;
                texture.path = newString;
#ifdef _DEBUG
       //         std::cout << "Texture Loaded from Resource Manager:\n";
       //         std::cout << "ID: " << texture.id << "\nType: " << texture.type << "\nPath: " << texture.path << '\n';
#endif
                textures.push_back(texture);
                textures_loaded.push_back(texture);  // Store in textures_loaded to prevent re-loading
            }
            return textures;
        }
        return textures;

    };



};
