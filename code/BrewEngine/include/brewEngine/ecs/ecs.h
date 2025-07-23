#pragma once

namespace gl3::brewEngine::ecs {
    /// The Entities IDs are of the type guid_t, which in this case is set to be a simple int.
    using guid_t = int;
    constexpr guid_t invalidID = -1;
}