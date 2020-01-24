#include "vulkan_state.h"

//Vulkan Instance
VkInstance vulkan_instance;

//Number of physical devices connected to the system
uint32_t vulkan_physical_device_count;
//Enumeration of vulkan physical devices
VkPhysicalDevice* vulkan_physical_devices;

//Vulkan Physical Device that is currently being used
VkPhysicalDevice vulkan_physical_device;
//Properties of the current physical device
VkPhysicalDeviceProperties vulkan_physical_device_properties;
//Features of the current physical device
VkPhysicalDeviceFeatures vulkan_physical_device_features;
//Memory properties of the current physical device
VkPhysicalDeviceMemoryProperties vulkan_physical_device_memory_properties;

//Vulkan Logical Device
VkDevice vulkan_logical_device;

//Vulkan Queues

/**
Queue family for graphics operations
Use for presenting, graphics operations, sync compute operations, and GPU-GPU transfers
*/
uint32_t vulkan_graphics_family = 0;
/**
Queue family for compute operations
Use for async compute operations
*/
uint32_t vulkan_compute_family = 0;
/**
Queue family for transfer operations
Use for CPU-GPU transfers
*/
uint32_t vulkan_transfer_family = 0;


//Number of queues in the queue family for graphics operations
uint32_t vulkan_graphics_count = 0;
//Array of graphics queues of size vulkan_graphics_count
VkQueue *vulkan_graphics_queues = NULL;

//Number of queues in the queue family for compute operations
uint32_t vulkan_compute_count = 0;
//Array of compute queues of size vulkan_compute_count
VkQueue *vulkan_compute_queues = NULL;

//Number of queues in the queue family for transfer operations
uint32_t vulkan_transfer_count = 0;
//Array of transfer queues of size vulkan_transfer_count
VkQueue *vulkan_transfer_queues = NULL;


//Vulkan surface

//Width of the current vulkan surface
uint32_t surface_width;
//Height of the current vulkan surface
uint32_t surface_height;

//Current vulkan surface
VkSurfaceKHR vulkan_surface;
//Capabilities of the current vulkan surface
VkSurfaceCapabilitiesKHR vulkan_surface_capabilities;
//Format of the current vulkan surface
VkSurfaceFormatKHR vulkan_surface_format;
//Present mode of the current vulkan surface
VkPresentModeKHR vulkan_present_mode;


//Vulkan presentation swapchain

//Extent of current vulkan swapchain
VkExtent2D vulkan_swapchain_extent;

//Current vulkan swapchain
VkSwapchainKHR vulkan_swapchain;
//Number of images used by the current vulkan swapchain
uint32_t vulkan_swapchain_image_count;
//Images used by the current vulkan swapchain
VkImage* vulkan_swapchain_images;
//Imageviews used by the current vulkan swapchain
VkImageView* vulkan_swapchain_imageviews;