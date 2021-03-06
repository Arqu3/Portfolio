﻿Shader "Unlit/Texture"
{
	Properties
	{
		_Color("Main Color", Color) = (1, 1, 1, 0.5)
		_MainTex("Texture", 2D) = "white" { }
	}

	SubShader
	{
		Pass
		{
			CGPROGRAM
			//Compilation directives/instructions for this snippet
			#pragma vertex vert
			#pragma fragment frag
			#include "UnityCG.cginc"

			fixed4 _Color;
			sampler2D _MainTex;

			struct v2f
			{
				float4 pos : SV_POSITION;
				float2 uv : TEXCOORD0;
			};

			float4 _MainTex_ST;

			//VERTEX PROGRAM - applies texture scale and offset properly
			v2f vert(appdata_base v)
			{
				v2f o;
				o.pos = mul(UNITY_MATRIX_MVP, v.vertex);
				o.uv = TRANSFORM_TEX(v.texcoord, _MainTex);
				return o;
			}

			//FRAGMENT PROGRAM - samples the texture and multiplies it with the color
			fixed4 frag(v2f i) : SV_Target
			{
				fixed4 texcol = tex2D(_MainTex, i.uv);
				return texcol * _Color;
			}

			ENDCG
		}
	}
}
