#include "vulkan_state.h"

//Vulkan Instance
VkInstance vulkan_instance;

//Enumeration of vulkan physical devices
uint32_t vulkan_physical_device_count;
VkPhysicalDevice* vulkan_physical_devices;

//Vulkan Physical Device
VkPhysicalDevice vulkan_physical_device;
VkPhysicalDeviceProperties vulkan_physical_device_properties;
VkPhysicalDeviceFeatures vulkan_physical_device_features;
VkPhysicalDeviceMemoryProperties vulkan_physical_device_memory_properties;

//Vulkan Logical Device
VkDevice vulkan_logical_device;

//Vulkan Queues
uint32_t vulkan_graphics_family = 0; //Use for presenting, graphics operations, sync compute operations, and GPU-GPU transfers
uint32_t vulkan_transfer_family = 0; //Use for CPU-GPU transfers
uint32_t vulkan_compute_family = 0;  //Use for async compute operations

uint32_t vulkan_graphics_count = 0;
VkQueue *vulkan_graphics_queues = NULL;
uint32_t vulkan_compute_count = 0;
VkQueue *vulkan_compute_queues = NULL;
uint32_t vulkan_transfer_count = 0;
VkQueue *vulkan_transfer_queues = NULL;

//Vulkan surface
uint32_t surface_width;
uint32_t surface_height;

VkSurfaceKHR vulkan_surface;
VkSurfaceCapabilitiesKHR vulkan_surface_capabilities;
VkSurfaceFormatKHR vulkan_surface_format;
VkPresentModeKHR vulkan_present_mode;

//Vulkan presentation swapchain
VkExtent2D vulkan_swapchain_extent;

VkSwapchainKHR vulkan_swapchain;
uint32_t vulkan_swapchain_image_count;
VkImage* vulkan_swapchain_images;
VkImageView* vulkan_swapchain_imageviews;