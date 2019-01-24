#include <SDL2/SDL.h>
#include <glad/glad.h>
#include "libfbxc.h"

GLuint compile_shader(GLenum shader_type, const char *filename)
{
    SDL_RWops *rw = SDL_RWFromFile(filename, "rb");
    if (!rw)
    {
        SDL_Log("unable to open file");
        exit(1);
    }

    size_t file_len = SDL_RWsize(rw);
    char *source = SDL_malloc(file_len + 1);
    if (!source)
    {
        SDL_Log("unable to allocate memory");
        exit(1);
    }

    if (SDL_RWread(rw, source, 1, file_len) != file_len)
    {
        SDL_Log("unable to read file");
        exit(1);
    }

    source[file_len] = 0;

    SDL_RWclose(rw);

    GLuint shader = glCreateShader(shader_type);
    // assign the shader code
    glShaderSource(shader, 1, (const GLchar **)&source, (GLint *)&file_len);
    // compile the shader
    glCompileShader(shader);

    SDL_free(source);

    GLint compile_status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
    if (compile_status == GL_FALSE)
    {
        GLint log_size;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
        char *error_log = SDL_malloc(log_size + 1);
        if (!error_log)
        {
            SDL_Log("unable to allocate memory for log");
            exit(1);
        }
        glGetShaderInfoLog(shader, log_size, &log_size, error_log);
        error_log[log_size] = 0;
        SDL_Log("shader compile error: %s", error_log);
        SDL_free(error_log);
        exit(1);
    }

    return shader;
}

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 1024, SDL_WINDOW_OPENGL);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // create opengl context with the major/minor specified with SetAttribute
    SDL_GLContext context = SDL_GL_CreateContext(window);

    // load GL symbols
    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    // SDL_Log("GL_VENDOR: %s", glGetString(GL_VENDOR));
    // SDL_Log("GL_RENDERER: %s", glGetString(GL_RENDERER));
    // SDL_Log("GL_VERSION: %s", glGetString(GL_VERSION));
    // SDL_Log("GL_SHADING_LANGUAGE_VERSION: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

    // set the current clear color
    glClearColor(1, 0, 0, 1);

    // allocate 1 VAO (in GPU)
    GLuint vao;
    glGenVertexArrays(1, &vao);
    // bind the VAO (in GPU). now it is the active one
    glBindVertexArray(vao);

    GLuint vbo[2];
    glGenBuffers(2, vbo);

    fbxc_scene_t mannequin = *fbxc_parse_file("Mannequin.FBX");
    // SDL_Log("%f %f %f", mannequin.vertices[0], mannequin.vertices[1], mannequin.vertices[2]);
    // SDL_Log("%f %f %f", mannequin.vertices[3], mannequin.vertices[4], mannequin.vertices[5]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, mannequin.vertices_len * sizeof(float), mannequin.vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // float colors[] = {
    //     1, 1, 1,
    //     1, 0, 1,
    //     0, 1, 0};
    // glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // create a new program/pipeline (in GPU)
    GLuint program = glCreateProgram();

    GLuint vertex_shader = compile_shader(GL_VERTEX_SHADER, "vertex.glsl");
    GLuint fragment_shader = compile_shader(GL_FRAGMENT_SHADER, "frag.glsl");

    // attach the sahders to the program
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    // linke the program (now is ready)
    glLinkProgram(program);

    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    // set the currently active program/pipeline
    glUseProgram(program);

    GLint x_uniform = glGetUniformLocation(program, "x");
    GLint y_uniform = glGetUniformLocation(program, "y");

    float triangle_x = 0;
    float triangle_y = 0;

    for (;;)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                return 0;

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RIGHT)
                    triangle_x += 0.1;
                if (event.key.keysym.sym == SDLK_LEFT)
                    triangle_x -= 0.1;
                if (event.key.keysym.sym == SDLK_UP)
                    triangle_y += 0.1;
                if (event.key.keysym.sym == SDLK_DOWN)
                    triangle_y -= 0.1;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glUniform1f(x_uniform, triangle_x);
        glUniform1f(y_uniform, triangle_y);

        glDrawArrays(GL_TRIANGLES, 0, mannequin.vertices_len / 3);

        SDL_GL_SwapWindow(window);
    }

    return 0;
}