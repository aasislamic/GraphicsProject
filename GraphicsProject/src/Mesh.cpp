#include "Mesh.h"
#include "Math/vec.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures) : VAO(0), EBO(0), VBO(0)
{
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;

 
  SetupVAO();
}


Mesh::~Mesh()
{
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}


void Mesh::SetupVAO() {

  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(offsetof(Vertex, normal)));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoord));
  
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void Mesh::Draw(Shader& shader) {	
/*
  unsigned int diffuseNr = 1;
  unsigned int specularNr = 1;
  unsigned int normalNr = 1;
  unsigned int heightNr = 1;

  for (unsigned int i = 0; i < textures.size(); i++)
    {
      glActiveTexture(GL_TEXTURE0 + i);
      std::string number;
      std::string name = textures[i].type;
      if (name == "texture_diffuse") {
	number = std::to_string(diffuseNr++);
      }
      else if (name == "texture_specular")
	number = std::to_string(specularNr++);
      else if (name == "texture_normal")
	number = std::to_string(normalNr++);

      else if (name == "texture_height")
	number = std::to_string(heightNr++);

      shader.LoadInt((name + number).c_str(), i);

      glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
	*/
  shader.LoadVec("color", textures[0].color);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);
}
