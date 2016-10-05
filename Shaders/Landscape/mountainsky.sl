void voronoi_f1f2_2d (float ss, tt; output float f1; output float spos1, tpos1; output float f2; output float spos2, tpos2;)
{
  float jitter=1.0;
  float sthiscell = floor(ss)+0.5;
  float tthiscell = floor(tt)+0.5;
  f1 = f2 = 1000;
  uniform float i, j;
  for (i = -1;  i <= 1;  i += 1) {
    float stestcell = sthiscell + i;
    for (j = -1;  j <= 1;  j += 1) {
      float ttestcell = tthiscell + j;
      float spos = stestcell + jitter * (cellnoise(stestcell, ttestcell) - 0.5);
      float tpos = ttestcell + jitter * (cellnoise(stestcell+23, ttestcell-87) - 0.5);
      float soffset = spos - ss;
      float toffset = tpos - tt;
      float dist = soffset*soffset + toffset*toffset;
      if (dist < f1) { 
        f2 = f1;
        spos2 = spos1;
        tpos2 = tpos1;
        f1 = dist;
        spos1 = spos;
        tpos1 = tpos;
      } else if (dist < f2) {
        f2 = dist;
        spos2 = spos;
        tpos2 = tpos;
      }
    }
  }
  f1 = sqrt(f1);  f2 = sqrt(f2);
}

#define snoise(p) (2 * (float noise(p)) - 1)

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

surface mountainsky(float frequency = 10.0f;
color white = (1.0, 1.0, 1.0);
color black = (0.0, 0.0, 0.0);
color cloudcolor1 = (0.5, 0.0, 0.5);
color cloudcolor2 = (0.2, 0.0, 1.0);
float Octaves = 4.0;
float Gain = 0.5;
float Lacunatiry = 2.0;)
{	
	//Sun
	point P1 = point(0.0, 0.0, 0.0);
	point P2 = point((u - 0.5) * 0.9, (v - 0.8) * 0.3, 0.0);
	point P3 = point(0.0, v, 0.0);
	
	float dist = distance(P1, P2) * 1.3;
	float dist2 = distance(P1, P3) * 1.8;
	dist = dist * dist2;
	dist = smoothstep(0.015, 0.3, dist);
	dist = clamp(dist, 0.01, 1.0);
	
	color sunColor = color(0.5, 0.2, 0.1) / dist;

	float fx = 0;
	float fy = 0;
	float fb1 = 0;
	float fb2 = 0;
	
	//Perspective
	float vc = (v+0.1) * 2.0;
	float uu = ((u - 0.5) * 1.0) / (1.0 - vc);
	float vv = ((vc - 0.6) / (1.0 - vc));
	
	point p = (uu, vv, 0);
	
	fb1 = fBm(p * (frequency / 2.0), Octaves, Lacunatiry, Gain);
	fb2 = fBm((p + 55.2351) * (frequency / 2.0), Octaves, Lacunatiry, Gain);
	
	fb1 = clamp(fb1, 0.0, 1.0);
	fb2 = clamp(fb2, 0.0, 1.0);
	
	color fbColor1 = cloudcolor1 * fb1;
	color fbColor2 = cloudcolor2 * fb2;
	
	voronoi_f1f2_2d(u * frequency, v * frequency, fx, 0, 0, fy, 0, 0);
	
	float f = fx / fy * 2;
	
	color mixColor = mix(fbColor1, fbColor2, f);
	
	f = smoothstep(0, 0.2, f);
	f += 0.01;
	color outcol = color(0.2, 0.1, 0.03)/f;
	color c = outcol;
	Ci = c + mixColor + sunColor;
	Oi = Os;
} 
