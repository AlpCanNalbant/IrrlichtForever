// Copyright (c) Alp Can Nalbant. Licensed under the MIT License.

#pragma once

namespace Irr
{
    class EventReceiver
    {
    public:
        EventReceiver() = default;
        EventReceiver(const EventReceiver &) = default;
        EventReceiver(EventReceiver &&) = default;
        EventReceiver &operator=(const EventReceiver &) = default;
        EventReceiver &operator=(EventReceiver &&) = default;

    protected:
        ~EventReceiver() = default;
    };
}
