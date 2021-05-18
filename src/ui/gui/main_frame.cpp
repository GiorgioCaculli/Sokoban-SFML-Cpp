#include "main_frame.hpp"

#include <iostream>

using namespace sokoban::ui::gui;

void framebuffer_size_callback( GLFWwindow *window, int width, int height );

void process_input( GLFWwindow *window );

MainFrame::MainFrame( int width, int height )
{
    logger = new Logger( "Main frame" );
    logger->log( LoggerLevel::INFO, "Init Window" );

    set_width( width );
    set_height( height );

    glfwInit();
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
#ifdef __APPLE__
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
#endif
    window = glfwCreateWindow( get_width(), get_height(), "Sokoban", nullptr, nullptr );
}

MainFrame::MainFrame()
        : MainFrame( 800, 600 )
{

}

MainFrame::~MainFrame()
{
    delete logger;
}

void MainFrame::set_width( int width )
{
    this->_width = width;
}

int MainFrame::get_width() const
{
    return _width;
}

void MainFrame::set_height( int height )
{
    this->_height = height;
}

int MainFrame::get_height() const
{
    return _height;
}

int MainFrame::launch() const
{
    if ( window == nullptr )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent( window );
    glfwSetFramebufferSizeCallback( window, framebuffer_size_callback );

    while ( !glfwWindowShouldClose( window ))
    {
        process_input( window );
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );
        glfwSwapBuffers( window );
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void process_input( GLFWwindow *window )
{
    if ( glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS )
    {
        glfwSetWindowShouldClose( window, true );
    }
}

void framebuffer_size_callback( GLFWwindow *window, int width, int height )
{
    glViewport( 0, 0, width, height );
}
