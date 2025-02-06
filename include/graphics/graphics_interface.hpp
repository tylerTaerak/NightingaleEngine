#pragma once

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace Nightingale::Graphics {

    class GraphicsInterface;

    // RAII for GraphicsProgram.use()
    class GraphicsProgramLease {
        public:
            GraphicsProgramLease(unsigned int program, const GraphicsInterface *iface);
            ~GraphicsProgramLease();
        private:
            unsigned int m_programId;
            const GraphicsInterface *m_interface;
    };

    class GraphicsInterface {
        public:
            GraphicsInterface();
            ~GraphicsInterface();

            unsigned int addNewShaderProgram(const std::string &vertexPath, const std::string &fragmentPath);

            unsigned int addNewShaderProgramFromText(const char *vertexText, const char *fragmentText);

            void addAttributeToShader(unsigned int shaderId, const std::string &attributeName);

            GraphicsProgramLease useProgram(unsigned int program);

            void setUniformForShader(unsigned int shaderId, const std::string &uniformName, int val);

            void setUniformForShader(unsigned int shaderId, const std::string &uniformName, float val);

            void setUniformForShader(unsigned int shaderId, const std::string &uniformName, glm::mat4 val);

            void setUniformForShader(unsigned int shaderId, const std::string &uniformName, glm::vec3 val);
        private:
            class GraphicsProgram {
                public:
                    GraphicsProgram();
                    ~GraphicsProgram();

                    void initAll(const std::string &vertexPath, const std::string &fragmentPath);

                    void use() const;
                    void unuse() const;

                    unsigned int getProgramId() const;
                    unsigned int getVertexShaderId() const;
                    unsigned int getFragmentShaderId() const;

                private:
                    void compileVertexShader(const std::string &filepath);
                    void compileFragmentShader(const std::string &filepath);
                    void compileVertexShaderFromText(const std::string &textData);
                    void compileFragmentShaderFromText(const std::string &textData);
                    void compileShader(const std::string &filepath, unsigned int &id);
                    void linkShaders();
                    std::string loadFileContents(const std::string &textData);

                    unsigned int m_programId;
                    unsigned int m_vertexShaderId;
                    unsigned int m_fragmentShaderId;
                    std::vector<std::size_t> m_attributeIndices;

                    static std::size_t s_currentAttributeIndex;

                    friend class GraphicsInterface;
            };

            std::vector<GraphicsProgram> m_programs;
            friend class GraphicsProgramLease;

    };
}
