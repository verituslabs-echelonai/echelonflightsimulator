/*
 * Copyright 2011 Nate Koenig & Andrew Howard
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
/* Desc: Body class
 * Author: Nate Koenig
 * Date: 13 Feb 2006
 * SVN: $Id$
 */

#ifndef BODY_HH
#define BODY_HH

#include <map>
#include <vector>

#include "Event.hh"
#include "Entity.hh"
#include "Pose3d.hh"
#include "Param.hh"
#include "Mass.hh"

namespace gazebo
{
  class Model;
  class Geom;
  class Sensor;
  class XMLConfigNode;

  /// \addtogroup gazebo_physics
  /// \brief The body class
  /// \{

  /// Body class
  class Body : public Entity
  {
    /// \brief Constructor
    public: Body(Entity *parent);

    /// \brief Destructor
    public: virtual ~Body();

    /// \brief Load the body based on an XMLConfig node
    /// \param node XMLConfigNode pointer
    public: virtual void Load(XMLConfigNode *node);

    /// \brief Save the body based on our XMLConfig node
    public: virtual void Save(std::string &prefix, std::ostream &stream);

    /// \brief Initialize the body
    public: virtual void Init();

    /// \brief Finalize the body
    public: void Fini();

    /// \brief Update the body
    public: virtual void Update();

    /// \brief Attach a geom to this body
    /// \param geom Geometery to attach to this body
    public: virtual void AttachGeom( Geom *geom );

    /// \brief Set whether this body is enabled
    public: virtual void SetEnabled(bool enable) const = 0;

    /// \brief Get whether this body is enabled in the physics engine
    public: virtual bool GetEnabled() const = 0;

    /// \brief Set whether this entity has been selected by the user 
    ///        through the gui
    public: virtual bool SetSelected( bool s );

    /// \brief Update the center of mass
    public: virtual void UpdateCoM();

    /// \brief Set whether gravity affects this body
    public: virtual void SetGravityMode(bool mode) = 0;

    /// \brief Get the gravity mode
    public: virtual bool GetGravityMode() = 0;


    /// \brief Set whether this body will collide with others in the model
    public: virtual void SetSelfCollide(bool collide) = 0;

    /// \brief Set the friction mode of the body
    public: void SetFrictionMode( const bool &v );

    /// \brief Set the collide mode of the body
    public: void SetCollideMode( const std::string &m );

    /// \brief Get Self-Collision Flag, if this is true, this body will collide
    //         with other bodies even if they share the same parent.
    public: bool GetSelfCollide();

    /// \brief Set the laser fiducial integer id
    public: void SetLaserFiducialId(int id);

   /// \brief Set the laser retro reflectiveness
    public: void SetLaserRetro(float retro);

    /// \brief Set the linear velocity of the body
    public: virtual void SetLinearVel(const Vector3 &vel) = 0;

    /// \brief Set the angular velocity of the body
    public: virtual void SetAngularVel(const Vector3 &vel) = 0;

    /// \brief Set the linear acceleration of the body
    public: void SetLinearAccel(const Vector3 &accel);

    /// \brief Set the angular acceleration of the body
    public: void SetAngularAccel(const Vector3 &accel);

    /// \brief Set the force applied to the body
    public: virtual void SetForce(const Vector3 &force) = 0;

    /// \brief Set the torque applied to the body
    public: virtual void SetTorque(const Vector3 &force) = 0;



    /// \brief Get the linear velocity of the body
    public: Vector3 GetRelativeLinearVel() const;

    /// \brief Get the angular velocity of the body
    public: Vector3 GetRelativeAngularVel() const;

    /// \brief Get the linear acceleration of the body
    public: Vector3 GetRelativeLinearAccel() const;

    /// \brief Get the linear acceleration of the body in the world frame
    public: Vector3 GetWorldLinearAccel() const;

    /// \brief Get the angular acceleration of the body
    public: Vector3 GetRelativeAngularAccel() const;

    /// \brief Get the angular acceleration of the body in the world frame
    public: Vector3 GetWorldAngularAccel() const;

    /// \brief Get the force applied to the body
    public: Vector3 GetRelativeForce() const;

    /// \brief Get the force applied to the body in the world frame
    public: virtual Vector3 GetWorldForce() const = 0;

    /// \brief Get the torque applied to the body
    public: Vector3 GetRelativeTorque() const;

    /// \brief Get the torque applied to the body in the world frame
    public: virtual Vector3 GetWorldTorque() const = 0;



    /// \brief Get the vector of all geoms
    public: const std::map<std::string, Geom*> *GetGeoms() const;

    /// \brief Get a geom by name
    public: Geom *GetGeom(const std::string &name) const;

    /// \brief Get the model that this body belongs to
    public: Model *GetModel() const;

    /// \brief Get the mass of the body
    public: const Mass &GetMass() const { return mass; }

    /// \brief Set the mass of the body
    public: void SetMass(Mass mass);

    /// \brief Get the list of interfaces e.g "pioneer2dx_model1::laser::laser_iface0->laser"
    public: void GetInterfaceNames(std::vector<std::string>& list) const;

    /// \brief Get a sensor by name
    public: Sensor *GetSensor( const std::string &name ) const;

    /// Load a new geom helper function
    /// \param node XMLConfigNode used to load the geom
    private: void LoadGeom(XMLConfigNode *node);

    /// Load a new sensor
    /// \param node XMLConfigNode used to load the geom
    private: void LoadSensor(XMLConfigNode *node);

    /// \brief Load a renderable
    private: void LoadVisual(XMLConfigNode *node);

    /// \brief Update the pose of the body
    //protected: void UpdatePose();

    /// \brief Set transparency for all child geometries
    public: void SetTransparent(const bool &show);

    /// \brief Returns list of sensors
    public:  std::vector< Sensor* > &GetSensors();

    /// \brief  Get the size of the body
    public: void GetBoundingBox(Vector3 &min, Vector3 &max) const;

    /// \brief Set the linear damping factor
    public: virtual void SetLinearDamping(double damping) = 0;

    /// \brief Set the angular damping factor
    public: virtual void SetAngularDamping(double damping) = 0;

    /// \brief Set to true to show the physics visualizations
    public: void ShowPhysics(const bool &show);

    public: Entity *GetCoMEntity() { return this->comEntity; }

    /// \brief Set whether this body is in the kinematic state
    public: virtual void SetKinematic(const bool &) {}

    /// \brief Get whether this body is in the kinematic state
    public: virtual bool GetKinematic() const {return false;}

    /// \brief Return true if auto disable is enabled
    public: bool GetAutoDisable() const;

    /// \brief Set the auto disable flag.
    public: virtual void SetAutoDisable(const bool &value);

    /// \brief Connect a to the add entity signal
    public: template<typename T>
            event::ConnectionPtr ConnectEnabledSignal( T subscriber )
            { return enabledSignal.Connect(subscriber); }

    public: void DisconnectEnabledSignal( event::ConnectionPtr &c )
            { enabledSignal.Disconnect(c); }

    /// List of geometries attached to this body
    protected: std::map< std::string, Geom* > geoms;

    /// List of attached sensors
    protected: std::vector< Sensor* > sensors;

    /// Mass properties of the object
    protected: Mass mass;

    protected: bool isStatic;

    /// Used by Model if this body is the canonical body
    ///   model pose = body pose + initModelOffset
    public: Pose3d initModelOffset;

    // Helper entity for separating body pose from center-of-mass pose
    protected: Entity *comEntity;

    /// The pose of the body relative to the model. Can also think of this
    /// as the body's pose offset.
    protected: Pose3d relativePose;

    protected: ParamT<Vector3> *xyzP;
    protected: ParamT<Quatern> *rpyP;

    protected: ParamT<double> *dampingFactorP;

    protected: ParamT<bool> *turnGravityOffP;
    protected: ParamT<bool> *selfCollideP;

    protected: std::vector< std::string > cgVisuals;

    protected: Vector3 linearAccel;
    protected: Vector3 angularAccel;

    ///  User specified Mass Matrix
    protected: ParamT<bool> *autoDisableP;
    protected: ParamT<bool> *customMassMatrixP;
    protected: ParamT<double> *cxP ;
    protected: ParamT<double> *cyP ;
    protected: ParamT<double> *czP ;
    protected: ParamT<double> *bodyMassP;
    protected: ParamT<double> *ixxP;
    protected: ParamT<double> *iyyP;
    protected: ParamT<double> *izzP;
    protected: ParamT<double> *ixyP;
    protected: ParamT<double> *ixzP;
    protected: ParamT<double> *iyzP;
    protected: ParamT<bool> *kinematicP;
    protected: Mass customMass;

    protected: std::vector<std::string> visuals;

    private: event::EventT<void (bool)> enabledSignal;
    private: event::ConnectionPtr showPhysicsConnection; 

    /// This flag is used to trigger the enabledSignal
    private: bool enabled;

    protected: Pose3d newPose;

    private: std::vector<event::ConnectionPtr> connections;
  };

  /// \}
}

#endif
