#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>

#include <memory>
#include "Camera.h"

enum class WalkMode
{
   Crawl,
   Walk,
   Run
};

enum class Direction : int
{
   Forward = 1,
   Backward = 2,
   Left = 4,
   Right = 8,
   Up = 16,
   Down = 32
};

class Player
{
public:
   Player(Prospect::Camera& camera);

   //TODO: Move camera controls inside player class.
   //TODO: Move player class in ProsectEngine.

   void Update(const double timeElapsed);

   void Move(const Direction& direction);

   void Stop(const Direction& direction);

   glm::vec3 GetPosition() const;
   void SetPosition(const glm::vec3& position);

   void SetWalkMode(const WalkMode& walkMode);

private:
   const float m_playerThreshold = 0.01f;
   const float m_playerFriction = 0.25f;

   const float m_playerCrawlSpeed = 0.004f;
   const float m_playerWalkSpeed = 0.01f;
   const float m_playerRunSpeed = 0.02f;
   float m_playerCurrentSpeed = m_playerWalkSpeed;

   int m_directionFlags = 0;
   glm::vec3 m_playerMomentum;
   glm::vec3 m_position;

   Prospect::Camera& m_camera;
};
