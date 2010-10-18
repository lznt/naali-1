// For conditions of distribution and use, see copyright notice in license.txt

#ifndef incl_OgreRenderer_EC_Placeable_h
#define incl_OgreRenderer_EC_Placeable_h

#include "IComponent.h"
#include "OgreModuleApi.h"
#include "OgreModuleFwd.h"
#include "Transform.h"
#include "Vector3D.h"
#include "Quaternion.h"
#include "Declare_EC.h"

#include <QQuaternion>
#include <QVector3D>

//! Ogre placeable (scene node) component
/**
<table class="header">
<tr>
<td>
<h2>Placeable</h2>
Ogre (scene node) component.

Registered by OgreRenderer::OgreRenderingModule.

<b>Attributes</b>:
<ul>
<li>Transform: transform
<div>Sets the position, rotation and scale of the entity. Not usable and not replicated in Opensim worlds.</div>
</ul>

<b>Exposes the following scriptable functions:</b>
<ul>
<li>"translate": translate
<li>"LookAt": LookAt wrapper that accepts a QVector3D for py & js e.g. camera use. 
</ul>

<b>Reacts on the following actions:</b>
<ul>
<li>...
</ul>
</td>
</tr>

Does not emit any actions.

<b>Doesn't depend on any components</b>.
</table>
*/
class OGRE_MODULE_API EC_Placeable : public IComponent
{
    DECLARE_EC(EC_Placeable);

    Q_OBJECT
    Q_PROPERTY(QVector3D Position READ GetQPosition WRITE SetQPosition)
    Q_PROPERTY(QVector3D Scale READ GetQScale WRITE SetQScale)
    Q_PROPERTY(QQuaternion Orientation READ GetQOrientation WRITE SetQOrientation)
    Q_PROPERTY(QVector3D LocalXAxis READ GetQLocalXAxis)
    Q_PROPERTY(QVector3D LocalYAxis READ GetQLocalYAxis)
    Q_PROPERTY(QVector3D LocalZAxis READ GetQLocalZAxis)
    Q_PROPERTY(float Yaw READ GetYaw)
    Q_PROPERTY(float Pitch READ GetPitch)
    Q_PROPERTY(float Roll READ GetRoll)
    Q_PROPERTY(int SelectPriority READ GetSelectPriority WRITE SetSelectPriority)

public:
    //! Transformation attribute for position, rotation and scale adjustments.
    //! @todo Transform attribute is not working in js need to expose it to QScriptEngine somehow.
    Q_PROPERTY(Transform transform READ gettransform WRITE settransform);
    DEFINE_QPROPERTY_ATTRIBUTE(Transform, transform);

    virtual ~EC_Placeable();
    
    //! Set component as serializable.
    /*! Note that despite this, in OpenSim worlds, the network sync will be disabled from the component,
        as EC_NetworkPosition controls the actual authoritative position (including interpolation)
     */
    virtual bool IsSerializable() const { return true; }
    
    //! sets parent placeable
    /*! set null placeable to attach to scene root (the default)
        \param placeable new parent
     */
    void SetParent(ComponentPtr placeable);
    
    //! sets position
    /*! \param position new position
     */
    void SetPosition(const Vector3df& position);
    //! sets orientation
    /*! \param orientation new orientation
     */
    void SetOrientation(const Quaternion& orientation);

    //! orients to look at a point in space
    /*! \param look_at point to look at
     */
    void LookAt(const Vector3df& look_at);
    //! yaws the node
    /*! \param radians how many radians to yaw
     */
    void SetYaw(float radians);
    //! pitches the node
    /*! \param radians how many radians to pitch
     */
    void SetPitch(float radians);
    //! rolls the node
    /*! \param radians how many radians to roll
     */
    void SetRoll(float radians);

    //! get the yaw of the node
    float GetYaw() const;
    //! get the pitch of the node
    float GetPitch() const;
    //! get the roll of the node
    float GetRoll() const;
    
    //! sets scale
    /*! \param scale new scale
     */
    void SetScale(const Vector3df& scale);

    //! sets select priority
    /*! \param priority new select priority
     */
    void SetSelectPriority(int priority) { select_priority_ = priority; }
    
    //! gets parent placeable
    ComponentPtr GetParent() { return parent_; }
    
    //! returns position
    Vector3df GetPosition() const;
    //! returns orientation
    Quaternion GetOrientation() const;
    //! returns scale
    Vector3df GetScale() const;

    //! Get the local X axis from the node orientation
    Vector3df GetLocalXAxis() const;
    //! Get the local Y axis from the node orientation
    Vector3df GetLocalYAxis() const;
    //! Get the local Z axis from the node orientation
    Vector3df GetLocalZAxis() const;
    //! Get the local X axis from the node orientation
    QVector3D GetQLocalXAxis() const;
    //! Get the local Y axis from the node orientation
    QVector3D GetQLocalYAxis() const;
    //! Get the local Z axis from the node orientation
    QVector3D GetQLocalZAxis() const;
    
    //! returns Ogre scenenode for attaching geometry.
    /*! Do not manipulate the pos/orientation/scale of this node directly
     */
    Ogre::SceneNode* GetSceneNode() const { return scene_node_; }
   
    //! returns Ogre scenenode for linking another placeable in OpenSim compatible way.
    /*! Only used by other placeables, or in other rare cases. Do not use if GetSceneNode() works for you,
        as this doesn't take scaling into account!
     */
    Ogre::SceneNode* GetLinkSceneNode() const { return link_scene_node_; }
                   
    //! returns select priority
    int GetSelectPriority() const { return select_priority_; }

    //! experimental accessors that use the new 3d vector etc types in Qt 4.6, for qproperties
    QVector3D GetQPosition() const;
    void SetQPosition(const QVector3D newpos);

    //! get node orientation
    QQuaternion GetQOrientation() const;
    //! set node orientation
    void SetQOrientation(const QQuaternion newort);

    //! set node scale
    QVector3D GetQScale() const;
    //! get node scale
    void SetQScale(const QVector3D newscale);


public slots:
    //! translate
    /* 0 = x, 1 = y, 2 = z. returns new position */
    QVector3D translate( int axis, float amount);

    //! LookAt wrapper that accepts a QVector3D for py & js e.g. camera use
    void LookAt(const QVector3D look_at) { LookAt(Vector3df(look_at.x(), look_at.y(), look_at.z())); }

    /// Shows the Entity
    void Show();

	/// Hides the Entity
	void Hide();

	/// Toggle Visibility
	void ToggleVisibility();

private slots:
    //! Handle attributechange
    /*! \param attribute Attribute that changed.
        \param change Change type.
     */
    void HandleAttributeChanged(IAttribute* attribute, AttributeChange::Type change);

    /// Registers the action this EC provides to the parent entity, when it's set.
	void RegisterActions();

private:
    //! constructor
    /*! \param module renderer module
     */
    explicit EC_Placeable(IModule* module);
    
    //! attaches scenenode to parent
    void AttachNode();
    
    //! detaches scenenode from parent
    void DetachNode();
    
    //! renderer
    OgreRenderer::RendererWeakPtr renderer_;
    
    //! parent placeable
    ComponentPtr parent_;
    
    //! Ogre scene node for geometry. scale is handled here
    Ogre::SceneNode* scene_node_;

    //! Ogre scene node for linking. position & orientation are handled here, and the geometry scene node is attached to this
    Ogre::SceneNode* link_scene_node_;
    
    //! attached to scene hierarchy-flag
    bool attached_;
    
    //! selection priority for picking
    int select_priority_;
};

#endif
