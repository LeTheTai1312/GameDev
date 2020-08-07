//precision mediump float;
//uniform samplerCube u_samplerCubeMap;
//varying vec4 v_pos;

//void main(void)
//{
//	gl_FragColor = textureCube(u_samplerCubeMap, v_pos.xyz);
//}

precision mediump float;
varying vec4 v_color;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;
varying vec2 v_uv;

void main()
{
	gl_FragColor = texture2D(u_texture0, v_uv)*texture2D(u_texture1, v_uv);
}