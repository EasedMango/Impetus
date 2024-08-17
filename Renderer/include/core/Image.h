﻿#pragma once
#include "utils/VKCommon.hpp"
#include "utils/QuickMacros.h"
#include "core/Vma.h"


#include "utils/Forwards.h"


namespace Imp::Render {

	class Image
	{
	private:
		Vma* allocator;
		vk::UniqueImage image;
		vk::UniqueImageView view;
		VmaAllocation allocation;
		vk::Extent3D extent;
		vk::Format format;
		inline static size_t idCounter = 0;
		size_t id = idCounter++;
	public:
		DISABLE_COPY_AND_MOVE(Image);

		// Constructor
		Image(const Device& device, Vma& allocator, vk::Extent3D extent, vk::Format format, vk::ImageUsageFlags usage, vk::ImageAspectFlags aspectFlags,bool mipmap=false);
		// Destructor
		~Image();

		// Getters
		const vk::Image& getImage() const;
		const vk::Image* getpImage() const;
		const vk::ImageView& getView() const;
		const vk::Extent3D& getExtent() const;
		const vk::Extent2D& getExtent2D() const;
		const vk::Format& getFormat() const;

		// Transition image layout
		void transitionImageLayout(const vk::CommandBuffer& commandBuffer, const vk::ImageLayout& oldLayout, const vk::ImageLayout& newLayout);
	};
	using UniqueImage = std::unique_ptr<Image>;
	using SharedImage = std::shared_ptr<Image>;
	UniqueImage CreateDrawImage(const Device& device, Vma& allocator, vk::Extent2D extent, vk::Format format);
	UniqueImage CreateDepthImage(const Device& device, Vma& allocator, vk::Extent2D extent);
	UniqueImage CreateImage(const Device& device, Vma& allocator,vk::Extent3D size, vk::Format format, vk::ImageUsageFlags usage, bool mipmapped =true );
	UniqueImage CreateImage(const Device& device, Vma& allocator, const ImmediateCommands& transferCommands, const vk::Queue& transferQueue, void*
	                        data, vk::Extent3D size, vk::Format format, vk::ImageUsageFlags usage, const vk::Queue* graphicsQueue , bool mipmapped = true);
	SharedImage CreateSharedImage(const Device& device, Vma& allocator, vk::Extent3D size, vk::Format format, vk::ImageUsageFlags usage, bool mipmapped = true);
	SharedImage CreateSharedImage(const Device& device, Vma& allocator, const ImmediateCommands& transferCommands, const vk::Queue& transferQueue, void*
							data, vk::Extent3D size, vk::Format format, vk::ImageUsageFlags usage, const vk::Queue* graphicsQueue , bool mipmapped = true);

	void CopyImageToImage(const CommandBuffer& cmd, Image& src, Image& dst);
	void CopyImageToSwapChain(const vk::CommandBuffer& cmd, Image& src, const SwapChain& swapChain, uint32_t imageIndex);
	void TransitionImageLayout(const vk::Image& image, const vk::CommandBuffer& commandBuffer, const vk::ImageLayout& oldLayout, const vk::ImageLayout
	                           & newLayout);
}
