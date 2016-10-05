

#define snoise(p) (2 * (float noise(p)) - 1)

float RidgedMultifractal(point p; uniform float octaves, lacunarity, gain, H, sharpness, threshold)
{
	float result, signal, weight, i, exponent;
	varying point PP=p;

	for( i=0; i<octaves; i += 1 ) {
       	if ( i == 0) {
          		signal = snoise( PP );
          		if ( signal < 0.0 ) signal = -signal;
          		signal = gain - signal;
          		signal = pow( signal, sharpness );
          		result = signal;
          		weight = 1.0;
        	}else{
          		exponent = pow( lacunarity, (-i*H) );
			PP = PP * lacunarity;
          		weight = signal * threshold;
          		weight = clamp(weight,0,1)    ;    		
          		signal = snoise( PP );
          		signal = abs(signal);
          		signal = gain - signal;
          		signal = pow( signal, sharpness );
          		signal *= weight;
          		result += signal * exponent;
       		}
		}
		return(result);
}

float fBm (point p; uniform float octaves, lacunarity, gain)
{
  uniform float amp = 1;
  varying point pp = p;
  varying float sum = 0;
  uniform float i;
  
  for (i = 0;  i < octaves;  i += 1) {
    sum += amp * snoise (pp);
    amp *= gain;
    pp *= lacunarity;
  }
  return sum;
}

surface mountain (float Ka = 0, Kd = 1.0;
color white = color(1.0, 1.0, 1.0);
color red = color(1.0, 0.0, 0.0);
color grey = color(0.3, 0.3, 0.3);
//Bump-mapping
float frequency = 0.3;
float bumpDepth = 2.0;
float roughness = 0.1;
//fBm
float octaves = 3.0;
float lacunarity = 1.5;
float gain = 0.8;
//Mountain fractal
float mOctaves = 4.0;
float mLacunarity = 2.0;
float mGain = 0.9;
float mH = 1.0;
float mSharpness = 7.0;
float mThreshold = 5.0;
)
{
    float magnitude = (RidgedMultifractal((P+10)*0.01, mOctaves, mLacunarity, 
	mGain, mH, mSharpness, mThreshold)*60.0001);
	float mountainAtt=distance(zcomp(P),50.0)/1000.0;
		
    P += magnitude*mountainAtt*normalize(N);
    N = calculatenormal(P);
    normal Nf = faceforward (normalize(N),I);
	
	point PP = point(u, v, 0.0);
	float fb = fBm(PP, octaves, lacunarity, gain);
	
	//Snow on mountains
	float snowsel = ycomp(normalize(N));
	snowsel = smoothstep(0.1, 0.8, snowsel);
	color mountainColor = mix(white, grey, snowsel);
	mountainColor = mountainColor * fb;
	
	color Diffuse=Cs*(Kd * diffuse(Nf));
	
	//Bump-mapping
	point PP2 = P;
	PP2 += noise(P * frequency) * N * bumpDepth;
	N = calculatenormal(PP2);
	normal Nn = normalize(N);
	vector V = normalize(-I);
	color diffColor = (0.2, 0.2, 0.2);
	color specColor = (0.2, 0.2, 0.2);
	color dColor = diffColor * diffuse(Nn);
	color sColor = specColor * specular(Nn, V, roughness);
	color bumpColor = dColor + sColor;
	
	//Rivers/lakes
	color c1 = red * u / magnitude * 3;
	color c2 = color(1.0, 0.6, 0.0) * u / magnitude * 4;
	color c3 = c1 + c2;
	c3 = clamp(c3, 0, 1);
	c3 = c3 + bumpColor;
	
	//Mist/fog
	float d = 1 - exp(-length(I) / mountainAtt);
	color mistColor = color(0.6, 0.3, 0.2) / d;
	
	color finalColor = Diffuse * mountainColor + c3;
	
    Ci = finalColor;
	Ci = mix(Ci, mistColor, mountainAtt);
    Oi = Os;      
}
