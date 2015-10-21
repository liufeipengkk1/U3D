Shader "Custom/SpecularLightModel" {
	Properties {
		_Color ("Diffuse Material Color", Color) = (1,1,1,1)
		_SpecColor ("Specular Material Color", Color) = (1,1,1,1) 
		_Shineness("Shineness",Range(1,20)) = 10
		_Attenuation("attenuation ",Range(0,1)) = 1
	}
	SubShader {
		
		Pass
		{
			Tags {"LightMode" = "ForwardBase"}
			
			CGPROGRAM
			
			#include "UnityCG.cginc"
			#pragma vertex vert
			#pragma fragment frag
			
			uniform float4 _LightColor0;
			float4 _Color;
			float4 _SpecColor; 
			float _Shineness;
			float _Attenuation;
			
			struct vertexInput
			{
				float4 pos:POSITION;
				float3 normal:NORMAL;
			};
			
			struct vertexOutput
			{
				float4 pos:SV_POSITION;
				float4 col:COLOR;
			};
			
			
			vertexOutput vert(vertexInput input)
			{
				vertexOutput o ;
				float3 viewDirection = normalize(_WorldSpaceCameraPos - mul(_Object2World,input.pos).xyz);
				float3 normalDirection = normalize(mul(_Object2World,float4(input.normal,0)).xyz);
				
				float3 lightDirection ;
				float attenuation;
				
				if(_WorldSpaceLightPos0.w == 0)
				{
					attenuation = 1 ;
					lightDirection = normalize(_WorldSpaceLightPos0.xyz);
				}
				else
				{
					float3 vertexToLightSource  = normalize(_WorldSpaceLightPos0.xyz - mul(_Object2World,input.pos).xyz);
					float distance = length(vertexToLightSource);
					attenuation = _Attenuation / distance;
					lightDirection = normalize(vertexToLightSource);
				}
				
				float3 ambientLighting = UNITY_LIGHTMODEL_AMBIENT.rgb * _Color.rgb;
				float3 diffuseReflection = attenuation * _LightColor0.rgb * _Color.rgb * max(0,dot(normalDirection,lightDirection)) ;
				
				float3 specularReflection ;
				if(dot(normalDirection, lightDirection) < 0.0)
				{
					specularReflection = float3(0.0, 0.0, 0.0); 
				}
				else
				{
					specularReflection = attenuation * _LightColor0.rgb * _SpecColor.rgb * pow(max(0,dot(viewDirection,reflect(-lightDirection, normalDirection))),_Shineness);
				}
				
				o.col = float4(ambientLighting + diffuseReflection + specularReflection, 1.0);
				o.pos = mul(UNITY_MATRIX_MVP,input.pos);
				return o;
			}
			
			float4 frag(vertexOutput input):COLOR
			{
				//input.col.w = _Transparency;
				return input.col;
			}
			ENDCG
			
		}
		
		
		Pass
		{
			Tags {"LightMode" = "ForwardAdd"}
			
			Blend One One
			CGPROGRAM
			
			#include "UnityCG.cginc"
			#pragma vertex vert
			#pragma fragment frag
			
			uniform float4 _LightColor0;
			float4 _Color;
			float4 _SpecColor; 
			float _Shineness;
			float _Attenuation;
			
			struct vertexInput
			{
				float4 pos:POSITION;
				float3 normal:NORMAL;
			};
			
			struct vertexOutput
			{
				float4 pos:SV_POSITION;
				float4 col:COLOR;
			};
			
			
			vertexOutput vert(vertexInput input)
			{
				vertexOutput o ;
				float3 viewDirection = normalize(_WorldSpaceCameraPos - mul(_Object2World,input.pos).xyz);
				float3 normalDirection = normalize(mul(_Object2World,float4(input.normal,0)).xyz);
				
				float3 lightDirection ;
				float attenuation;
				
				if(_WorldSpaceLightPos0.w == 0)
				{
					attenuation = 1 ;
					lightDirection = normalize(_WorldSpaceLightPos0.xyz);
				}
				else
				{
					float3 vertexToLightSource  = normalize(_WorldSpaceLightPos0.xyz - mul(_Object2World,input.pos).xyz);
					float distance = length(vertexToLightSource);
					attenuation = _Attenuation / distance;
					lightDirection = normalize(vertexToLightSource);
				}
				
				float3 ambientLighting = UNITY_LIGHTMODEL_AMBIENT.rgb * _Color.rgb;
				float3 diffuseReflection = attenuation * _LightColor0.rgb * _Color.rgb * max(0,dot(normalDirection,lightDirection)) ;
				
				float3 specularReflection ;
				if(dot(normalDirection, lightDirection) < 0.0)
				{
					specularReflection = float3(0.0, 0.0, 0.0); 
				}
				else
				{
					specularReflection = attenuation * _LightColor0.rgb * _SpecColor.rgb * pow(max(0,dot(viewDirection,reflect(-lightDirection, normalDirection))),_Shineness);
				}
				
				o.col = float4(ambientLighting + diffuseReflection + specularReflection, 1.0);
				o.pos = mul(UNITY_MATRIX_MVP,input.pos);
				return o;
			}
			
			float4 frag(vertexOutput input):COLOR
			{
				//input.col.w = _Transparency;
				return input.col;
			}
			ENDCG
			
		}
	} 
	FallBack "Diffuse"
}
