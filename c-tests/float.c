int main(void) {

    float a = 1.0;
    float b = 1.0f;
    float c = 1.0F;
    float d = 1f;
    float e = 1e0;
    float f = 1e+1f;
    float g = 1e-1f;
    g *= 10.0;

	return a + b + c + d + e + f + g - 16;
}
