/********************************************************
 * This file is generated by RGDE EffectGenerator.      *
 * (c) RGDE Team. 2006.                                 *
 ********************************************************/


#include "../Parameters.fx"


/********************************************************
 * This technique is generated by RGDE EffectGenerator. *
 * (c) RGDE Team. 2006.                                 *
 ********************************************************/
technique BumpIlluminationReflectionCubeTransparent
{
   pass pass0
   {
      MaterialAmbient = (vAmbientColor);
      MaterialDiffuse = (vDiffuseColor);
      MaterialEmissive = (vEmissiveColor);
      MaterialSpecular = (vSpecularColor);
      MaterialPower = (fPower);
      Sampler[0] = (SamplerIllumination);
      Sampler[1] = (SamplerReflection);
      ColorOp[0] = ADD;
      ColorOp[1] = ADD;
      ColorOp[2] = DISABLE;
      ColorOp[3] = DISABLE;
      AlphaOp[0] = SELECTARG1;
      AlphaOp[1] = DISABLE;
      AlphaOp[2] = DISABLE;
      AlphaOp[3] = DISABLE;
      AlphaArg1[0] = CURRENT;
      ColorArg0[0] = CURRENT;
      ColorArg0[1] = CURRENT;
      ColorArg1[0] = TEXTURE;
      ColorArg1[1] = TEXTURE;
      TexCoordIndex[0] = PASSTHRU;
      TexCoordIndex[1] = CAMERASPACEREFLECTIONVECTOR;
      FogEnable = (fog.bEnabled);
      FogColor = (fog.color);
      FogTableMode = (fog.iMode);
      FogStart = (fog.fStart);
      FogEnd = (fog.fEnd);
      SpecularEnable = true;
      ColorVertex = true;
      Lighting = (LightingEnabled);
      Ambient = (vAmbientLight);
      CullMode = CW;
      FillMode = (FillMode);
      NormalizeNormals = true;
      ZEnable = true;
      AlphaBlendEnable = true;
      SrcBlend = SRCALPHA;
      DestBlend = INVSRCALPHA;
      ZWriteEnable = false;
      ViewTransform = (View);
      ProjectionTransform = (Projection);
      WorldTransform[0] = (World);
      LightPosition[0] = (lights[0].vPos);
      LightPosition[1] = (lights[1].vPos);
      LightPosition[2] = (lights[2].vPos);
      LightPosition[3] = (lights[3].vPos);
      LightPosition[4] = (lights[4].vPos);
      LightPosition[5] = (lights[5].vPos);
      LightPosition[6] = (lights[6].vPos);
      LightPosition[7] = (lights[7].vPos);
      LightDirection[0] = (lights[0].vDir);
      LightDirection[1] = (lights[1].vDir);
      LightDirection[2] = (lights[2].vDir);
      LightDirection[3] = (lights[3].vDir);
      LightDirection[4] = (lights[4].vDir);
      LightDirection[5] = (lights[5].vDir);
      LightDirection[6] = (lights[6].vDir);
      LightDirection[7] = (lights[7].vDir);
      LightDiffuse[0] = (lights[0].vDiffuse);
      LightDiffuse[1] = (lights[1].vDiffuse);
      LightDiffuse[2] = (lights[2].vDiffuse);
      LightDiffuse[3] = (lights[3].vDiffuse);
      LightDiffuse[4] = (lights[4].vDiffuse);
      LightDiffuse[5] = (lights[5].vDiffuse);
      LightDiffuse[6] = (lights[6].vDiffuse);
      LightDiffuse[7] = (lights[7].vDiffuse);
      LightSpecular[0] = (lights[0].vSpecular);
      LightSpecular[1] = (lights[1].vSpecular);
      LightSpecular[2] = (lights[2].vSpecular);
      LightSpecular[3] = (lights[3].vSpecular);
      LightSpecular[4] = (lights[4].vSpecular);
      LightSpecular[5] = (lights[5].vSpecular);
      LightSpecular[6] = (lights[6].vSpecular);
      LightSpecular[7] = (lights[7].vSpecular);
      LightAmbient[0] = (lights[0].vAmbient);
      LightAmbient[1] = (lights[1].vAmbient);
      LightAmbient[2] = (lights[2].vAmbient);
      LightAmbient[3] = (lights[3].vAmbient);
      LightAmbient[4] = (lights[4].vAmbient);
      LightAmbient[5] = (lights[5].vAmbient);
      LightAmbient[6] = (lights[6].vAmbient);
      LightAmbient[7] = (lights[7].vAmbient);
      LightEnable[0] = (lights[0].bEnabled);
      LightEnable[1] = (lights[1].bEnabled);
      LightEnable[2] = (lights[2].bEnabled);
      LightEnable[3] = (lights[3].bEnabled);
      LightEnable[4] = (lights[4].bEnabled);
      LightEnable[5] = (lights[5].bEnabled);
      LightEnable[6] = (lights[6].bEnabled);
      LightEnable[7] = (lights[7].bEnabled);
      LightRange[0] = (lights[0].fRange);
      LightRange[1] = (lights[1].fRange);
      LightRange[2] = (lights[2].fRange);
      LightRange[3] = (lights[3].fRange);
      LightRange[4] = (lights[4].fRange);
      LightRange[5] = (lights[5].fRange);
      LightRange[6] = (lights[6].fRange);
      LightRange[7] = (lights[7].fRange);
      LightFalloff[0] = (lights[0].vSpot.z);
      LightFalloff[1] = (lights[1].vSpot.z);
      LightFalloff[2] = (lights[2].vSpot.z);
      LightFalloff[3] = (lights[3].vSpot.z);
      LightFalloff[4] = (lights[4].vSpot.z);
      LightFalloff[5] = (lights[5].vSpot.z);
      LightFalloff[6] = (lights[6].vSpot.z);
      LightFalloff[7] = (lights[7].vSpot.z);
      LightTheta[0] = (lights[0].vSpot.x);
      LightTheta[1] = (lights[1].vSpot.x);
      LightTheta[2] = (lights[2].vSpot.x);
      LightTheta[3] = (lights[3].vSpot.x);
      LightTheta[4] = (lights[4].vSpot.x);
      LightTheta[5] = (lights[5].vSpot.x);
      LightTheta[6] = (lights[6].vSpot.x);
      LightTheta[7] = (lights[7].vSpot.x);
      LightPhi[0] = (lights[0].vSpot.y);
      LightPhi[1] = (lights[1].vSpot.y);
      LightPhi[2] = (lights[2].vSpot.y);
      LightPhi[3] = (lights[3].vSpot.y);
      LightPhi[4] = (lights[4].vSpot.y);
      LightPhi[5] = (lights[5].vSpot.y);
      LightPhi[6] = (lights[6].vSpot.y);
      LightPhi[7] = (lights[7].vSpot.y);
      LightAttenuation0[0] = (lights[0].vAttenuation.x);
      LightAttenuation0[1] = (lights[1].vAttenuation.x);
      LightAttenuation0[2] = (lights[2].vAttenuation.x);
      LightAttenuation0[3] = (lights[3].vAttenuation.x);
      LightAttenuation0[4] = (lights[4].vAttenuation.x);
      LightAttenuation0[5] = (lights[5].vAttenuation.x);
      LightAttenuation0[6] = (lights[6].vAttenuation.x);
      LightAttenuation0[7] = (lights[7].vAttenuation.x);
      LightAttenuation1[0] = (lights[0].vAttenuation.y);
      LightAttenuation1[1] = (lights[1].vAttenuation.y);
      LightAttenuation1[2] = (lights[2].vAttenuation.y);
      LightAttenuation1[3] = (lights[3].vAttenuation.y);
      LightAttenuation1[4] = (lights[4].vAttenuation.y);
      LightAttenuation1[5] = (lights[5].vAttenuation.y);
      LightAttenuation1[6] = (lights[6].vAttenuation.y);
      LightAttenuation1[7] = (lights[7].vAttenuation.y);
      LightAttenuation2[0] = (lights[0].vAttenuation.z);
      LightAttenuation2[1] = (lights[1].vAttenuation.z);
      LightAttenuation2[2] = (lights[2].vAttenuation.z);
      LightAttenuation2[3] = (lights[3].vAttenuation.z);
      LightAttenuation2[4] = (lights[4].vAttenuation.z);
      LightAttenuation2[5] = (lights[5].vAttenuation.z);
      LightAttenuation2[6] = (lights[6].vAttenuation.z);
      LightAttenuation2[7] = (lights[7].vAttenuation.z);
      LightType[0] = (lights[0].iType);
      LightType[1] = (lights[1].iType);
      LightType[2] = (lights[2].iType);
      LightType[3] = (lights[3].iType);
      LightType[4] = (lights[4].iType);
      LightType[5] = (lights[5].iType);
      LightType[6] = (lights[6].iType);
      LightType[7] = (lights[7].iType);
   }
   pass pass1
   {
      MaterialAmbient = (vAmbientColor);
      MaterialDiffuse = (vDiffuseColor);
      MaterialEmissive = (vEmissiveColor);
      MaterialSpecular = (vSpecularColor);
      MaterialPower = (fPower);
      Sampler[0] = (SamplerIllumination);
      Sampler[1] = (SamplerReflection);
      ColorOp[0] = ADD;
      ColorOp[1] = ADD;
      ColorOp[2] = DISABLE;
      ColorOp[3] = DISABLE;
      AlphaOp[0] = SELECTARG1;
      AlphaOp[1] = DISABLE;
      AlphaOp[2] = DISABLE;
      AlphaOp[3] = DISABLE;
      AlphaArg1[0] = CURRENT;
      ColorArg0[0] = CURRENT;
      ColorArg0[1] = CURRENT;
      ColorArg1[0] = TEXTURE;
      ColorArg1[1] = TEXTURE;
      TexCoordIndex[0] = PASSTHRU;
      TexCoordIndex[1] = CAMERASPACEREFLECTIONVECTOR;
      FogEnable = (fog.bEnabled);
      FogColor = (fog.color);
      FogTableMode = (fog.iMode);
      FogStart = (fog.fStart);
      FogEnd = (fog.fEnd);
      SpecularEnable = true;
      ColorVertex = true;
      Lighting = (LightingEnabled);
      Ambient = (vAmbientLight);
      CullMode = CW;
      FillMode = (FillMode);
      NormalizeNormals = true;
      ZEnable = true;
      AlphaBlendEnable = true;
      SrcBlend = SRCALPHA;
      DestBlend = INVSRCALPHA;
      ZWriteEnable = false;
      ViewTransform = (View);
      ProjectionTransform = (Projection);
      WorldTransform[0] = (World);
      LightPosition[0] = (lights[0].vPos);
      LightPosition[1] = (lights[1].vPos);
      LightPosition[2] = (lights[2].vPos);
      LightPosition[3] = (lights[3].vPos);
      LightPosition[4] = (lights[4].vPos);
      LightPosition[5] = (lights[5].vPos);
      LightPosition[6] = (lights[6].vPos);
      LightPosition[7] = (lights[7].vPos);
      LightDirection[0] = (lights[0].vDir);
      LightDirection[1] = (lights[1].vDir);
      LightDirection[2] = (lights[2].vDir);
      LightDirection[3] = (lights[3].vDir);
      LightDirection[4] = (lights[4].vDir);
      LightDirection[5] = (lights[5].vDir);
      LightDirection[6] = (lights[6].vDir);
      LightDirection[7] = (lights[7].vDir);
      LightDiffuse[0] = (lights[0].vDiffuse);
      LightDiffuse[1] = (lights[1].vDiffuse);
      LightDiffuse[2] = (lights[2].vDiffuse);
      LightDiffuse[3] = (lights[3].vDiffuse);
      LightDiffuse[4] = (lights[4].vDiffuse);
      LightDiffuse[5] = (lights[5].vDiffuse);
      LightDiffuse[6] = (lights[6].vDiffuse);
      LightDiffuse[7] = (lights[7].vDiffuse);
      LightSpecular[0] = (lights[0].vSpecular);
      LightSpecular[1] = (lights[1].vSpecular);
      LightSpecular[2] = (lights[2].vSpecular);
      LightSpecular[3] = (lights[3].vSpecular);
      LightSpecular[4] = (lights[4].vSpecular);
      LightSpecular[5] = (lights[5].vSpecular);
      LightSpecular[6] = (lights[6].vSpecular);
      LightSpecular[7] = (lights[7].vSpecular);
      LightAmbient[0] = (lights[0].vAmbient);
      LightAmbient[1] = (lights[1].vAmbient);
      LightAmbient[2] = (lights[2].vAmbient);
      LightAmbient[3] = (lights[3].vAmbient);
      LightAmbient[4] = (lights[4].vAmbient);
      LightAmbient[5] = (lights[5].vAmbient);
      LightAmbient[6] = (lights[6].vAmbient);
      LightAmbient[7] = (lights[7].vAmbient);
      LightEnable[0] = (lights[0].bEnabled);
      LightEnable[1] = (lights[1].bEnabled);
      LightEnable[2] = (lights[2].bEnabled);
      LightEnable[3] = (lights[3].bEnabled);
      LightEnable[4] = (lights[4].bEnabled);
      LightEnable[5] = (lights[5].bEnabled);
      LightEnable[6] = (lights[6].bEnabled);
      LightEnable[7] = (lights[7].bEnabled);
      LightRange[0] = (lights[0].fRange);
      LightRange[1] = (lights[1].fRange);
      LightRange[2] = (lights[2].fRange);
      LightRange[3] = (lights[3].fRange);
      LightRange[4] = (lights[4].fRange);
      LightRange[5] = (lights[5].fRange);
      LightRange[6] = (lights[6].fRange);
      LightRange[7] = (lights[7].fRange);
      LightFalloff[0] = (lights[0].vSpot.z);
      LightFalloff[1] = (lights[1].vSpot.z);
      LightFalloff[2] = (lights[2].vSpot.z);
      LightFalloff[3] = (lights[3].vSpot.z);
      LightFalloff[4] = (lights[4].vSpot.z);
      LightFalloff[5] = (lights[5].vSpot.z);
      LightFalloff[6] = (lights[6].vSpot.z);
      LightFalloff[7] = (lights[7].vSpot.z);
      LightTheta[0] = (lights[0].vSpot.x);
      LightTheta[1] = (lights[1].vSpot.x);
      LightTheta[2] = (lights[2].vSpot.x);
      LightTheta[3] = (lights[3].vSpot.x);
      LightTheta[4] = (lights[4].vSpot.x);
      LightTheta[5] = (lights[5].vSpot.x);
      LightTheta[6] = (lights[6].vSpot.x);
      LightTheta[7] = (lights[7].vSpot.x);
      LightPhi[0] = (lights[0].vSpot.y);
      LightPhi[1] = (lights[1].vSpot.y);
      LightPhi[2] = (lights[2].vSpot.y);
      LightPhi[3] = (lights[3].vSpot.y);
      LightPhi[4] = (lights[4].vSpot.y);
      LightPhi[5] = (lights[5].vSpot.y);
      LightPhi[6] = (lights[6].vSpot.y);
      LightPhi[7] = (lights[7].vSpot.y);
      LightAttenuation0[0] = (lights[0].vAttenuation.x);
      LightAttenuation0[1] = (lights[1].vAttenuation.x);
      LightAttenuation0[2] = (lights[2].vAttenuation.x);
      LightAttenuation0[3] = (lights[3].vAttenuation.x);
      LightAttenuation0[4] = (lights[4].vAttenuation.x);
      LightAttenuation0[5] = (lights[5].vAttenuation.x);
      LightAttenuation0[6] = (lights[6].vAttenuation.x);
      LightAttenuation0[7] = (lights[7].vAttenuation.x);
      LightAttenuation1[0] = (lights[0].vAttenuation.y);
      LightAttenuation1[1] = (lights[1].vAttenuation.y);
      LightAttenuation1[2] = (lights[2].vAttenuation.y);
      LightAttenuation1[3] = (lights[3].vAttenuation.y);
      LightAttenuation1[4] = (lights[4].vAttenuation.y);
      LightAttenuation1[5] = (lights[5].vAttenuation.y);
      LightAttenuation1[6] = (lights[6].vAttenuation.y);
      LightAttenuation1[7] = (lights[7].vAttenuation.y);
      LightAttenuation2[0] = (lights[0].vAttenuation.z);
      LightAttenuation2[1] = (lights[1].vAttenuation.z);
      LightAttenuation2[2] = (lights[2].vAttenuation.z);
      LightAttenuation2[3] = (lights[3].vAttenuation.z);
      LightAttenuation2[4] = (lights[4].vAttenuation.z);
      LightAttenuation2[5] = (lights[5].vAttenuation.z);
      LightAttenuation2[6] = (lights[6].vAttenuation.z);
      LightAttenuation2[7] = (lights[7].vAttenuation.z);
      LightType[0] = (lights[0].iType);
      LightType[1] = (lights[1].iType);
      LightType[2] = (lights[2].iType);
      LightType[3] = (lights[3].iType);
      LightType[4] = (lights[4].iType);
      LightType[5] = (lights[5].iType);
      LightType[6] = (lights[6].iType);
      LightType[7] = (lights[7].iType);
      MaterialAmbient = (vAmbientColor);
      MaterialDiffuse = (vDiffuseColor);
      MaterialEmissive = (vEmissiveColor);
      MaterialSpecular = (vSpecularColor);
      MaterialPower = (fPower);
      Sampler[0] = (SamplerIllumination);
      Sampler[1] = (SamplerReflection);
      ColorOp[0] = ADD;
      ColorOp[1] = ADD;
      ColorOp[2] = DISABLE;
      ColorOp[3] = DISABLE;
      AlphaOp[0] = SELECTARG1;
      AlphaOp[1] = DISABLE;
      AlphaOp[2] = DISABLE;
      AlphaOp[3] = DISABLE;
      AlphaArg1[0] = CURRENT;
      ColorArg0[0] = CURRENT;
      ColorArg0[1] = CURRENT;
      ColorArg1[0] = TEXTURE;
      ColorArg1[1] = TEXTURE;
      TexCoordIndex[0] = PASSTHRU;
      TexCoordIndex[1] = CAMERASPACEREFLECTIONVECTOR;
      FogEnable = (fog.bEnabled);
      FogColor = (fog.color);
      FogTableMode = (fog.iMode);
      FogStart = (fog.fStart);
      FogEnd = (fog.fEnd);
      SpecularEnable = true;
      ColorVertex = true;
      Lighting = (LightingEnabled);
      Ambient = (vAmbientLight);
      CullMode = CCW;
      FillMode = (FillMode);
      NormalizeNormals = true;
      ZEnable = true;
      AlphaBlendEnable = true;
      SrcBlend = SRCALPHA;
      DestBlend = INVSRCALPHA;
      ZWriteEnable = false;
      ViewTransform = (View);
      ProjectionTransform = (Projection);
      WorldTransform[0] = (World);
      LightPosition[0] = (lights[0].vPos);
      LightPosition[1] = (lights[1].vPos);
      LightPosition[2] = (lights[2].vPos);
      LightPosition[3] = (lights[3].vPos);
      LightPosition[4] = (lights[4].vPos);
      LightPosition[5] = (lights[5].vPos);
      LightPosition[6] = (lights[6].vPos);
      LightPosition[7] = (lights[7].vPos);
      LightDirection[0] = (lights[0].vDir);
      LightDirection[1] = (lights[1].vDir);
      LightDirection[2] = (lights[2].vDir);
      LightDirection[3] = (lights[3].vDir);
      LightDirection[4] = (lights[4].vDir);
      LightDirection[5] = (lights[5].vDir);
      LightDirection[6] = (lights[6].vDir);
      LightDirection[7] = (lights[7].vDir);
      LightDiffuse[0] = (lights[0].vDiffuse);
      LightDiffuse[1] = (lights[1].vDiffuse);
      LightDiffuse[2] = (lights[2].vDiffuse);
      LightDiffuse[3] = (lights[3].vDiffuse);
      LightDiffuse[4] = (lights[4].vDiffuse);
      LightDiffuse[5] = (lights[5].vDiffuse);
      LightDiffuse[6] = (lights[6].vDiffuse);
      LightDiffuse[7] = (lights[7].vDiffuse);
      LightSpecular[0] = (lights[0].vSpecular);
      LightSpecular[1] = (lights[1].vSpecular);
      LightSpecular[2] = (lights[2].vSpecular);
      LightSpecular[3] = (lights[3].vSpecular);
      LightSpecular[4] = (lights[4].vSpecular);
      LightSpecular[5] = (lights[5].vSpecular);
      LightSpecular[6] = (lights[6].vSpecular);
      LightSpecular[7] = (lights[7].vSpecular);
      LightAmbient[0] = (lights[0].vAmbient);
      LightAmbient[1] = (lights[1].vAmbient);
      LightAmbient[2] = (lights[2].vAmbient);
      LightAmbient[3] = (lights[3].vAmbient);
      LightAmbient[4] = (lights[4].vAmbient);
      LightAmbient[5] = (lights[5].vAmbient);
      LightAmbient[6] = (lights[6].vAmbient);
      LightAmbient[7] = (lights[7].vAmbient);
      LightEnable[0] = (lights[0].bEnabled);
      LightEnable[1] = (lights[1].bEnabled);
      LightEnable[2] = (lights[2].bEnabled);
      LightEnable[3] = (lights[3].bEnabled);
      LightEnable[4] = (lights[4].bEnabled);
      LightEnable[5] = (lights[5].bEnabled);
      LightEnable[6] = (lights[6].bEnabled);
      LightEnable[7] = (lights[7].bEnabled);
      LightRange[0] = (lights[0].fRange);
      LightRange[1] = (lights[1].fRange);
      LightRange[2] = (lights[2].fRange);
      LightRange[3] = (lights[3].fRange);
      LightRange[4] = (lights[4].fRange);
      LightRange[5] = (lights[5].fRange);
      LightRange[6] = (lights[6].fRange);
      LightRange[7] = (lights[7].fRange);
      LightFalloff[0] = (lights[0].vSpot.z);
      LightFalloff[1] = (lights[1].vSpot.z);
      LightFalloff[2] = (lights[2].vSpot.z);
      LightFalloff[3] = (lights[3].vSpot.z);
      LightFalloff[4] = (lights[4].vSpot.z);
      LightFalloff[5] = (lights[5].vSpot.z);
      LightFalloff[6] = (lights[6].vSpot.z);
      LightFalloff[7] = (lights[7].vSpot.z);
      LightTheta[0] = (lights[0].vSpot.x);
      LightTheta[1] = (lights[1].vSpot.x);
      LightTheta[2] = (lights[2].vSpot.x);
      LightTheta[3] = (lights[3].vSpot.x);
      LightTheta[4] = (lights[4].vSpot.x);
      LightTheta[5] = (lights[5].vSpot.x);
      LightTheta[6] = (lights[6].vSpot.x);
      LightTheta[7] = (lights[7].vSpot.x);
      LightPhi[0] = (lights[0].vSpot.y);
      LightPhi[1] = (lights[1].vSpot.y);
      LightPhi[2] = (lights[2].vSpot.y);
      LightPhi[3] = (lights[3].vSpot.y);
      LightPhi[4] = (lights[4].vSpot.y);
      LightPhi[5] = (lights[5].vSpot.y);
      LightPhi[6] = (lights[6].vSpot.y);
      LightPhi[7] = (lights[7].vSpot.y);
      LightAttenuation0[0] = (lights[0].vAttenuation.x);
      LightAttenuation0[1] = (lights[1].vAttenuation.x);
      LightAttenuation0[2] = (lights[2].vAttenuation.x);
      LightAttenuation0[3] = (lights[3].vAttenuation.x);
      LightAttenuation0[4] = (lights[4].vAttenuation.x);
      LightAttenuation0[5] = (lights[5].vAttenuation.x);
      LightAttenuation0[6] = (lights[6].vAttenuation.x);
      LightAttenuation0[7] = (lights[7].vAttenuation.x);
      LightAttenuation1[0] = (lights[0].vAttenuation.y);
      LightAttenuation1[1] = (lights[1].vAttenuation.y);
      LightAttenuation1[2] = (lights[2].vAttenuation.y);
      LightAttenuation1[3] = (lights[3].vAttenuation.y);
      LightAttenuation1[4] = (lights[4].vAttenuation.y);
      LightAttenuation1[5] = (lights[5].vAttenuation.y);
      LightAttenuation1[6] = (lights[6].vAttenuation.y);
      LightAttenuation1[7] = (lights[7].vAttenuation.y);
      LightAttenuation2[0] = (lights[0].vAttenuation.z);
      LightAttenuation2[1] = (lights[1].vAttenuation.z);
      LightAttenuation2[2] = (lights[2].vAttenuation.z);
      LightAttenuation2[3] = (lights[3].vAttenuation.z);
      LightAttenuation2[4] = (lights[4].vAttenuation.z);
      LightAttenuation2[5] = (lights[5].vAttenuation.z);
      LightAttenuation2[6] = (lights[6].vAttenuation.z);
      LightAttenuation2[7] = (lights[7].vAttenuation.z);
      LightType[0] = (lights[0].iType);
      LightType[1] = (lights[1].iType);
      LightType[2] = (lights[2].iType);
      LightType[3] = (lights[3].iType);
      LightType[4] = (lights[4].iType);
      LightType[5] = (lights[5].iType);
      LightType[6] = (lights[6].iType);
      LightType[7] = (lights[7].iType);
   }
}