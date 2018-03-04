#include "ProspectEngine_pch.h"

#include "LightingPass.h"

#include "Renderer/Pipeline/ShaderLibrary.h"
#include "Renderer/Pipeline/GBuffer.h"
#include "Renderer/ShadowMap.h"

using namespace Prospect;
using namespace glm;

LightingPass::LightingPass(
   ShaderLibrary& shaderLibrary,
   const GBuffer& gbuffer)
   :
   m_shader(shaderLibrary.GetLightingShader()),
   m_gBuffer(gbuffer)
{
}

void LightingPass::Render(const ShadowMap& shadowMap)
{
   //Move [-1, 1] space to [0, 1] required for sampling textures.
   const mat4 biasMatrix(
      0.5, 0.0, 0.0, 0.0,
      0.0, 0.5, 0.0, 0.0,
      0.0, 0.0, 0.5, 0.0,
      0.5, 0.5, 0.5, 1.0
   );
   const auto shadowMatrix = biasMatrix * shadowMap.GetProjection() * shadowMap.GetView();

   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glDisable(GL_DEPTH_TEST);
   glBlendFunc(GL_ONE, GL_ZERO);

   glDrawBuffer(GL_BACK);
   glBindTextureUnit(0, m_gBuffer.GetAlbedoTexture());
   glBindTextureUnit(1, m_gBuffer.GetNormalTexture());
   glBindTextureUnit(2, m_gBuffer.GetSpecularTexture());
   glBindTextureUnit(3, m_gBuffer.GetDepthTexture());

   //TEMP
   glBindTextureUnit(4, shadowMap.GetShadowTexture());

   m_shader.Bind();

   const GLuint shadowMatrixUniformLocation = m_shader.GetUniformLocation("shadowMatrix");
   glUniformMatrix4fv(shadowMatrixUniformLocation, 1, GL_FALSE, &shadowMatrix[0][0]);

   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
