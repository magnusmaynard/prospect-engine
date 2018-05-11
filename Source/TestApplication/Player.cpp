#include "Player.h"

void Player::Update(const double timeElapsed, const Prospect::Camera& camera)
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
   m_playerMomentum += playerDirection * m_playerCurrentSpeed * static_cast<
      float>(timeElapsed);

   //Apply friction.
   if (length(m_playerMomentum) > m_playerThreshold)
   {
      m_position += m_playerMomentum;
      m_playerMomentum *= 1.0 - m_playerFriction;
   }
}

void Player::Move(const Direction& direction)
{
   m_directionFlags = m_directionFlags | static_cast<int>(direction);
}

void Player::Stop(const Direction& direction)
{
   m_directionFlags = m_directionFlags & ~static_cast<int>(direction);
}

glm::vec3 Player::GetPosition() const
{
   return m_position;
}

void Player::SetWalkMode(const WalkMode& walkMode)
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
