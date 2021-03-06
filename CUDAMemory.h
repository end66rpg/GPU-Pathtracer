#pragma once
#include "CUDACall.h"

namespace CUDAMemory {
	// Type safe device pointer wrapper
	template<typename T>
	struct Ptr {
		CUdeviceptr ptr;

		Ptr()                : ptr(NULL) { }
		Ptr(CUdeviceptr ptr) : ptr(ptr)  { }
	};

	template<typename T>
	inline T * malloc_pinned(int count = 1) {
		assert(count > 0);

		T * ptr;
		CUDACALL(cuMemAllocHost(reinterpret_cast<void **>(&ptr), count * sizeof(T)));

		return ptr;
	}

	template<typename T>
	inline Ptr<T> malloc(int count = 1) {
		assert(count > 0);

		CUdeviceptr ptr;
		CUDACALL(cuMemAlloc(&ptr, count * sizeof(T)));

		return Ptr<T>(ptr);
	}

	template<typename T>
	inline void free(Ptr<T> ptr) {
		assert(ptr.ptr);
		CUDACALL(cuMemFree(ptr.ptr));
	}

	template<typename T>
	inline void memcpy(Ptr<T> ptr, const T * data, int count = 1) {
		assert(ptr.ptr);
		assert(data);
		assert(count > 0);

		CUDACALL(cuMemcpyHtoD(ptr.ptr, data, count * sizeof(T)));
	}

	CUarray          create_array       (int width, int height, int channels, CUarray_format format);
	CUmipmappedArray create_array_mipmap(int width, int height, int channels, CUarray_format format, int level_count);

	// Copies data from the Host Texture to the Device Array
	void copy_array(CUarray array, int width_in_bytes, int height, const void * data);
	void copy_array_3d(CUarray array, int width_in_bytes, int height, const void * data);
	
	// Graphics Resource management (for OpenGL interop)
	CUgraphicsResource resource_register(unsigned gl_texture, unsigned flags);
	void               resource_unregister(CUgraphicsResource resource);

	CUarray resource_get_array(CUgraphicsResource resource);
}
