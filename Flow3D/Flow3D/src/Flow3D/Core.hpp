#pragma once

// contains macros used in different parts of the engine

#define BIT(x) (1 << x)
#define FLOW_BIND_EVENT_FUNCTION(fn) std::bind(&fn, this, std::placeholders::_1)