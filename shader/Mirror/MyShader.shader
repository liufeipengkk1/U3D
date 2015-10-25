Shader "Cunstom/MyMirror" {
	Properties {
		_RefTex ("Reflection Tex", 2D) = "white" {}
		_BumpMap("Normal Map",2D) = "bump"{}
		_Transparency("transparency",Range(0,1)) = 1 
		_Color("color",COLOR) = (1,1,1,1)
		_Amplitude("amplitude",Range(-1,1)) = 0.5
		_waveSpeed("wave speed",Range(0.1,80)) = 5
		_Frequency("frequency",Range(0,5)) = 2
		_SpecColor ("Specular Material Color", Color) = (1,1,1,1) 
		_Shineness("Shineness",Float) = 10
		
	}
	SubShader {

		Tags{ "Queue" = "Transparent"}

		pass{
			Tags {"LightMode"="ForwardBase"}

			ZWrite Off
			Blend SrcAlpha OneMinusSrcAlpha

			CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag
		
			#include "UnityCG.cginc"

			uniform sampler2D _BumpMap ;
			uniform float4 _BumpMap_ST;
			sampler2D _RefTex;
			float _Transparency;
			float4x4 _ProjMat;
			float4 _Color;
			float _Amplitude;
			float _waveSpeed;
			float _Frequency ;
		
			uniform float4 _LightColor0;
			float4 _SpecColor; 
			float _Shineness;

			struct vertexInput
			{
				float4 pos:POSITION;
				float3 normal:NORMAL;
				float4 tangent:TANGENT;
			};
			
			struct vertexOutput
			{
				float4 pos:SV_POSITION;
				float4 texc:TEXCOORD0;
				float4 posWorld : TEXCOORD1;
				float3 tangentWorld:TEXCOORD2;
				float3 normalWorld:TEXCOORD3;
				float3 binormalWorld:TEXCOORD4;
			};
			
			vertexOutput vert(vertexInput input)
			{
				vertexOutput output;
				float time = _Time * _waveSpeed;
				float waveValue = sin(time + input.pos.x * _Frequency) * _Amplitude;
				input.pos.xyz = float3(input.pos.x,input.pos.y + waveValue,input.pos.z);
				//input.normal = normalize(float3(input.pos.x,input.pos.y + waveValue,input.pos.z));

				float4x4 proj;
				proj=mul(_ProjMat,_Object2World);
				
				output.pos=mul(UNITY_MATRIX_MVP,input.pos);
				output.posWorld = mul(_Object2World,input.pos);
				
				output.tangentWorld = normalize(
						mul(_Object2World,float4(input.tangent.xyz,0)).xyz
					);
				output.normalWorld = normalize(mul(_Object2World,float4(input.normal,0)).xyz);
				// w 用来指定正负
				output.binormalWorld = (cross(output.normalWorld, output.tangentWorld) * input.tangent.w);
				
				output.texc=mul(proj,input.pos);
				return output;
			}
		
			float4 frag(vertexOutput input):COLOR
			{
		
				float3 viewDirection = normalize(_WorldSpaceCameraPos - input.posWorld.xyz);
				float4 encodedNormal = tex2D(_BumpMap,_BumpMap_ST.xy * input.texc.xy + _BumpMap_ST.zw);
				float3 localCoords = float3(2.0 * encodedNormal.a - 1.0, 2.0 * encodedNormal.g - 1.0, 0.0);
            	localCoords.z = sqrt(1.0 - dot(localCoords, localCoords));

            	 float3x3 local2WorldTranspose = float3x3(input.tangentWorld, input.binormalWorld, input.normalWorld);

           		 float3 normalDirection = normalize(mul(localCoords, local2WorldTranspose));
					
				float3 lightDirection ;
				float attenuation;
				if(_WorldSpaceLightPos0.w == 0)
				{
					attenuation = 1 ;
					lightDirection = normalize(_WorldSpaceLightPos0.xyz);
				}
				else
				{
					float3 vertexToLightSource  = normalize(_WorldSpaceLightPos0.xyz -  input.posWorld.xyz);
					float distance = length(vertexToLightSource);
					attenuation = 1 / distance;
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
			
				float4 c=tex2Dproj(_RefTex,input.texc);
				return float4((ambientLighting + diffuseReflection)*c + specularReflection, _Transparency);
			}
		
			ENDCG
		}
		
		pass{
			Tags {"LightMode"="ForwardAdd"}

			ZWrite Off
			Blend SrcAlpha OneMinusSrcAlpha

			CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag
		
			#include "UnityCG.cginc"

			uniform sampler2D _BumpMap ;
			uniform float4 _BumpMap_ST;
			sampler2D _RefTex;
			float _Transparency;
			float4x4 _ProjMat;
			float4 _Color;
			float _Amplitude;
			float _waveSpeed;
			float _Frequency ;
		
			uniform float4 _LightColor0;
			float4 _SpecColor; 
			float _Shineness;

			struct vertexInput
			{
				float4 pos:POSITION;
				float3 normal:NORMAL;
				float4 tangent:TANGENT;
			};
			
			struct vertexOutput
			{
				float4 pos:SV_POSITION;
				float4 texc:TEXCOORD0;
				float4 posWorld : TEXCOORD1;
				float3 tangentWorld:TEXCOORD2;
				float3 normalWorld:TEXCOORD3;
				float3 binormalWorld:TEXCOORD4;
			};
			
			vertexOutput vert(vertexInput input)
			{
				vertexOutput output;
				float time = _Time * _waveSpeed;
				float waveValue = sin(time + input.pos.x * _Frequency) * _Amplitude;
				input.pos.xyz = float3(input.pos.x,input.pos.y + waveValue,input.pos.z);
				//input.normal = normalize(float3(input.pos.x,input.pos.y + waveValue,input.pos.z));

				float4x4 proj;
				proj=mul(_ProjMat,_Object2World);
				
				output.pos=mul(UNITY_MATRIX_MVP,input.pos);
				output.posWorld = mul(_Object2World,input.pos);
				
				output.tangentWorld = normalize(
						mul(_Object2World,float4(input.tangent.xyz,0)).xyz
					);
				output.normalWorld = normalize(mul(_Object2World,float4(input.normal,0)).xyz);
				// w 用来指定正负
				output.binormalWorld = (cross(output.normalWorld, output.tangentWorld) * input.tangent.w);
				
				output.texc=mul(proj,input.pos);
				return output;
			}
		
			float4 frag(vertexOutput input):COLOR
			{
		
				float3 viewDirection = normalize(_WorldSpaceCameraPos - input.posWorld.xyz);
				float4 encodedNormal = tex2D(_BumpMap,_BumpMap_ST.xy * input.texc.xy + _BumpMap_ST.zw);
				float3 localCoords = float3(2.0 * encodedNormal.a - 1.0, 2.0 * encodedNormal.g - 1.0, 0.0);
            	localCoords.z = sqrt(1.0 - dot(localCoords, localCoords));

            	 float3x3 local2WorldTranspose = float3x3(input.tangentWorld, input.binormalWorld, input.normalWorld);

           		 float3 normalDirection = normalize(mul(localCoords, local2WorldTranspose));
					
				float3 lightDirection ;
				float attenuation;
				if(_WorldSpaceLightPos0.w == 0)
				{
					attenuation = 1 ;
					lightDirection = normalize(_WorldSpaceLightPos0.xyz);
				}
				else
				{
					float3 vertexToLightSource  = normalize(_WorldSpaceLightPos0.xyz -  input.posWorld.xyz);
					float distance = length(vertexToLightSource);
					attenuation = 1 / distance;
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
			
				float4 c=tex2Dproj(_RefTex,input.texc);
				return float4((ambientLighting + diffuseReflection)*c + specularReflection, _Transparency);
			}
		
			ENDCG
		}
	} 
}
