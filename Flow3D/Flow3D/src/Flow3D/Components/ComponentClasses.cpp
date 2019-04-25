#include "Component.hpp"

#include "FreeCamera.hpp"
#include "RenderableCube.hpp"
#include "RenderablePlane.hpp"

using namespace Flow;

const std::size_t Component::Type = std::hash<std::string>()(TO_STRING(Component));

CLASS_DEFINITION(Component, FreeCamera)
CLASS_DEFINITION(Component, RenderableCube)
CLASS_DEFINITION(Component, RenderablePlane)