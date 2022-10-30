#ifndef ENGINE_SCENE_NODE_H
#define ENGINE_SCENE_NODE_H
#include "Movable.h"
#include "SceneObject.h"

#include <list>
#include <string>
#include <string_view>
#include <vector>

namespace engine
{
using RenderableEntry = std::pair<int, SceneObject*>;
using RenderableList  = std::vector<RenderableEntry>;
class SceneNode : public Movable {
  public:
    enum class UpdateType : unsigned int {
        none       = 0,
        pos        = (1 << 1),
        childNodes = (1 << 2),
    };

    friend inline UpdateType operator|(UpdateType lh, UpdateType rh) { return static_cast<UpdateType>(static_cast<int>(lh) | static_cast<int>(rh)); }
    friend inline UpdateType operator&(UpdateType lh, UpdateType rh) { return static_cast<UpdateType>(static_cast<int>(lh) & static_cast<int>(rh)); }

    SceneNode() noexcept;
    SceneNode(std::string_view id) noexcept;
    virtual ~SceneNode() override = default;

    const std::string& id() const noexcept;

    void setPos(const math::Vector<double, 3>& pos) override;
    void translate(const math::Vector<double, 3>& v) override;
    void setScale(const math::Vector<double, 2>& scale) override;
    void scale(const math::Vector<double, 2>& scale) override;
    void setRot(double rot) override;
    void rotate(double rot) override;
    void setIsFlipped(bool isFlipped) override;
    void flip() override;
    void setIsVisible(bool isVisible) override;

    const math::Vector<double, 3>& absPos() const;
    const math::Vector<double, 3>& pos() const { return pos_; };

    void attach(SceneObject* obj);
    void detach(SceneObject* obj);
    void attach(SceneNode* node);
    void detach(SceneNode* node);
    void notifyAttach(SceneNode* parent);
    void notifyDetach();
    void notifyNeedsUpdate(UpdateType type = UpdateType::pos | UpdateType::childNodes);
    void update();
    void collectRenderables(RenderableList& list) const;

  private:
    std::string id_          = "Node";
    SceneNode* parent_       = nullptr;
    UpdateType neededUpdate_ = UpdateType::none;

    math::Vector<double, 3> pos_   = { { 0.0, 0.0, 0.0 } };
    math::Vector<double, 2> scale_ = { { 1.0, 1.0 } };
    double rot_                    = 0.0;
    bool isFlipped_                = false;
    bool isVisible_                = true;

    math::Vector<double, 3> absPos_   = { { 0.0, 0.0, 0.0 } };
    math::Vector<double, 2> absScale_ = { { 1.0, 1.0 } };
    double absRot_                    = 0.0;
    bool absIsFlipped_                = false;
    bool absIsVisible_                = true;

    std::list<SceneNode*> childNodes_;
    std::list<SceneObject*> sceneObjects_;
};
} // namespace engine
#endif
