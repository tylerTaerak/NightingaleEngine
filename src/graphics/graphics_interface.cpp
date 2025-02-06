#include <cstdio>
#include <glm/ext/matrix_clip_space.hpp>
#define GL_GLEXT_PROTOTYPES

#include "nightingale.hpp"
#include "utils/logger.hpp"
#include <graphics/graphics_interface.hpp>
#include <fstream>
#include <SDL_opengl.h>

namespace Nightingale::Graphics {
    std::size_t GraphicsInterface::GraphicsProgram::s_currentAttributeIndex = 0;

    GraphicsProgramLease::GraphicsProgramLease(unsigned int program, const GraphicsInterface *iface) : m_programId(program), m_interface(iface) {
        for (const GraphicsInterface::GraphicsProgram &graphicsProgram : m_interface->m_programs) {
            if (graphicsProgram.getProgramId() == program) {
                m_programId = graphicsProgram.getProgramId();
                graphicsProgram.use();
            }
        }

        if (!m_programId) {
            LOG(NG_ERROR, "Unable to find program: " + std::to_string(m_programId));
        }
    }

    GraphicsProgramLease::~GraphicsProgramLease() {
        for (const GraphicsInterface::GraphicsProgram &graphicsProgram : m_interface->m_programs) {
            if (graphicsProgram.getProgramId() == m_programId) {
                graphicsProgram.unuse();
            }
        }
    }

    GraphicsInterface::GraphicsProgram::GraphicsProgram() 
        : m_programId(0), m_vertexShaderId(0), m_fragmentShaderId(0) {
    }

    GraphicsInterface::GraphicsProgram::~GraphicsProgram() {
    }

    void GraphicsInterface::GraphicsProgram::initAll(const std::string &vertexPath, const std::string &fragmentPath) {
        compileVertexShader(vertexPath);
        compileFragmentShader(fragmentPath);
        linkShaders();
    }

    void GraphicsInterface::GraphicsProgram::compileVertexShader(const std::string &filepath) {
        m_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        if (!m_vertexShaderId) {
            LOG(NG_ERROR, "Unable to create vertex shader");
        }

        compileShader(loadFileContents(filepath), m_vertexShaderId);
    }

    void GraphicsInterface::GraphicsProgram::compileFragmentShader(const std::string &filepath) {
        m_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        if (!m_fragmentShaderId) {
            LOG(NG_ERROR, "Unable to create fragment shader");
        }

        compileShader(loadFileContents(filepath), m_fragmentShaderId);
    }

    void GraphicsInterface::GraphicsProgram::compileVertexShaderFromText(const std::string &textData) {
        m_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        if (!m_vertexShaderId) {
            LOG(NG_ERROR, "Unable to create vertex shader");
        }

        compileShader(textData, m_vertexShaderId);
    }

    void GraphicsInterface::GraphicsProgram::compileFragmentShaderFromText(const std::string &textData) {
        m_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        if (!m_fragmentShaderId) {
            LOG(NG_ERROR, "Unable to create fragment shader");
        }

        compileShader(textData, m_fragmentShaderId);
    }

    std::string GraphicsInterface::GraphicsProgram::loadFileContents(const std::string &filepath) {
        std::ifstream file(filepath);
        if (file.fail()) {
            LOG(NG_FATAL, "Unable to open file");
        }

        std::string contents = "";
        std::string line;

        while (std::getline(file, line)) {
            contents += line + "\n";
        }

        file.close();

        return contents;
    }

    void GraphicsInterface::GraphicsProgram::compileShader(const std::string &textData, unsigned int &id) {
        const char *contentsPtr = textData.c_str();
        glShaderSource(id, 1, &contentsPtr, nullptr);

        glCompileShader(id);

        auto e = glGetError();

        GLint success = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);

        if (success == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            
            std::vector<char> errorLog(maxLength);
            glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

            glDeleteShader(id);

            LOG(NG_ERROR, "Unable to compile shader");
        }
    }

    void GraphicsInterface::GraphicsProgram::linkShaders() {
        m_programId = glCreateProgram();

        glAttachShader(m_programId, m_vertexShaderId);
        glAttachShader(m_programId, m_fragmentShaderId);

        glLinkProgram(m_programId);

        GLint isLinked = 0;
        glGetProgramiv(m_programId, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE) {
            GLint maxLength = 0;
            glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(m_programId, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(m_programId);
            glDeleteShader(m_vertexShaderId);
            glDeleteShader(m_fragmentShaderId);

            LOG(NG_ERROR, "Unable to link shader");
        }

        glDetachShader(m_programId, m_vertexShaderId);
        glDetachShader(m_programId, m_fragmentShaderId);

        glDeleteShader(m_vertexShaderId);
        glDeleteShader(m_fragmentShaderId);
    }

    void GLAPIENTRY
    MessageCallback( GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar *message,
            const void *userParam) {
        fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
                ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ), type, severity, message);
    }

    GraphicsInterface::GraphicsInterface() {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(MessageCallback, 0);

        glViewport(0, 0, Nightingale::Window->getScreenWidth(), Nightingale::Window->getScreenHeight());
    }

    GraphicsInterface::~GraphicsInterface() {
    }

    void GraphicsInterface::GraphicsProgram::use() const {
        glUseProgram(m_programId);

        for (std::size_t i : m_attributeIndices) {
            glEnableVertexAttribArray(i);
        }
    }

    void GraphicsInterface::GraphicsProgram::unuse() const {
        glUseProgram(0);

        for (std::size_t i : m_attributeIndices) {
            glDisableVertexAttribArray(i);
        }
    }

    unsigned int GraphicsInterface::GraphicsProgram::getProgramId() const {
        return m_programId;
    }

    unsigned int GraphicsInterface::GraphicsProgram::getVertexShaderId() const {
        return m_vertexShaderId;
    }

    unsigned int GraphicsInterface::GraphicsProgram::getFragmentShaderId() const {
        return m_fragmentShaderId;
    }

    unsigned int GraphicsInterface::addNewShaderProgram(const std::string &vertexPath, const std::string &fragmentPath) {
        GraphicsProgram program;
        program.initAll(vertexPath, fragmentPath);

        m_programs.push_back(program);

        return program.getProgramId();
    }

    unsigned int GraphicsInterface::addNewShaderProgramFromText(const char *vertexText, const char *fragmentText) {
        GraphicsProgram program;
        program.compileVertexShaderFromText(vertexText);
        program.compileFragmentShaderFromText(fragmentText);
        program.linkShaders();

        m_programs.push_back(program);

        return program.getProgramId();
    }

    void GraphicsInterface::addAttributeToShader(unsigned int shaderId, const std::string &attributeName) {
        for (auto &program : m_programs) {
            if (shaderId == program.getProgramId()) {
                glBindAttribLocation(shaderId, GraphicsProgram::s_currentAttributeIndex, attributeName.c_str());

                program.m_attributeIndices.push_back(GraphicsProgram::s_currentAttributeIndex++);
            }
        }
    }

    GraphicsProgramLease GraphicsInterface::useProgram(unsigned int program) {
        return GraphicsProgramLease(program, this);
    }

    void GraphicsInterface::setUniformForShader(unsigned int shaderId, const std::string &uniformName, int val) {
        GLuint loc = glGetUniformLocation(shaderId, uniformName.c_str());
        if (loc == GL_INVALID_INDEX) {
            LOG(NG_FATAL, "Could not locate uniform " + uniformName + " for shader: " + std::to_string(shaderId));
        }

        glUniform1i(loc, val);
    }

    void GraphicsInterface::setUniformForShader(unsigned int shaderId, const std::string &uniformName, float val) {
        GLuint loc = glGetUniformLocation(shaderId, uniformName.c_str());
        if (loc == GL_INVALID_INDEX) {
            LOG(NG_FATAL, "Could not locate uniform " + uniformName + " for shader: " + std::to_string(shaderId));
        }

        glUniform1f(loc, val);
    }

    void GraphicsInterface::setUniformForShader(unsigned int shaderId, const std::string &uniformName, glm::vec3 val) {
        GLuint loc = glGetUniformLocation(shaderId, uniformName.c_str());
        if (loc == GL_INVALID_INDEX) {
            LOG(NG_FATAL, "Could not locate uniform " + uniformName + " for shader: " + std::to_string(shaderId));
        }

        glUniform3fv(loc, 1, &(val[0]));
    }

    void GraphicsInterface::setUniformForShader(unsigned int shaderId, const std::string &uniformName, glm::mat4 val) {
        GLuint loc = glGetUniformLocation(shaderId, uniformName.c_str());
        if (loc == GL_INVALID_INDEX) {
            LOG(NG_FATAL, "Could not locate uniform " + uniformName + " for shader: " + std::to_string(shaderId));
        }

        glUniformMatrix4fv(loc, 1, GL_FALSE, &(val[0][0]));
    }
}
