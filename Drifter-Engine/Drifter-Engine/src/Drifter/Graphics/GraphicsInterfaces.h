#pragma once

namespace Drifter {

	class IBindable {
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
	};

	class IHasRendererID{
	public:
		virtual uint32_t GetRendererID() const = 0;
	};
}