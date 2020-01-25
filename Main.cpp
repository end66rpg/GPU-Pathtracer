#include <cstdio>
#include <cstdlib>
#include <time.h> 

#include "Window.h"

#include "ScopedTimer.h"

#include "Pathtracer.h"
#include "MegaKernel.h"

// Forces NVIDIA driver to be used 
extern "C" { _declspec(dllexport) unsigned NvOptimusEnablement = true; }

#define MEGAKERNEL 0
#define WAVEFRONT  1

#define PATH_TRACER WAVEFRONT

#define TOTAL_TIMING_COUNT 1000
float timings[TOTAL_TIMING_COUNT];
int   current_frame = 0;

int main(int argument_count, char ** arguments) {
	Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "Pathtracer");
	
	// Initialize timing stuff
	Uint64 now  = 0;
	Uint64 last = 0;
	float inv_perf_freq = 1.0f / (float)SDL_GetPerformanceFrequency();
	float delta_time = 0;

	float second = 0.0f;
	int frames = 0;
	int fps    = 0;
	
#if PATH_TRACER == MEGAKERNEL
	MegaKernel megakernel;
	megakernel.init(DATA_PATH("scene.obj"), window.frame_buffer_handle);
#elif PATH_TRACER == WAVEFRONT
	Pathtracer pathtracer;
	pathtracer.init(DATA_PATH("scene.obj"), window.frame_buffer_handle);
#endif

	srand(1337);

	last = SDL_GetPerformanceCounter();

	// Game loop
	while (!window.is_closed) {
#if PATH_TRACER == MEGAKERNEL
		megakernel.update(delta_time, SDL_GetKeyboardState(nullptr));
		megakernel.render();
#elif PATH_TRACER == WAVEFRONT
		pathtracer.update(delta_time, SDL_GetKeyboardState(nullptr));
		pathtracer.render();
#endif

		window.update();

		// Perform frame timing
		now = SDL_GetPerformanceCounter();
		delta_time = float(now - last) * inv_perf_freq;
		last = now;

		// Calculate average of last TOTAL_TIMING_COUNT frames
		timings[current_frame++ % TOTAL_TIMING_COUNT] = delta_time;

		float avg = 0.0f;
		int count = current_frame < TOTAL_TIMING_COUNT ? current_frame : TOTAL_TIMING_COUNT;
		for (int i = 0; i < count; i++) {
			avg += timings[i];
		}
		avg /= count;

		// Calculate fps
		frames++;

		second += delta_time;
		while (second >= 1.0f) {
			second -= 1.0f;

			fps = frames;
			frames = 0;
		}

		// Report timings
		printf("%d - Delta: %.2f ms, Average: %.2f ms, FPS: %d        \r", current_frame, delta_time * 1000.0f, avg * 1000.0f, fps);
	}

	return EXIT_SUCCESS;
}
