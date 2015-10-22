Shader "Custom/lightingTexture" {
	Properties {
		_MainTex("Main Texture",2D) = "white"{}
		_Color ("Color", Color) = (1,1,1,1)
		_SpecColor ("Specular Material Color", Color) = (1,1,1,1) 
		_Transparency("transparecy",Range(0,1)) = 1
		_Attenuation("attenuation ",Range(0,1)) = 1
		_Shineness("Shineness",Range(1,20)) = 10
	}
	SubShader {
		Tags { "Queue" = "Transparent"} 
		Pass
		{
			Tags{"LightMode" = "ForwardBase"}
				
			ZWrite Off
			Blend SrcAlpha OneMinusSrcAlpha 
			
			
			CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag
			
			#include "UnityCG.cginc"
			
			uniform float4 _LightColor0;
			
			sampler2D _MainTex ;
			uniform float4 _MainTex_ST ;
			
			uniform float4 _Color;
			float _Transparency;
			float _Attenuation;
			float4 _SpecColor; 
			float _Shineness;
			
			struct vertexInput
			{
				float4 pos:POSITION;
				float3 normal:NORMAL;
				float4 tex:TEXCOORD0;
			};
			
			
			struct vertexOutput
			{
				float4 pos:SV_POSITION;
				float4 tex:TEXCOORD0;
				float4 posWorld : TEXCOORD1;
				float3 normalDir : TEXCOORD2;
			};
			
			
			vertexOutput vert(vertexInput input)
			{
				vertexOutput o ;
				o.pos = mul(UNITY_MATRIX_MVP,input.pos);
				o.tex = input.tex;
				o.posWorld = mul(_Object2World,input.pos);
				o.normalDir = normalize(mul(_Object2World,float4(input.normal,0)).xyz);
				return o;
			}
			
			float4 frag(vertexOutput input):COLOR
			{
			
				float3 viewDirection = normalize(_WorldSpaceCameraPos - input.posWorld.xyz);
				float3 normalDirection = normalize(input.normalDir.xyz);
				
				float3 lightDirection ;
				float attenuation;
				if(_WorldSpaceLightPos0.w == 0)
				{
					attenuation = 1 ;
					lightDirection = normalize(_WorldSpaceLightPos0.xyz);
				}
				else
				{
					float3 vertexToLightSource  = normalize(_WorldSpaceLightPos0.xyz - input.posWorld.xyz);
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
				
				float4 c = tex2D(_MainTex,input.tex.xy*_MainTex_ST.xy + _MainTex_ST.wz);
				float4 diffuseCol = float4(ambientLighting + diffuseReflection,1);
				float4 specularCol = float4(specularReflection,1);
				float4 finalCol = diffuseCol* c + specularCol;
				finalCol.w = _Transparency;
				return finalCol;
			}
			
			ENDCG
		}
		
		// for additional light
		Pass
		{
			Tags{"LightMode" = "ForwardAdd"}
				
			ZWrite Off
			Blend SrcAlpha OneMinusSrcAlpha 
			
			
			CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag
			
			#include "UnityCG.cginc"
			
			uniform float4 _LightColor0;
			
			sampler2D _MainTex ;
			uniform float4 _Color;
			float _Transparency;
			float _Attenuation;
			float4 _SpecColor; 
			float _Shineness;
			
			uniform float4 _MainTex_ST ;
			
			struct vertexInput
			{
				float4 pos:POSITION;
				float3 normal:NORMAL;
				float4 tex:TEXCOORD0;
			};
			
			
			struct vertexOutput
			{
				float4 pos:SV_POSITION;
				float4 tex:TEXCOORD0;
				float4 posWorld : TEXCOORD1;
				float3 normalDir : TEXCOORD2;
			};
			
			
			vertexOutput vert(vertexInput input)
			{
				vertexOutput o ;
				o.pos = mul(UNITY_MATRIX_MVP,input.pos);
				o.tex = input.tex;
				o.posWorld = mul(_Object2World,input.pos);
				o.normalDir = normalize(mul(_Object2World,float4(input.normal,0)).xyz);
				return o;
				
			}
			
			float4 frag(vertexOutput input):COLOR
			{
				float3 viewDirection = normalize(_WorldSpaceCameraPos - input.posWorld.xyz);
				float3 normalDirection = normalize(input.normalDir.xyz);
				
				float3 lightDirection ;
				float attenuation;
				if(_WorldSpaceLightPos0.w == 0)
				{
					attenuation = 1 ;
					lightDirection = normalize(_WorldSpaceLightPos0.xyz);
				}
				else
				{
					float3 vertexToLightSource  = normalize(_WorldSpaceLightPos0.xyz - input.posWorld.xyz);
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
				
				float4 c = tex2D(_MainTex,input.tex.xy*_MainTex_ST.xy + _MainTex_ST.wz);
				float4 diffuseCol = float4(ambientLighting + diffuseReflection,1);
				float4 specularCol = float4(specularReflection,1);
				float4 finalCol = diffuseCol* c + specularCol;
				finalCol.w = _Transparency;
				return finalCol;
			}
			
			ENDCG
		}
	} 
	FallBack "Diffuse"
}
