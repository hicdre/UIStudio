#pragma once
#include "base/base_defines.h"

namespace base
{
	//
	// A point has an x and y coordinate.
	//
	template <class T>
	class PointT {
	public:
		PointT() : x_(0), y_(0) {}
		PointT(T x, T y) : x_(x), y_(y) {}
		PointT(const PointT& point) : x_(point.x_), y_(point.y_) {}
		PointT& operator=(const PointT& point) {
			x_ = point.x_;
			y_ = point.y_;
			return *this;
		}

		~PointT() {}

		T x() const { return x_; }
		T y() const { return y_; }

		void SetPoint(T x, T y) {
			x_ = x;
			y_ = y;
		}

		void set_x(T x) { x_ = x; }
		void set_y(T y) { y_ = y; }

		void Offset(T delta_x, T delta_y) {
			x_ += delta_x;
			y_ += delta_y;
		}

		bool operator==(const PointT& rhs) const {
			return x_ == rhs.x_ && y_ == rhs.y_;
		}

		bool operator!=(const PointT& rhs) const {
			return !(*this == rhs);
		}	

	private:
		T x_;
		T y_;
	};

	typedef PointT<int> Point;
	typedef PointT<float> PointF;
}