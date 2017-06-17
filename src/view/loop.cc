#include "view.ih"

#define CC_USE_ALL
extern "C"
{
#include <ccore/display.h>
#include <ccore/window.h>
#include <ccore/opengl.h>   

#include <ccore/event.h>
}

//#include <iostream>

//using namespace std;

void View::loop()
{    
    ccRect windowRect;
    d_loop = true;

    ccDisplayInitialize();

    windowRect.x = 0;
    windowRect.y = 0;
    windowRect.width = d_winWidth;
    windowRect.height = d_winHeight;

    ccWindowCreate(windowRect, "Openflight dev", CC_WINDOW_FLAG_NORESIZE);
    ccGLContextBind();
    ccWindowSetCentered();
    
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        cout << "Glew not OK...\n";
        exit(1); // or handle the error in a nicer way
    }
    if (!GLEW_VERSION_2_1)  // check that the machine supports the 2.1 API.
    {
        cout << "glew version  2.1\n";
        exit(1); // or handle the error in a nicer way
    }
    
    glEnable(GL_TEXTURE_2D);

    compile();
    linkShaders();
    
    initFramebuffer();
    
    glViewport(0,0,d_winWidth, d_winHeight);
    
    //glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    //glEnable(GL_DEPTH_TEST);
   // glDepthFunc(GL_LESS);
    
    glEnable(GL_CULL_FACE),
    glCullFace(GL_BACK);
   
    setTextures();
    d_world.load();
    for(size_t idx = 0; d_loop; ++idx) {
        
        while(ccWindowEventPoll()) {
            switch(ccWindowEventGet().type) {
                case CC_EVENT_WINDOW_QUIT:
                    d_loop = false;
                    break;
                case CC_EVENT_KEY_DOWN:
                    switch(ccWindowEventGet().keyCode) {
                        case CC_KEY_M:
                            ccWindowSetMaximized();
                            break;
                        case CC_KEY_W:
                            ccWindowSetWindowed(&windowRect);
                            ccWindowSetCentered();
                            break;
                        case CC_KEY_UP:
                            d_yRotation -= 1;
                            break;
                        case CC_KEY_DOWN:
                            d_yRotation += 1;
                            break;
                        case CC_KEY_LEFT:
                            d_xRotation -= 1;
                            break;
                        case CC_KEY_RIGHT:
                            d_xRotation += 1;
                            break;
                    }

                    break;
                default:
                    break;
            }
        }   
        

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        glUseProgram(d_activeShader->id());
        setProjection();
        //glBindFramebuffer(GL_DRAW_FRAMEBUFFER, d_frameBuffer);

        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        
        d_world.render(d_activeShader->id(), d_view);

        ccGLBuffersSwap();
    }
    
    ccFree();

    return;

}