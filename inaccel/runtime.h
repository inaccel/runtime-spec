#ifndef INACCEL_RUNTIME_H
#define INACCEL_RUNTIME_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Return value of object constructors in case of an internal error. */
#define INACCEL_FAILED ((void *) -1)

/* CL resource struct (API Type). */
typedef struct _cl_resource *cl_resource;

/**
 * @details Creates a resource object.
 *
 * @param index The index associated with this resource.
 * @returns A valid non-zero object if the resource is created successfuly. The
 *          value INACCEL_FAILED (that is, (void *) -1) is returned to indicate
 *          a failure to allocate resources required by the implementation.
 */
cl_resource create_resource(unsigned int index);

/**
 * @details Get the vendor of a resource.
 *
 * @param resource Refers to a valid resource object.
 * @returns The resource vendor.
 */
char *get_resource_vendor(cl_resource resource);

/**
 * @details Get the name of a resource.
 *
 * @param resource Refers to a valid resource object.
 * @returns The resource name.
 */
char *get_resource_name(cl_resource resource);

/**
 * @details Get the version of a resource.
 *
 * @param resource Refers to a valid resource object.
 * @returns The resource version.
 */
char *get_resource_version(cl_resource resource);

/**
 * @details Get the serial number of a resource.
 *
 * @param resource Refers to a valid resource object.
 * @returns The resource serial number.
 */
char *get_resource_serial_no(cl_resource resource);

/**
 * @details Get the current power of a resource.
 *
 * @param resource Refers to a valid resource object.
 * @returns The resource current power in Watts.
 */
float get_resource_power(cl_resource resource);

/**
 * @details Get the current temperature of a resource.
 *
 * @param resource Refers to a valid resource object.
 * @returns The resource current temperature in degrees Celsius.
 */
float get_resource_temperature(cl_resource resource);

/**
 * @details Loads the specified binary executable bits into the resource object.
 *
 * @param resource Refers to a valid resource object.
 * @param size The size in bytes of the binary to be loaded.
 * @param binary Pointer to binary to be loaded. The binary specified contains
 *               the bits that describe the executable that will be run on the
 *               associated resource.
 * @returns 0 on success; 1 on failure.
 */
int program_resource_with_binary(cl_resource resource, size_t size, const void *binary);

/**
 * @details Deletes a resource object.
 *
 * @param resource Refers to a valid resource object.
 */
void release_resource(cl_resource resource);

/* CL memory struct (API Type). */
typedef struct _cl_memory *cl_memory;

/**
 * @details Creates a memory object.
 *
 * @param resource A valid resource used to create the memory object.
 * @param index The index associated with this memory.
 * @returns A valid non-zero object if the memory is created successfuly. The
 *          value INACCEL_FAILED (that is, (void *) -1) is returned to indicate
 *          a failure to allocate resources required by the implementation.
 */
cl_memory create_memory(cl_resource resource, unsigned int index);

/**
 * @details Get the type of a memory.
 *
 * @param memory Refers to a valid memory object.
 * @returns The memory type.
 */
char *get_memory_type(cl_memory memory);

/**
 * @details Get the size of a memory.
 *
 * @param memory Refers to a valid memory object.
 * @returns The size of the memory in bytes.
 */
size_t get_memory_size(cl_memory memory);

/**
 * @details Deletes a memory object.
 *
 * @param memory Refers to a valid memory object.
 */
void release_memory(cl_memory memory);

/* CL buffer struct (API Type). */
typedef struct _cl_buffer *cl_buffer;

/**
 * @details Creates a buffer object.
 *
 * @param memory A valid memory used to create the buffer object.
 * @param size The size in bytes of the buffer memory object to be allocated.
 * @param host A pointer to the buffer data that should already be allocated by
 *             the application. The size of the buffer that address points to
 *             must be greater than or equal to the size bytes.
 * @returns A valid non-zero object if the buffer is created successfuly. The
 *          value INACCEL_FAILED (that is, (void *) -1) is returned to indicate
 *          a failure to allocate resources required by the implementation.
 */
cl_buffer create_buffer(cl_memory memory, size_t size, void *host);

/**
 * @details Commands to write to a buffer object from host memory.
 *
 * @param buffer Refers to a valid buffer object.
 * @returns 0 on success; 1 on failure.
 */
int copy_to_buffer(cl_buffer buffer);

/**
 * @details Commands to read from a buffer object to host memory.
 *
 * @param buffer Refers to a valid buffer object.
 * @returns 0 on success; 1 on failure.
 */
int copy_from_buffer(cl_buffer buffer);

/**
 * @details Waits on the host thread until all previous copy commands are issued
 *          to the associated resource and have completed.
 *
 * @param buffer Refers to a valid buffer object.
 * @returns 0 on success; 1 on failure.
 */
int await_buffer_copy(cl_buffer buffer);

/**
 * @details Deletes a buffer object.
 *
 * @param buffer Refers to a valid buffer object.
 */
void release_buffer(cl_buffer buffer);

/* CL compute unit struct (API Type). */
typedef struct _cl_compute_unit *cl_compute_unit;

/**
 * @details Creates a compute unit object.
 *
 * @param resource A valid resource used to create the compute unit object.
 * @param name A function name in the binary executable.
 * @returns A valid non-zero object if the compute unit is created successfuly.
 *          The value INACCEL_FAILED (that is, (void *) -1) is returned to
 *          indicate a failure to allocate resources required by the
 *          implementation.
 */
cl_compute_unit create_compute_unit(cl_resource resource, const char *name);

/**
 * @details Used to set the argument value for a specific argument of a compute
 *          unit.
 *
 * @param buffer Refers to a valid compute unit object.
 * @param index The argument index.
 * @param size Specifies the size of the argument value. If the argument is a
 *             buffer object, the size is NULL.
 * @param value A pointer to data that should be used for argument specified by
 *              index. If the argument is a buffer the value entry will be the
 *              appropriate object. The buffer object must be created with the
 *              resource associated with the compute unit object.
 * @returns 0 on success; 1 on failure.
 */
int set_compute_unit_arg(cl_compute_unit compute_unit, unsigned int index, size_t size, const void *value);

/**
 * @details Command to execute a compute unit on a resource.
 *
 * @param buffer Refers to a valid compute unit object.
 * @returns 0 on success; 1 on failure.
 */
int run_compute_unit(cl_compute_unit compute_unit);

/**
 * @details Waits on the host thread until all previous run commands are issued
 *          to the associated resource and have completed.
 *
 * @param buffer Refers to a valid compute unit object.
 * @returns 0 on success; 1 on failure.
 */
int await_compute_unit_run(cl_compute_unit compute_unit);

/**
 * @details Deletes a compute unit object.
 *
 * @param compute_unit Refers to a valid compute unit object.
 */
void release_compute_unit(cl_compute_unit compute_unit);

#ifdef __cplusplus
}
#endif

#endif // INACCEL_RUNTIME_H
