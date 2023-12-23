# R-Type - Game Engine

The `GameEngine` folder has all the parts necessary to create a game. They are separated into 3 libraries ([r-type-ecs.so](#ECS), [r-type-graphics.so](#Graphics), [r-type-physics.so](#Physics)), so it's not necessary to load every parts if not needed.

## ECS
This part means Entity-Component-System. As its name suggest, you can load entities, that are defined by components, and apply systems to them.

The class [ECSManager](../GameEngine/ECS/include/rtype/ECSManager.hpp) has a `ComponentManager`, a `SystemManager` and an `EntityManager`. It's the hub of this part, and handles the elements. It has templated methods such as this one:
```cpp

    template <class TComponent>
    SparseArray<TComponent> &register_component(SparseArray<TComponent> &array)
    {
        return m_component_manager.register_component<TComponent>(array);
    }
```
This method create a new component and regirster it in the component manager.

## Graphics
The Graphics part is an overlay of the SFML library. The components can be linked to a sprite, texture, and rendered if needed.

## Physics
Physics are the systems applied to components, such as gravity, collisions, ...

## How to link it to the project ?
Once built, the shared libraries is located in the `libs` folder.
1. You can load it in your CMakeList with the command `target_link_libraries(<project> PRIVATE r-type-ecs r-type-physics r-type-graphics)`
2. The best way to load it is dynamically, with [dlfcn](https://www.man7.org/linux/man-pages/man0/dlfcn.h.0p.html) functions. There is a overlay of those functions in the folder `RType-Utils`. Below an example for `r-type-ecs`:
```cpp
#include <rtype/dlloader/DlLoader.hpp>

int main(void)
{
    dl::DlLoader<rtype::ECSManager> ecs{};

    ecs.init_class<std::unique_ptr<rtype::ECSManager>()>("path to library");

    // to acceed to the class
    ecs.get_class().register_component({some component});
    return 0;
}
```

