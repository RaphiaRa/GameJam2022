#include <catch2/catch_test_macros.hpp>
#include <engine/SceneNode.h>
#include <limits>

using engine::SceneNode;

using Vector3d = engine::math::Vector<double, 3>;
using Vector2d = engine::math::Vector<double, 2>;
class MockSceneObject : public engine::SceneObject {
    void update(const Vector3d& pos, const Vector2d& scale, double rot, bool isFlipped, bool isVisible) override;
    void notifyAttach() override;
    void notifyDetach() override;

  public:
    ~MockSceneObject() override = default;
    Vector3d pos_               = { 0.0, 0.0, 0.0 };
    Vector2d scale_             = { 0.0, 0.0 };
    double rot_                 = 0.0;
    bool isFlipped_             = false;
    bool isVisible_             = false;
    bool isAttached_            = false;
};

TEST_CASE("SceneNodes are created", "[SceneNode::SceneNode()]")
{
    SECTION("Default SceneNode")
    {
        SceneNode node;
        CHECK(node.id() == "Node");
    }
    SECTION("SceneNode with custom id")
    {
        SceneNode node("TestNode");
        CHECK(node.id() == "TestNode");
    }
}

TEST_CASE("Objects are attached to SceneNodes", "[SceneNode::attach()]")
{
    SceneNode rootNode;
    MockSceneObject obj;
    rootNode.attach(&obj);
    rootNode.update();
    SECTION("Obj is attached and has default position values")
    {
        CHECK(obj.isAttached_);
        CHECK(obj.pos_ == Vector3d{ 0.0, 0.0, 0.0 });
        CHECK(obj.scale_ == Vector2d{ 1.0, 1.0 });
        CHECK(obj.rot_ == 0.0);
        CHECK(obj.isVisible_);
        CHECK(obj.isFlipped_ == false);
        SECTION("Detach object")
        {
            rootNode.detach(&obj);
            CHECK(!obj.isAttached_);
        }
    }
}

TEST_CASE("SceneNodes are translated", "[SceneNode::translate()]")
{
    SceneNode rootNode;
    SceneNode childNode;
    MockSceneObject obj;
    rootNode.attach(&childNode);
    childNode.attach(&obj);
    rootNode.update();
    SECTION("Obj has default position values")
    {
        CHECK(obj.pos_ == Vector3d{ 0.0, 0.0, 0.0 });
    }
    SECTION("Translate childNode")
    {
        childNode.translate(Vector3d{ 5.0, 3.5, 0.0 });
        rootNode.update();
        CHECK(obj.pos_ == Vector3d{ 5.0, 3.5, 0.0 });
        childNode.translate(Vector3d{ 1.0, 1.5, 0.0 });
        childNode.translate(Vector3d{ 1.0, 1.0, 0.0 });
        rootNode.update();
        CHECK(obj.pos_ == Vector3d{ 7.0, 6.0, 0.0 });
        SECTION("Translate rootNode")
        {
            rootNode.translate(Vector3d{ 1.0, 1.0, 1.0 });
            rootNode.update();
            CHECK(obj.pos_ == Vector3d{ 8.0, 7.0, 1.0 });
        }
    }
}

TEST_CASE("SceneNode's visbility is changed", "[SceneNode::setIsVisible]")
{
    SceneNode rootNode;
    SceneNode childNode;
    MockSceneObject obj;
    rootNode.attach(&childNode);
    childNode.attach(&obj);
    rootNode.update();
    SECTION("Obj is visible by default")
    {
        CHECK(obj.isVisible_);
    }
    SECTION("Hide childNode")
    {
        childNode.setIsVisible(false);
        rootNode.update();
        CHECK(!obj.isVisible_);
    }
    SECTION("Hide rootNode")
    {
        rootNode.setIsVisible(false);
        rootNode.update();
        CHECK(!obj.isVisible_);
    }
}

TEST_CASE("SceneNode is scaled", "[SceneNode::scale]")
{
    SceneNode rootNode;
    SceneNode childNode;
    MockSceneObject obj;
    rootNode.attach(&childNode);
    childNode.attach(&obj);
    childNode.setPos(Vector3d({ 1.0, 0.0, 0.0 }));
    rootNode.update();
    SECTION("Obj is not scaled by default")
    {
        CHECK(obj.scale_ == Vector2d({ 1.0, 1.0 }));
    }
    SECTION("Scale childNode by factor 2")
    {
        childNode.scale(Vector2d{ 2.0, 2.0 });
        rootNode.update();
        CHECK(obj.pos_ == Vector3d({ 1.0, 0.0, 0.0 }));
        CHECK(obj.scale_ == Vector2d({ 2.0, 2.0 }));
    }
    SECTION("Scale rootNode by factor 2")
    {
        rootNode.scale(Vector2d{ 2.0, 2.0 });
        rootNode.update();
        CHECK(obj.pos_ == Vector3d({ 2.0, 0.0, 0.0 }));
        CHECK(obj.scale_ == Vector2d({ 2.0, 2.0 }));
    }
}

TEST_CASE("SceneNode is rotated", "[SceneNode::rot]")
{
    SceneNode rootNode;
    SceneNode childNode;
    MockSceneObject obj;
    rootNode.attach(&childNode);
    childNode.attach(&obj);
    childNode.setPos(Vector3d({ 1.0, 0.0, 0.0 }));
    rootNode.update();
    SECTION("Obj is not rotated by default")
    {
        CHECK(obj.rot_ == 0);
    }
    SECTION("Rotate childNode by 90 degrees")
    {
        childNode.rotate(90);
        rootNode.update();
        CHECK(obj.pos_ == Vector3d({ 1.0, 0.0, 0.0 }));
        CHECK(obj.rot_ == 90);
    }
    SECTION("Rotate rootNode by 90 degrees")
    {
        rootNode.rotate(90);
        rootNode.update();
        CHECK(engine::math::max_norm(obj.pos_ - Vector3d({ 0.0, 1.0, 0.0 })) < std::numeric_limits<double>::epsilon());
        CHECK(obj.rot_ == 90);
    }
}

TEST_CASE("SceneNode is flipped", "[SceneNode::flip]")
{
    SceneNode rootNode;
    SceneNode childNode;
    MockSceneObject obj;
    rootNode.attach(&childNode);
    childNode.attach(&obj);
    childNode.setPos(Vector3d({ 1.0, 0.0, 0.0 }));
    rootNode.update();
    SECTION("Obj is not flipped by default")
    {
        CHECK(!obj.isFlipped_);
    }
    SECTION("Attached object are flipped when childNode is flipped")
    {
        childNode.flip();
        rootNode.update();
        CHECK(obj.isFlipped_);
        CHECK(obj.pos_ == Vector3d({ 1.0, 0.0, 0.0 }));
        SECTION("Attached object are flipped again relative to the rootNode when rootNode is flipped")
        {
            rootNode.flip();
            rootNode.update();
            CHECK(!obj.isFlipped_);
            CHECK(obj.pos_ == Vector3d({ -1.0, 0.0, 0.0 }));
        }
    }
}

void MockSceneObject::update(const Vector3d& pos, const Vector2d& scale, double rot, bool isFlipped, bool isVisible)
{
    pos_       = pos;
    scale_     = scale;
    rot_       = rot;
    isFlipped_ = isFlipped;
    isVisible_ = isVisible;
}

void MockSceneObject::notifyAttach()
{
    isAttached_ = true;
}
void MockSceneObject::notifyDetach()
{
    isAttached_ = false;
}
