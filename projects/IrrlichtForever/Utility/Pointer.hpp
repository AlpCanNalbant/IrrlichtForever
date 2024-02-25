// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once

#include "Concepts.hpp"

namespace Irr
{
	template <ReferenceCountable T>
	class Pointer
	{
	public:
		Pointer() = default;
		Pointer(std::nullptr_t) noexcept;
		Pointer(T *ptr, const bool isCreated) noexcept;
		Pointer(const Pointer<T> &other) noexcept;
		Pointer(Pointer<T> &&other) noexcept;
		template <ReferenceCountable U>
		Pointer(const Pointer<U> &other, T *ptr) noexcept;
		template <ReferenceCountable U>
		Pointer(Pointer<U> &&other, T *ptr) noexcept;
		~Pointer() noexcept;
		void Reset() noexcept;
		[[nodiscard]] T *Get() const noexcept;
		[[nodiscard]] bool IsUnique() const noexcept;
		[[nodiscard]] irr::s32 GetReferenceCount() const noexcept;
		Pointer<T> &operator=(const Pointer<T> &other) noexcept;
		Pointer<T> &operator=(Pointer<T> &&other) noexcept;
		Pointer<T> &operator=(std::nullptr_t) noexcept;
		[[nodiscard]] T *operator->() const noexcept;
		[[nodiscard]] T &operator*() const noexcept;
		explicit operator bool() const noexcept;

	private:
		T *ptr_{nullptr};
	};

	[[nodiscard]] Pointer<irr::IrrlichtDevice> CreateDevice(const irr::E_DRIVER_TYPE deviceType = irr::EDT_OPENGL,
															const irr::dimension2d<irr::u32> &windowSize = irr::dimension2d<irr::u32>(640, 480), const irr::u32 bits = 16,
															const bool fullscreen = false, const bool stencilbuffer = false, const bool vsync = false, irr::IEventReceiver *receiver = nullptr) noexcept;
	[[nodiscard]] Pointer<irr::IrrlichtDevice> CreateDevice(const irr::SIrrlichtCreationParameters &parameters) noexcept;
	template <ReferenceCountable T>
	[[nodiscard]] Pointer<T> GrabCreatedPtr(T *ptr) noexcept;
	template <ReferenceCountable T>
	[[nodiscard]] Pointer<T> GrabPtr(T *ptr) noexcept;
	template <ReferenceCountable U1, ReferenceCountable U2>
	[[nodiscard]] bool operator==(const Pointer<U1> &lhs, const U2 *ptr) noexcept;
	template <ReferenceCountable U1, ReferenceCountable U2>
	[[nodiscard]] bool operator==(const Pointer<U1> &lhs, const Pointer<U2> &rhs) noexcept;
	template <ReferenceCountable U>
	[[nodiscard]] bool operator==(const Pointer<U> &lhs, std::nullptr_t) noexcept;
	template <ReferenceCountable U1, ReferenceCountable U2>
	[[nodiscard]] std::strong_ordering operator<=>(const Pointer<U1> &lhs, const U2 *ptr) noexcept;
	template <ReferenceCountable U1, ReferenceCountable U2>
	[[nodiscard]] std::strong_ordering operator<=>(const Pointer<U1> &lhs, const Pointer<U2> &rhs) noexcept;
	template <ReferenceCountable U>
	[[nodiscard]] std::strong_ordering operator<=>(const Pointer<U> &lhs, std::nullptr_t) noexcept;
	template <ReferenceCountable To, ReferenceCountable From>
	[[nodiscard]] Pointer<To> StaticPointerCast(const Pointer<From> &ptr) noexcept;
	template <ReferenceCountable To, ReferenceCountable From>
	[[nodiscard]] Pointer<To> StaticPointerCast(Pointer<From> &&ptr) noexcept;
	template <ReferenceCountable To, ReferenceCountable From>
	[[nodiscard]] Pointer<To> ConstPointerCast(const Pointer<From> &ptr) noexcept;
	template <ReferenceCountable To, ReferenceCountable From>
	[[nodiscard]] Pointer<To> ConstPointerCast(Pointer<From> &&ptr) noexcept;
	template <ReferenceCountable To, ReferenceCountable From>
	[[nodiscard]] Pointer<To> DynamicPointerCast(const Pointer<From> &ptr) noexcept;
	template <ReferenceCountable To, ReferenceCountable From>
	[[nodiscard]] Pointer<To> DynamicPointerCast(Pointer<From> &&ptr) noexcept;
	template <ReferenceCountable To, ReferenceCountable From>
	[[nodiscard]] Pointer<To> ReinterpretPointerCast(const Pointer<From> &ptr) noexcept;
	template <ReferenceCountable To, ReferenceCountable From>
	[[nodiscard]] Pointer<To> ReinterpretPointerCast(Pointer<From> &&ptr) noexcept;
}

#include "Pointer.inl"
