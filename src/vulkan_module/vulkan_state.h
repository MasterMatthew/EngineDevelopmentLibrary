#ifndef VULKAN_STATE_H
#define VULKAN_STATE_H

/*
Avoid importing this file unless it is necessary for some c++ level library

This holds all state involved with the creation of a vulkan instance and vulkan devices as well as auxillary vulkan systems such as the surface and swapchain
*/

#include "vulkan/vulkan.h"


//Vulkan Instance
extern VkInstance vulkan_instance;

//Enumeration of vulkan physical devices
extern uint32_t vulkan_physical_device_count;
extern VkPhysicalDevice* vulkan_physical_devices;

//Vulkan Physical Device
extern VkPhysicalDevice vulkan_physical_device;
extern VkPhysicalDeviceProperties vulkan_physical_device_properties;
extern VkPhysicalDeviceFeatures vulkan_physical_device_features;
extern VkPhysicalDeviceMemoryProperties vulkan_physical_device_memory_properties;

//Vulkan Logical Device
extern VkDevice vulkan_logical_device;

//Vulkan Queues
extern uint32_t vulkan_graphics_family; //Use for presenting, graphics operations, sync compute operations, and GPU-GPU transfers
extern uint32_t vulkan_transfer_family; //Use for CPU-GPU transfers
extern uint32_t vulkan_compute_family;  //Use for async compute operations

extern uint32_t vulkan_graphics_count;
extern VkQueue* vulkan_graphics_queues;
extern uint32_t vulkan_compute_count;
extern VkQueue* vulkan_compute_queues;
extern uint32_t vulkan_transfer_count;
extern VkQueue* vulkan_transfer_queues;

//Vulkan surface
extern uint32_t surface_width;
extern uint32_t surface_height;

extern VkSurfaceKHR vulkan_surface;
extern VkSurfaceCapabilitiesKHR vulkan_surface_capabilities;
extern VkSurfaceFormatKHR vulkan_surface_format;
extern VkPresentModeKHR vulkan_present_mode;

//Vulkan presentation swapchain
extern VkExtent2D vulkan_swapchain_extent;

extern VkSwapchainKHR vulkan_swapchain;
extern uint32_t vulkan_swapchain_image_count;
extern VkImage* vulkan_swapchain_images;
extern VkImageView* vulkan_swapchain_imageviews;

#endif // !VULKAN_STATE_H