#pragma once
#include "base/base_defines.h"

namespace base
{
	//
	// A size has width and height values.
	//
	template <class T>
	class SizeT {
	public:
		SizeT() : width_(0), height_(0) {}
		SizeT(T width, T height) {
			set_width(width);
			set_height(height);
		}

		~SizeT() {}

		T width() const { return width_; }
		T height() const { return height_; }

		T GetArea() const { return width_ * height_; }

		void SetSize(T width, T height) {
			set_width(width);
			set_height(height);
		}

		void Enlarge(T width, T height) {
			set_width(width_ + width);
			set_height(height_ + height);
		}

		void Reduce(T width, T height) {
			if (width_ - width > 0)
				set_width(width_ - width);
			else
				set_width(0);

			if (height_ - height > 0)
				set_height(height_ - height);
			else
				set_height(0);
		}

		void set_width(T width) {
			if (width < 0) {				
				width = 0;
			}
			width_ = width;
		}
		void set_height(T height) {
			if (height < 0) {				
				height = 0;
			}
			height_ = height;
		}

		bool operator==(const SizeT& s) const {
			return width_ == s.width_ && height_ == s.height_;
		}

		bool operator!=(const SizeT& s) const {
			return !(*this == s);
		}

		bool IsEmpty() const {
			// Size doesn't allow negative dimensions, so testing for 0 is enough.
			return (width_ == 0) || (height_ == 0);
		}
				
	private:
		T width_;
		T height_;
	};

	typedef SizeT<int> Size;
	typedef SizeT<float> SizeF;
}