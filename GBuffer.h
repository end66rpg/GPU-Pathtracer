#pragma once

struct GBuffer {
	unsigned gbuffer = 0;

	unsigned buffer_normal_and_depth;
	unsigned buffer_uv;
	unsigned buffer_uv_gradient;
	unsigned buffer_mesh_id_and_triangle_id;
	unsigned buffer_motion;
	unsigned buffer_z_gradient;
	unsigned buffer_depth;

	void resize(int width, int height);

	void bind();
	void unbind();
};
