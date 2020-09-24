#pragma once
#include "fwd.hpp"

class SystemManager {
public:
    SystemManager(std::shared_ptr<ComponentManager>,
                  std::shared_ptr<InputManager>,
                  Gengine*);
    void registerSystem(std::shared_ptr<System>,
                        ComponentSignature);
    void invalidateSystemCache();
    void cacheAllSystems();
    void cacheSystemWithSignature(std::shared_ptr<System>, ComponentSignature);
    void tick();
private:
    void registerBeginTickSystem(std::shared_ptr<System>,
                                    ComponentSignature);
    void registerEndTickSystem(std::shared_ptr<System>,
                                  ComponentSignature);

    void registerSystemToList(std::shared_ptr<System>,
                              ComponentSignature&,
                              SystemList&);

    SystemList _beginTickSystems;
    SystemList _systems;
    SystemList _endTickSystems;

    std::shared_ptr<ComponentManager> _componentMan;
    std::shared_ptr<InputManager> _inputMan;
    Gengine* _parentGengine;

    std::unordered_map<std::shared_ptr<System>, std::set<EntityID>> _systemCache;
    std::unordered_map<std::shared_ptr<System>, bool> _isSystemCached;
    bool _areSystemsCached;

    friend class Gengine;
};
