

#ifndef SHADER_H
#define SHADER_H

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <string>

class Shader
{
public:
    unsigned int ID;
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(std::string vertexPath, std::string fragmentPath);
    // activate the shader
    // ------------------------------------------------------------------------
    void use();

    // Functions to set uniforms
    // ------------------------------------------------------------------------
    void setBool(const std::string& name, bool value) const;
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value) const;
    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value) const;
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const glm::vec3& value) const;
    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, const glm::mat4& mat) const;

    std::string getVertexPath();
    std::string getFragmentPath();

private:
    std::string vertexPath, fragmentPath;
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, std::string type);
};
#endif

