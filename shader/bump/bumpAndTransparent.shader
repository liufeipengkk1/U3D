Shader "Custom/bump" {
	Properties
	{
		_BumpMap("Normal Map",2D) = "bump"{}
		_MainTex("Main tex",2D) = "white"{}
		_Color("diffuse Material Color",Color) = (1,1,1,1)
		_SpecColor("Specular Material Color",Color) = (1,1,1,1)
		_Shininess("Shininess",Float) = 10
		_Transparency("transparecy",Range(0,1)) = 1
		
	}

	SubShader
	{
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

			uniform sampler2D _BumpMap ;
			uniform sampler2D _MainTex;
			uniform float4 _BumpMap_ST;
			uniform float4 _Color;
			uniform float4 _SpecColor;
			uniform float _Shininess;
			float _Transparency;

			struct vertexInput
			{
				float4 vertex:POSITION;
				float4 texcoord:TEXCOORD0;
				float3 normal:NORMAL;
				float4 tangent:TANGENT;
			};

			struct vertexOutput
			{
				float4 pos:SV_POSITION;
				float4 posWorld:TEXCOORD0;
				float4 tex:TEXCOORD1;
				float3 tangentWorld:TEXCOORD2;
				float3 normalWorld:TEXCOORD3;
				float3 binormalWorld:TEXCOORD4;
			};

			vertexOutput vert(vertexInput input)
			{
				vertexOutput output;

				output.pos = mul(UNITY_MATRIX_MVP,input.vertex);
				output.posWorld = mul(_Object2World,input.vertex);
				output.tex = input.texcoord;
				output.tangentWorld = normalize(
						mul(_Object2World,float4(input.tangent.xyz,0)).xyz
					);
				output.normalWorld = normalize(mul(_Object2World,float4(input.normal,0)).xyz);
				// w 用来指定正负
				output.binormalWorld = (cross(output.normalWorld, output.tangentWorld) * input.tangent.w);
				return output;
			}

			float4 frag(vertexOutput input) : COLOR
			{
				float4 encodedNormal = tex2D(_BumpMap,_BumpMap_ST.xy * input.tex.xy + _BumpMap_ST.zw);
				float3 localCoords = float3(2.0 * encodedNormal.a - 1.0, 2.0 * encodedNormal.g - 1.0, 0.0);
            	localCoords.z = sqrt(1.0 - dot(localCoords, localCoords));

            	 float3x3 local2WorldTranspose = float3x3(input.tangentWorld, input.binormalWorld, input.normalWorld);

           		 float3 normalDirection = normalize(mul(localCoords, local2WorldTranspose));

           		 float3 viewDirection =  normalize(_WorldSpaceCameraPos -input.posWorld.xyz);
           		 float3 lightDirection;
           		 float attenuation;
 
            	if (0.0 == _WorldSpaceLightPos0.w) // directional light?
            	{
               		attenuation = 1.0; // no attenuation
               		lightDirection = normalize(_WorldSpaceLightPos0.xyz);
            	} 
            	else // point or spot light
            	{
               		float3 vertexToLightSource = _WorldSpaceLightPos0.xyz - input.posWorld.xyz;
               		float distance = length(vertexToLightSource);
					attenuation = 1.0 / distance; // linear attenuation 
               		lightDirection = normalize(vertexToLightSource);
            	}
 
	            float3 ambientLighting = UNITY_LIGHTMODEL_AMBIENT.rgb * _Color.rgb;
 
            	float3 diffuseReflection = attenuation * _LightColor0.rgb * _Color.rgb* max(0.0, dot(normalDirection, lightDirection));
 
            	float3 specularReflection;
            	if (dot(normalDirection, lightDirection) < 0.0) // light source on the wrong side?
           		{
               		specularReflection = float3(0.0, 0.0, 0.0); 
                  	// no specular reflection
            	}
            	else // light source on the right side
            	{
               		specularReflection = attenuation * _LightColor0.rgb * _SpecColor.rgb * pow(max(0.0, dot(reflect(-lightDirection, normalDirection), viewDirection)), _Shininess);
               	}

               	float4 c = tex2D(_MainTex,input.tex.xy);
            	return float4((ambientLighting + diffuseReflection)*c + specularReflection, _Transparency);
			}
			ENDCG
		}
		
		
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

			uniform sampler2D _BumpMap ;
			uniform sampler2D _MainTex;
			uniform float4 _BumpMap_ST;
			uniform float4 _Color;
			uniform float4 _SpecColor;
			uniform float _Shininess;
			float _Transparency;

			struct vertexInput
			{
				float4 vertex:POSITION;
				float4 texcoord:TEXCOORD0;
				float3 normal:NORMAL;
				float4 tangent:TANGENT;
			};

			struct vertexOutput
			{
				float4 pos:SV_POSITION;
				float4 posWorld:TEXCOORD0;
				float4 tex:TEXCOORD1;
				float3 tangentWorld:TEXCOORD2;
				float3 normalWorld:TEXCOORD3;
				float3 binormalWorld:TEXCOORD4;
			};

			vertexOutput vert(vertexInput input)
			{
				vertexOutput output;

				output.pos = mul(UNITY_MATRIX_MVP,input.vertex);
				output.posWorld = mul(_Object2World,input.vertex);
				output.tex = input.texcoord;
				output.tangentWorld = normalize(
						mul(_Object2World,float4(input.tangent.xyz,0)).xyz
					);
				output.normalWorld = normalize(mul(_Object2World,float4(input.normal,0)).xyz);
				// w 用来指定正负
				output.binormalWorld = (cross(output.normalWorld, output.tangentWorld) * input.tangent.w);
				return output;
			}

			float4 frag(vertexOutput input) : COLOR
			{
				float4 encodedNormal = tex2D(_BumpMap,_BumpMap_ST.xy * input.tex.xy + _BumpMap_ST.zw);
				float3 localCoords = float3(2.0 * encodedNormal.a - 1.0, 2.0 * encodedNormal.g - 1.0, 0.0);
            	localCoords.z = sqrt(1.0 - dot(localCoords, localCoords));

            	 float3x3 local2WorldTranspose = float3x3(input.tangentWorld, input.binormalWorld, input.normalWorld);

           		 float3 normalDirection = normalize(mul(localCoords, local2WorldTranspose));

           		 float3 viewDirection =  normalize(_WorldSpaceCameraPos -input.posWorld.xyz);
           		 float3 lightDirection;
           		 float attenuation;
 
            	if (0.0 == _WorldSpaceLightPos0.w) // directional light?
            	{
               		attenuation = 1.0; // no attenuation
               		lightDirection = normalize(_WorldSpaceLightPos0.xyz);
            	} 
            	else // point or spot light
            	{
               		float3 vertexToLightSource = _WorldSpaceLightPos0.xyz - input.posWorld.xyz;
               		float distance = length(vertexToLightSource);
					attenuation = 1.0 / distance; // linear attenuation 
               		lightDirection = normalize(vertexToLightSource);
            	}
 
	            float3 ambientLighting = UNITY_LIGHTMODEL_AMBIENT.rgb * _Color.rgb;
 
            	float3 diffuseReflection = attenuation * _LightColor0.rgb * _Color.rgb* max(0.0, dot(normalDirection, lightDirection));
 
            	float3 specularReflection;
            	if (dot(normalDirection, lightDirection) < 0.0) // light source on the wrong side?
           		{
               		specularReflection = float3(0.0, 0.0, 0.0); 
                  	// no specular reflection
            	}
            	else // light source on the right side
            	{
               		specularReflection = attenuation * _LightColor0.rgb * _SpecColor.rgb * pow(max(0.0, dot(reflect(-lightDirection, normalDirection), viewDirection)), _Shininess);
               	}

               	float4 c = tex2D(_MainTex,input.tex.xy);
            	return float4((ambientLighting + diffuseReflection)*c + specularReflection, _Transparency);
			}
			ENDCG
		}
	}
}
