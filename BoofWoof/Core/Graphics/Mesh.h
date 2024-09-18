#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h> // for access to OpenGL API declarations

#include "glslshader.h"
#include <string>
#include <vector>
using namespace std;

#define MAX_BONE_INFLUENCE 4

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    //// texCoords
    //glm::vec2 TexCoords;
    //// tangent
    //glm::vec3 Tangent;
    //// bitangent
    //glm::vec3 Bitangent;
    ////bone indexes which will influence this vertex
    //int m_BoneIDs[MAX_BONE_INFLUENCE];
    ////weights from each bone
    //float m_Weights[MAX_BONE_INFLUENCE];
};

//struct Texture {
//    unsigned int id;
//    string type;
//    string path;
//};

class Mesh {
public:
    // mesh Data
    vector<Vertex>       vertices{};
    vector<unsigned int> indices{};
    //vector<Texture>      textures;
    unsigned int VAO{};
    unsigned int drawMode{};

    // constructor
    Mesh() {}
    //Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices)
    {
        this->vertices = vertices;
        this->indices = indices;
        //this->textures = textures;

        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        setupMesh();
       
    }

    // render the mesh
    void Draw(GLSLShader& shader)
    {
        (void)shader;
        //// bind appropriate textures
        //unsigned int diffuseNr = 1;
        //unsigned int specularNr = 1;
        //unsigned int normalNr = 1;
        //unsigned int heightNr = 1;
        //for (unsigned int i = 0; i < textures.size(); i++)
        //{
        //    glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        //    // retrieve texture number (the N in diffuse_textureN)
        //    string number;
        //    string name = textures[i].type;
        //    if (name == "texture_diffuse")
        //        number = std::to_string(diffuseNr++);
        //    else if (name == "texture_specular")
        //        number = std::to_string(specularNr++); // transfer unsigned int to string
        //    else if (name == "texture_normal")
        //        number = std::to_string(normalNr++); // transfer unsigned int to string
        //    else if (name == "texture_height")
        //        number = std::to_string(heightNr++); // transfer unsigned int to string

        //    // now set the sampler to the correct texture unit
        //    glUniform1i(glGetUniformLocation(shader.GetHandle(), (name + number).c_str()), i);
        //    // and finally bind the texture
        //    glBindTexture(GL_TEXTURE_2D, textures[i].id);
        //}

        // draw mesh
        glPolygonMode(GL_FRONT_AND_BACK, drawMode);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }

    // render the mesh with lines
    void DrawLines(GLSLShader& shader)
    {
        (void)shader;
        //glPolygonMode(GL_FRONT_AND_BACK, drawMode);

		glBindVertexArray(VAO);

        glDrawArrays(GL_LINES, 0, static_cast<unsigned int>(indices.size()));
		//glDrawElements(GL_LINES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}
    
    // render the mesh with point
    void DrawPoints(GLSLShader& shader)
	{
        (void)shader;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
        // change the point size
        glPointSize(50.0f);
		glBindVertexArray(VAO);
		glDrawElements(GL_POINTS, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}
    void setupGenericMesh()
    {
        // create buffers/arrays
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);


        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    }

    void updateGenericMesh()
    {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_DYNAMIC_DRAW);
	}

//private:
    // render data 
    unsigned int VBO{}, EBO{};

    // initializes all the buffer objects/arrays
    void setupMesh()
    {
        
        
        // create buffers/arrays
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        //// vertex texture coords
        //glEnableVertexAttribArray(2);
        //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        //// vertex tangent
        //glEnableVertexAttribArray(3);
        //glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
        //// vertex bitangent
        //glEnableVertexAttribArray(4);
        //glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
        //// ids
        //glEnableVertexAttribArray(5);
        //glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

        //// weights
        //glEnableVertexAttribArray(6);
        //glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
        //glBindVertexArray(0);
    }

   

    
    

};