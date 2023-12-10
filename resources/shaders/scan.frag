#version 330

in vec2 fragTexCoord;
in vec4 fragColor;
uniform float resize;
uniform float resolution;
out vec4 colorOut;

vec2 size = vec2(resolution, resolution);
const float samples = 9.0;
const float quality = 8;

uniform sampler2D texture0;
uniform vec4 colDiffuse;

void main()
{
    // scanlines
    vec4 originalColor = texture(texture0, fragTexCoord) * fragColor;
    float y = floor(fragTexCoord.y * size.y);
    if (mod(y, 4) == 3) originalColor /= resize;

    // Bloom effect
    vec4 sum = vec4(0);
    vec2 sizeFactor = vec2(1) / size * quality;
    const int range = 2;
    for (int x = -range; x <= range; x++)
    {
        for (int y = -range; y <= range; y++)
        {
            sum += texture(texture0, fragTexCoord + vec2(x, y) * sizeFactor);
        }
    }

    // Simulate color bleeding
    float bleedingIntensity = 0.1;
    vec2 bleedingCoord = fragTexCoord + vec2(5.0, 0.0);
    vec2 bleedingCoordNorm = bleedingCoord / size;
    vec3 bleedColor = texture(texture0, bleedingCoordNorm).rgb * bleedingIntensity;

    colorOut = ((sum / (samples * samples)) + originalColor + vec4(bleedColor, 0.0)) * colDiffuse - vec4(0, 0, 0, 0.54);
}
