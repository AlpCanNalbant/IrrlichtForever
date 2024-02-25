// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

namespace Irr
{
    inline void App::Clear() const noexcept
    {
        Driver->beginScene(ClearBufferBits[0], ClearBufferBits[1], ClearColor);
    }

    inline void App::Swap() const noexcept
    {
        Driver->endScene();
    }
}
