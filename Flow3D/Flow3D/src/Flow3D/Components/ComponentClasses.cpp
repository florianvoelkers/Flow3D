#include "Component.hpp"

// Add all the different component classes here
#include "Lighting.hpp"
#include "FreeCamera.hpp"
#include "Renderable.hpp"
#include "Rotatable.hpp"

using namespace Flow;

const std::size_t Component::Type = std::hash<std::string>()(TO_STRING(Component));

// All class definitions for components
// CLASS_DEFINITION(parent class, sub class)
CLASS_DEFINITION(Component, Rotatable)
CLASS_DEFINITION(Component, FreeCamera)
CLASS_DEFINITION(Component, Renderable)
CLASS_DEFINITION(Component, BaseLight)
CLASS_DEFINITION(BaseLight, DirectionalLight)
CLASS_DEFINITION(BaseLight, PointLight)
CLASS_DEFINITION(BaseLight, SpotLight)