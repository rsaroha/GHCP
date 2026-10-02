#include <iostream>
#include <stdexcept>
#include <string>

#include "input.h"
#include "renderer.h"
#include "renderer_gl.h"

int main(int argc, char* argv[]) {
    bool useGL = true;
    for (int i = 1; i < argc; i++) {
        std::string a = argv[i];
        if (a == "--opengl" || a == "--gl") useGL = true;
    }

    try {
        InputHandler input;
        while (true) {
            input.state.switchRenderer = false;
            input.state.useOpenGL      = useGL;

            if (useGL) {
                RendererGL renderer;
                renderer.run(input);
            } else {
                Renderer renderer;
                renderer.run(input);
            }

            if (!input.state.switchRenderer) break;
            useGL = !useGL;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
