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

    ccWindowCreate(windowRect, "A ccore window", CC_WINDOW_FLAG_NORESIZE);
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
    
    
    compile();
    linkShaders();
    loadObjects();

    glViewport(0,0,d_winWidth, d_winHeight);
    for(size_t idx = 0; d_loop; ++idx) {
        //cout << idx << '\n';
        
        
        
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
                    }

                    break;
                default:
                    break;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        glUseProgram(d_activeShader->id());
        
        d_view = conv_to<fmat>::from(arma::eye(1,4));  //eye is armadillo for Identity
        d_projection = conv_to<fmat>::from(arma::eye(1,4));
        
        fmat camera = {200,200,500};
        fmat up = {0,1,0};
        
        fmat eyeRot = conv_to<fmat>::from(arma::eye(4,4));
        
        render();
        
        


        ccGLBuffersSwap();
    }
    
    ccFree();

    return;

}