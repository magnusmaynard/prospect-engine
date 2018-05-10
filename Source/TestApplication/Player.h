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
   void Update(const double timeElapsed, const Prospect::Camera& camera)
   {
      //Update direction.
      glm::vec3 playerDirection;
      if (m_directionFlags & static_cast<int>(Direction::Forward))
      {
         playerDirection += camera.GetForward();
      }
      if (m_directionFlags & static_cast<int>(Direction::Backward))
      {
         playerDirection -= camera.GetForward();
      }
      if (m_directionFlags & static_cast<int>(Direction::Left))
      {
         playerDirection += camera.GetLeft();
      }
      if (m_directionFlags & static_cast<int>(Direction::Right))
      {
         playerDirection -= camera.GetLeft();
      }
      if (m_directionFlags & static_cast<int>(Direction::Up))
      {
         playerDirection += cross(camera.GetForward(), camera.GetLeft());
      }
      if (m_directionFlags & static_cast<int>(Direction::Down))
      {
         playerDirection -= cross(camera.GetForward(), camera.GetLeft());
      }

      if (length(playerDirection) > m_playerThreshold)
      {
         playerDirection = normalize(playerDirection);
      }
      else
      {
         playerDirection = glm::vec3();
      }

      //Apply direction.
      m_playerMomentum += playerDirection * m_playerCurrentSpeed * static_cast<float>(timeElapsed);

      //Apply friction.
      if (length(m_playerMomentum) > m_playerThreshold)
      {
         m_position += m_playerMomentum;
         m_playerMomentum *= 1.0 - m_playerFriction;
      }
      
   }

   void Move(const Direction& direction)
   {
      m_directionFlags = m_directionFlags | static_cast<int>(direction);
   }

   void Stop(const Direction& direction)
   {
      m_directionFlags = m_directionFlags & ~static_cast<int>(direction);
   }

   glm::vec3 GetPosition() const
   {
      return m_position;
   }

   void SetWalkMode(const WalkMode& walkMode)
   {
      switch (walkMode)
      {
         case WalkMode::Crawl:
            m_playerCurrentSpeed = m_playerCrawlSpeed;
            break;
         case WalkMode::Run:
            m_playerCurrentSpeed = m_playerRunSpeed;
            break;
         default:
         case WalkMode::Walk:
            m_playerCurrentSpeed = m_playerWalkSpeed;
            break;
      }
   }

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
};
