#version 330

varying vec2 v_texCoord;
varying vec3 v_normal;
varying vec3 v_color;

uniform sampler2D diffuse;

void main() {

    //vec3 ambient = vec3(0.0, 0.0, 0.0);
    float sDotN = clamp(dot(-vec3(0, 0, 1), v_normal) * 0.9, 0.0, 10.0);
    vec3 Ld = vec3(2.0, 2.0, 2.0);
    vec3 Kd = vec3(0.8, 0.8, 0.8);
    vec3 ldiffuse = Ld * sDotN * Kd;

    vec3 La = vec3(0.2, 0.2, 0.2);


    /*gl_FragColor = texture2D(diffuse, v_texCoord) * vec4(v_color, 1.0)
        * clamp(dot(-vec3(0, 0, 1), v_normal) * 0.9, 0.0, 10.0);*/

    gl_FragColor = texture2D(diffuse, v_texCoord) * vec4(ldiffuse + La, 1.0);
    //gl_FragColor = texture2D(diffuse, v_texCoord) * vec4(v_color, 1.0) * vec4(0.4, 0.4, 0.4, 1.0);

}