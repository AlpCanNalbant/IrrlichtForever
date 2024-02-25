// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

namespace Irr
{
	template <ReferenceCountable T>
	Pointer<T>::Pointer(std::nullptr_t) noexcept
	{ }

	template <ReferenceCountable T>
	Pointer<T>::Pointer(T *ptr, const bool isCreated) noexcept
		: ptr_{ptr}
	{
		if (!isCreated)
		{
			IRR_FOREVER_ASSERT_IF(!ptr && "Irr::Pointer::Pointer(T *ptr, const bool isCreated) 'ptr' is null.");
			ptr->grab();
		}
	}

	template <ReferenceCountable T>
	Pointer<T>::Pointer(const Pointer<T> &other) noexcept
		: ptr_{other.ptr_}
	{
		if (other)
		{
			other->grab();
		}
	}

	template <ReferenceCountable T>
	Pointer<T>::Pointer(Pointer<T> &&other) noexcept
		: ptr_{other.ptr_}
	{
		other.ptr_ = nullptr;
	}

	template <ReferenceCountable T>
	template <ReferenceCountable U>
	Pointer<T>::Pointer(const Pointer<U> &other, T *ptr) noexcept
		: ptr_{ptr}
	{
		IRR_FOREVER_ASSERT_IF(other.ptr_ != static_cast<void *>(ptr) && "Irr::Pointer::Pointer(const Pointer<U> &other, T *ptr) Only call in the typical use cases where 'ptr' is a member of the object managed by 'other'.");
		// nullptr is implicitly convertible to any pointer type so nullness checking is non-redunant here.
		if (other)
		{
			other->grab();
		}
	}

	template <ReferenceCountable T>
	template <ReferenceCountable U>
	Pointer<T>::Pointer(Pointer<U> &&other, T *ptr) noexcept
		: ptr_{ptr}
	{
		IRR_FOREVER_ASSERT_IF(other.ptr_ != static_cast<void *>(ptr) && "Irr::Pointer::Pointer(Pointer<U> &&other, T *ptr) Only call in the typical use cases where 'ptr' is a member of the object managed by 'other'.")
		other.ptr_ = nullptr;
	}

	template <ReferenceCountable T>
	Pointer<T>::~Pointer() noexcept
	{
		Reset();
	}

	template <ReferenceCountable T>
	void Pointer<T>::Reset() noexcept
	{
		if (ptr_ && ptr_->getReferenceCount() > 0)
		{
			ptr_->drop();
		}
		ptr_ = nullptr;
	}

	template <ReferenceCountable T>
	T *Pointer<T>::Get() const noexcept
	{
		return ptr_;
	}

	template <ReferenceCountable T>
	bool Pointer<T>::IsUnique() const noexcept
	{
		return GetReferenceCount() == 1;
	}

	template <ReferenceCountable T>
	irr::s32 Pointer<T>::GetReferenceCount() const noexcept
	{
		if (ptr_)
		{
			return ptr_->getReferenceCount();
		}
		return 0;
	}

	template <ReferenceCountable T>
	Pointer<T> &Pointer<T>::operator=(const Pointer<T> &other) noexcept
	{
		if (this != &other)
		{
			Reset();
			if (other)
			{
				other->grab();
			}
			ptr_ = other.ptr_;
		}
		return *this;
	}

	template <ReferenceCountable T>
	Pointer<T> &Pointer<T>::operator=(Pointer<T> &&other) noexcept
	{
		if (this != &other)
		{
			Reset();
			ptr_ = other.ptr_;
			other.ptr_ = nullptr;
		}
		return *this;
	}

	template <ReferenceCountable T>
	Pointer<T> &Pointer<T>::operator=(std::nullptr_t) noexcept
	{
		Reset();
		return *this;
	}

	template <ReferenceCountable T>
	T *Pointer<T>::operator->() const noexcept
	{
		IRR_FOREVER_ASSERT_IF(!ptr_ && "Irr::Pointer::operator->() 'ptr_' is null.");
		return ptr_;
	}

	template <ReferenceCountable T>
	T &Pointer<T>::operator*() const noexcept
	{
		IRR_FOREVER_ASSERT_IF(!ptr_ && "Irr::Pointer::operator*() 'ptr_' is null.");
		return *ptr_;
	}

	template <ReferenceCountable T>
	Pointer<T>::operator bool() const noexcept
	{
		return ptr_ != nullptr;
	}

	template <ReferenceCountable T>
	Pointer<T> GrabCreatedPtr(T *ptr) noexcept
	{
		return {ptr, true};
	}

	template <ReferenceCountable T>
	Pointer<T> GrabPtr(T *ptr) noexcept
	{
		return {ptr, false};
	}

	template <ReferenceCountable U1, ReferenceCountable U2>
	bool operator==(const Pointer<U1> &lhs, const U2 *ptr) noexcept
	{
		return lhs.Get() == ptr;
	}

	template <ReferenceCountable U1, ReferenceCountable U2>
	bool operator==(const Pointer<U1> &lhs, const Pointer<U2> &rhs) noexcept
	{
		return lhs.Get() == rhs.Get();
	}

	template <ReferenceCountable U>
	bool operator==(const Pointer<U> &lhs, std::nullptr_t) noexcept
	{
		return !lhs.Get();
	}

	template <ReferenceCountable U1, ReferenceCountable U2>
	std::strong_ordering operator<=>(const Pointer<U1> &lhs, const U2 *ptr) noexcept
	{
		return std::compare_three_way()(lhs.Get(), ptr);
	}

	template <ReferenceCountable U1, ReferenceCountable U2>
	std::strong_ordering operator<=>(const Pointer<U1> &lhs, const Pointer<U2> &rhs) noexcept
	{
		return std::compare_three_way()(lhs.Get(), rhs.Get());
	}

	template <ReferenceCountable U>
	std::strong_ordering operator<=>(const Pointer<U> &lhs, std::nullptr_t) noexcept
	{
		return std::compare_three_way()(lhs.Get(), static_cast<U *>(nullptr));
	}

	template <ReferenceCountable To, ReferenceCountable From>
	Pointer<To> StaticPointerCast(const Pointer<From> &ptr) noexcept
	{
		return {ptr, static_cast<To *>(ptr.Get())};
	}

	template <ReferenceCountable To, ReferenceCountable From>
	Pointer<To> StaticPointerCast(Pointer<From> &&ptr) noexcept
	{
		return {std::move(ptr), static_cast<To *>(ptr.Get())};
	}

	template <ReferenceCountable To, ReferenceCountable From>
	Pointer<To> ConstPointerCast(const Pointer<From> &ptr) noexcept
	{
		return {ptr, const_cast<To *>(ptr.Get())};
	}

	template <ReferenceCountable To, ReferenceCountable From>
	Pointer<To> ConstPointerCast(Pointer<From> &&ptr) noexcept
	{
		return {std::move(ptr), const_cast<To *>(ptr.Get())};
	}

	template <ReferenceCountable To, ReferenceCountable From>
	Pointer<To> DynamicPointerCast(const Pointer<From> &ptr) noexcept
	{
		if (auto p = dynamic_cast<To *>(ptr.Get()))
		{
			return {ptr, p};
		}
		return {};
	}

	template <ReferenceCountable To, ReferenceCountable From>
	Pointer<To> DynamicPointerCast(Pointer<From> &&ptr) noexcept
	{
		if (auto p = dynamic_cast<To *>(ptr.Get()))
		{
			return {std::move(ptr), p};
		}
		return {};
	}

	template <ReferenceCountable To, ReferenceCountable From>
	Pointer<To> ReinterpretPointerCast(const Pointer<From> &ptr) noexcept
	{
		return {ptr, reinterpret_cast<To *>(ptr.Get())};
	}

	template <ReferenceCountable To, ReferenceCountable From>
	Pointer<To> ReinterpretPointerCast(Pointer<From> &&ptr) noexcept
	{
		return {std::move(ptr), reinterpret_cast<To *>(ptr.Get())};
	}
}
