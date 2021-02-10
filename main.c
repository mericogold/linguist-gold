void destroy() {
    renderer_destroy(&state.renderer);
    world_destroy(&state.world);
    ui_destroy(&state.ui);
}

void update() {
    renderer_update(&state.renderer);
    world_update(&state.world);
    ui_update(&state.ui);

    // wireframe toggle (T)
    if (state.window->keyboard.keys[GLFW_KEY_T].pressed) {
        state.renderer.flags.wireframe = !state.renderer.flags.wireframe;
    }
}

void render() {
    renderer_prepare(&state.renderer, PASS_3D);
    world_render(&state.world);

    renderer_prepare(&state.renderer, PASS_2D);
    renderer_push_camera(&state.renderer);
    {
        renderer_set_camera(&state.renderer, CAMERA_ORTHO);
        ui_render(&state.ui);
    }
    renderer_pop_camera(&state.renderer);
}

int main(int argc, char *argv[]) {
    window_create(init, destroy, tick, update, render);
    window_loop();
}