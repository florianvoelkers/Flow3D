#pragma once

#include <string>
#include <functional>
#include <vector>
#include <memory>
#include <algorithm>

#include "Flow3D/Transform.hpp"
#include "Flow3D/GameObject.hpp"

/*
Code for implementing template functions for components is taken from:
https://stackoverflow.com/questions/44105058/how-does-unitys-getcomponent-work
*/

#define TO_STRING( x ) #x

// CLASS_DECLARATION
// This macro must be included in the declaration of any subclass of component. It declares variables used in type checking.
#define CLASS_DECLARATION( classname )                                                      \
public:                                                                                     \
    static const std::size_t Type;                                                          \
    virtual bool IsClassType( const std::size_t classType ) const override;                 \

// CLASS_DEFINITION
// This macro must be included in the class definition to properly initialize variables used in type checking.
// Take special care to ensure that the proper parentclass is indicated or the run-time type information will be
// incorrect. Only works on single-inheritance RTTI.
#define CLASS_DEFINITION( parentclass, childclass )                                         \
const std::size_t childclass::Type = std::hash< std::string >()( TO_STRING( childclass ) ); \
bool childclass::IsClassType( const std::size_t classType ) const {                         \
        if ( classType == childclass::Type )                                                \
            return true;                                                                    \
        return parentclass::IsClassType( classType );                                       \
}                                                                                           \


namespace Flow {

	class Component
	{
	public:
		static const std::size_t Type;
		virtual bool IsClassType(const std::size_t classType) const 
		{ 
			return classType == Type; 
		}

		Component(GameObject* gameObject) : m_GameObject(gameObject) {}
		virtual ~Component() {} // TODO: Destructor with ~Component() = default?

		virtual void OnUpdate (double deltaTime) {}
		virtual void OnEvent (Event& event) {}
		virtual void Render (Mat4 view, Mat4 projection) {}

		inline Transform* GetTransform() { return m_GameObject->GetTransform(); }
		inline const Transform& GetTransform() const { return *m_GameObject->GetTransform(); }

	protected:
		GameObject* m_GameObject;
	};
}
