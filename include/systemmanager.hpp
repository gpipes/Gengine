#pragma once
#include "fwd.hpp"

class SystemManager {
public:
    SystemManager(std::shared_ptr<ComponentManager>,
                  std::shared_ptr<InputManager>,
                  std::shared_ptr<ScreenManager>);

    void registerSystem(SystemPtr,
                        ComponentSignature);
    void invalidateSystemCache();
    void cacheAllSystems();
    void cacheSystemWithSignature(SystemPtr, ComponentSignature);
    void tick();
private:
    void registerBeginTickSystem(SystemPtr,
                                    ComponentSignature);
    void registerEndTickSystem(SystemPtr,
                                  ComponentSignature);

    void registerSystemToList(SystemPtr,
                              ComponentSignature&,
                              SystemList&);

    SystemList _beginTickSystems;
    SystemList _systems;
    SystemList _endTickSystems;

    std::shared_ptr<ComponentManager> _componentMan;
    std::shared_ptr<InputManager> _inputMan;
    std::shared_ptr<ScreenManager> _screenMan;

    std::unordered_map<SystemPtr, std::vector<EntityID>> _systemCache;
    std::unordered_map<SystemPtr, bool> _isSystemCached;
    bool _areSystemsCached;

    friend class Gengine;
};
