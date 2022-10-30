#include <engine/SceneNode.h>

using engine::SceneNode;
using Vector3d = engine::math::Vector<double, 3>;
using Vector2d = engine::math::Vector<double, 2>;

SceneNode::SceneNode() noexcept = default;

SceneNode::SceneNode(std::string_view id) noexcept : id_(id) {}

const std::string& SceneNode::id() const noexcept
{
    return id_;
}

void SceneNode::setPos(const Vector3d& pos)
{
    pos_ = pos;
    notifyNeedsUpdate();
}

void SceneNode::translate(const Vector3d& v)
{
    pos_ += v;
    notifyNeedsUpdate();
}

void SceneNode::setScale(const Vector2d& scale)
{
    scale_ = scale;
    notifyNeedsUpdate();
}

void SceneNode::scale(const Vector2d& scale)
{
    scale_[0] *= scale[0];
    scale_[1] *= scale[1];
    notifyNeedsUpdate();
}

void SceneNode::setRot(double rot)
{
    rot_ = rot;
    notifyNeedsUpdate();
}

void SceneNode::rotate(double rot)
{
    rot_ += rot;
    notifyNeedsUpdate();
}

void SceneNode::setIsFlipped(bool isFlipped)
{
    isFlipped_ = isFlipped;
    notifyNeedsUpdate();
}

void SceneNode::flip()
{
    isFlipped_ = !isFlipped_;
    notifyNeedsUpdate();
}

void SceneNode::setIsVisible(bool isVisible)
{
    isVisible_ = isVisible;
    notifyNeedsUpdate();
}

const engine::math::Vector<double, 3>& SceneNode::absPos() const
{
    return absPos_;
}

void SceneNode::attach(SceneObject* obj)
{
    sceneObjects_.push_back(obj);
    notifyNeedsUpdate(UpdateType::childNodes);
}

void SceneNode::detach(SceneObject* obj)
{
    sceneObjects_.remove(obj);
    notifyNeedsUpdate(UpdateType::childNodes);
}

void SceneNode::attach(SceneNode* node)
{
    childNodes_.push_back(node);
    node->notifyAttach(this);
    notifyNeedsUpdate(UpdateType::childNodes);
}

void SceneNode::detach(SceneNode* node)
{
    node->notifyDetach();
    childNodes_.remove(node);
    notifyNeedsUpdate(UpdateType::childNodes);
}

void SceneNode::notifyAttach(SceneNode* parent)
{
    parent_ = parent;
}

void SceneNode::notifyDetach()
{
    parent_ = nullptr;
}

void SceneNode::notifyNeedsUpdate(UpdateType type)
{
    if ((neededUpdate_ & UpdateType::pos) == UpdateType::none && (type & UpdateType::pos) == UpdateType::pos) {
        for (auto node : childNodes_)
            node->notifyNeedsUpdate(UpdateType::pos);
        neededUpdate_ = neededUpdate_ | UpdateType::pos;
    }
    if ((neededUpdate_ & UpdateType::childNodes) == UpdateType::none && (type & UpdateType::childNodes) == UpdateType::childNodes) {
        if (parent_)
            parent_->notifyNeedsUpdate(UpdateType::childNodes);
        neededUpdate_ = neededUpdate_ | UpdateType::childNodes;
    }
}

void SceneNode::update()
{
    if (neededUpdate_ == UpdateType::none)
        return;
    if ((neededUpdate_ & UpdateType::pos) != UpdateType::none) {
        if (!parent_) // if this is the root node
        {
            absPos_       = pos_;
            absScale_     = scale_;
            absRot_       = rot_;
            absIsFlipped_ = isFlipped_;
            absIsVisible_ = isVisible_;

        } else {
            const double rad     = math::degToRad(parent_->absRot_);
            const Vector2d scale = parent_->absScale_;
            const double f       = (parent_->absIsFlipped_ ? -1 : 1);
            // Rotation matrix
            const math::Matrix<double, 3, 3> R = { {
                    { f * cos(rad) * scale[1], f * -sin(rad) * scale[0], 0.0 },
                    { sin(rad) * scale[1], cos(rad) * scale[0], 0.0 },
                    { 0.0, 0.0, 1.0 },
            } };

            absPos_       = parent_->absPos_ + R * pos_;
            absScale_     = { scale[0] * scale_[0], scale[1] * scale_[1] };
            absRot_       = parent_->rot_ + rot_;
            absIsFlipped_ = !(parent_->absIsFlipped_ == isFlipped_);
            absIsVisible_ = parent_->absIsVisible_ && isVisible_;
        }
        for (auto obj : sceneObjects_)
            obj->update(absPos_, absScale_, absRot_, absIsFlipped_, absIsVisible_);
        for (auto node : childNodes_)
            node->update();
        neededUpdate_ = UpdateType::none;
    } else if ((neededUpdate_ & UpdateType::childNodes) != UpdateType::none) {
        for (auto obj : sceneObjects_)
            obj->update(absPos_, absScale_, absRot_, absIsFlipped_, absIsVisible_);
        for (auto node : childNodes_)
            node->update();
        neededUpdate_ = UpdateType::none;
    }
}

void SceneNode::collectRenderables(RenderableList& list) const
{
    for (const auto entry : childNodes_) {
        entry->collectRenderables(list);
    }
    for (const auto entry : sceneObjects_) {
        if (entry->isRenderable())
            list.push_back({ absPos_[2], entry });
    }
}
