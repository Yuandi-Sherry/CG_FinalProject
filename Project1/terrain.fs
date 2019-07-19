#version 330 core

uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform vec3 lightColor;
uniform float p;
uniform float time;

uniform int N; //size of the grid

// First texture. Defined by glActiveTexture and passed by glUniform1i.
uniform sampler2D heightMapTex;

// Environmental textures.
uniform sampler2D sandTex;
uniform sampler2D treeTex;
uniform sampler2D stoneTex;


uniform sampler2D shadowMapTex;
//uniform sampler2DShadow shadowMap;
in vec4 ShadowCoord;


// Position (world coordinates) after heightmap displacement.
in vec3 displaced;
// Position (camera coordinates) after heightmap displacement.
in vec3 displaced_mv;


//light direction
in vec3 light_dir;
//view direction
in vec3 view_dir;

// First output buffer is pixel color.
// gl_FragColor
layout(location = 0) out vec3 color;

void main() {

	// Different levels of height for texture mapping
    const float sandMax = 0.02f;
	const float stoneMin = 0.035f;
	const float grassMin = 0.04f;
	const float grassMax = 0.2f;
    const float forestMin = 0.35f;

    float grid_size = 2.0/float(N);
    float tex_size = grid_size/2.0;
    ivec3 off = ivec3(-1, 0, 1);
    vec2 size = vec2(2.0/1024.0, 0.0);   //1024 is the size of the generated height map

    //current UV coordinate
    vec2 UV = vec2((displaced.xy +1.0)/2.0);
	color = (displaced.z > 0.008) ? vec3(0.0, 1.0, 0.0) : vec3(1.0, 0.0, 0.0) ; // ȫ�� > -0.01, <0.008
	//if it is water region, use normal from normal map 
	//otherwise need to calculate it 
	vec3 normal;
	//first calculate the normal vector using finite difference
	float s11 = texture(heightMapTex, UV).r;
	float s01 = textureOffset(heightMapTex, UV, off.xy).r;
	float s21 = textureOffset(heightMapTex, UV, off.zy).r;
	float s10 = textureOffset(heightMapTex, UV, off.yx).r;
	float s12 = textureOffset(heightMapTex, UV, off.yz).r;

	vec3 va = normalize(vec3(size.xy, s21 - s01));
	vec3 vb = normalize(vec3(0.0, size.x,  s12 - s10));
	vec3 tmp = cross(va,vb);
	normal = normalize(vec3(tmp.xy, 2*tmp.z));

    // Normalize the vectors.
    vec3 L = normalize(light_dir);
    vec3 V = normalize(view_dir);

	// Compute the ambient color component.
	vec3 ambient = Ia * ka * lightColor;
    // Compute the diffuse color component.
    vec3 diffuse = Id * kd * max(dot(normal,L),0.0);
    // Compute the specular color component
    vec3 specular = Is * ks * pow(max(dot(V,reflect(L,normal)),0.0),p) * lightColor;

    // Color dependent on the elevation (similar to texture mapping).
    vec3 mapped;

    float slope = smoothstep(0.35, 0.65 , normal.z);

    if(displaced.z < stoneMin) {
		vec3 stone = texture2D(stoneTex, 10*displaced.xy).rgb;
        vec3 sand = texture2D(sandTex, 30*displaced.xy).rgb;
        mapped = mix(stone, sand, slope);    
	} else if(displaced.z < grassMin) {  //mix between sand, rock
        vec3 forest = texture2D(treeTex, 10*displaced.xy).rgb;
        vec3 sand = texture2D(sandTex, 30*displaced.xy).rgb;
        mapped = mix(forest, sand, slope);          
		// color = vec3(0,1,0);
    } else {  //mix between forest and rock
        vec3 stone = texture2D(stoneTex, 10*displaced.xy).rgb;
        vec3 forest = texture2D(treeTex, 10*displaced.xy).rgb;
        mapped = mix(stone, forest, slope);
    } 
    // Assemble the colors.
    color = (ambient + diffuse + specular)*mapped;
    vec3 light = vec3(0.8);

    float bias = 0.005;  // 0.001
    ///>>>>>>>>>> TODO >>>>>>>>>>>
    /// TODO: Practical 6.
    /// 2) query the visibility of ShadowCoord in shadowMap, bias the query by subtracting bias. What happens without bias?
    /// Hint: Divide the ShadowCoord by its w-component before using it as a 3d point.
    /// Ressources: https://www.opengl.org/wiki/Sampler_(GLSL)#Shadow_samplers
    ///<<<<<<<<<< TODO <<<<<<<<<<<
    float visibility = 1.0;
}
