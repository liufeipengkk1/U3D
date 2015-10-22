Shader "Custom/BasicTexture" {
	Properties {
		_MainTex ("Main Texture", 2D) = "white" {}
	}
	SubShader {
	
		Tags { "RenderType"="Opaque" }
		Pass
		{
			CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag
			
			sampler2D _MainTex;
			uniform float4 _MainTex_ST ;
			struct vertexInput
			{
				float4 pos:POSITION;
				float4 tex:TEXCOORD0;
			};
			
			struct vertexOutput
			{
				float4 pos:SV_POSITION;
				float4 tex:TEXCOORD0;
			};
			
			
			vertexOutput vert(vertexInput input)
			{
				vertexOutput output ;
				output.pos = mul(UNITY_MATRIX_MVP,input.pos);
				output.tex = input.tex;
				return output;
			}
			
			
			float4 frag(vertexOutput input):COLOR
			{
				return tex2D(_MainTex,input.tex.xy * _MainTex_ST.xy + _MainTex_ST.wz);
			}
			
			ENDCG
		}
	} 
	FallBack "Diffuse"
}
