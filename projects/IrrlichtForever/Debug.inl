// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

namespace Irr
{
	template <std::derived_from<irr::IReferenceCounted> T>
    const irr::c8 *GetDebugName(const T *ptr) noexcept
    {
#ifdef IRR_FOREVER_DEBUG
    	IRR_FOREVER_ASSERT_IF(!rawPtr && "Irr::GetDebugName(const T *ptr) 'ptr' is null.");
    	return rawPtr->getDebugName();
#else
        return nullptr;
#endif
    }

    template <std::derived_from<irr::IReferenceCounted> T>
    const irr::c8 *GetDebugName(const Pointer<T> &ptr) noexcept
    {
#ifdef IRR_FOREVER_DEBUG
        return ptr->getDebugName();
#else
        return nullptr;
#endif
    }
}
