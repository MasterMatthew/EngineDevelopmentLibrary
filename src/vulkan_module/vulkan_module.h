#ifndef VULKAN_MODULE_H
#define VULKAN_MODULE_H

#include <stdlib.h>

#include "vulkan/vulkan.h"

#include "common_struct.h"

#include "cglm/cglm.h"

#include "vulkan_struct.h"
#include "vulkan_create_info.h"
#include "vulkan_init.h"
#include "vulkan_command_buffer.h"
#include "vulkan_surface.h"
#include "vulkan_swapchain.h"
#include "vulkan_pipeline.h"
#include "vulkan_descriptor.h"
#include "vulkan_buffer.h"
#include "vulkan_image.h"

//#define VULKAN_MODULE_EXPOSE_STATE
//Define to expose the state of the current vulkan instance
#ifdef VULKAN_MODULE_EXPOSE_STATE
#import "vulkan_state.h"
#endif // VULKAN_MODULE_EXPOSE_STATE

#endif // !VULKAN_MODULE_H