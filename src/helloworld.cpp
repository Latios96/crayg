#include<iostream>
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "bitmap_image.hpp"

class Vector3f {
public:
	float x, y, z;
	
	/**
	Creates a new Vector and initialised x,y,z to 0
	*/
	Vector3f() {
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3f(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
	}
	// TODO use operator overloading
	Vector3f add(const Vector3f &otherVector) {
		return Vector3f(x + otherVector.x, y + otherVector.y, z + otherVector.z);
	}

	Vector3f substract(const Vector3f &otherVector) {
		return Vector3f(x - otherVector.x, y - otherVector.y, z - otherVector.z);
	}

	Vector3f multiplyScalar(float scalar) {
		return Vector3f(x*scalar, y*scalar, z*scalar);
	}

	float length() {
		return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
	}

	Vector3f normalize() {
		float length = this->length();
		// TODO optimize with computing 1/length and multiply with vector components
		return Vector3f(x / length, y / length, z / length);
	}

	Vector3f invert() {
		return Vector3f(x*-1, y*-1, z*-1);
	}

	Vector3f crossProduct(const Vector3f &otherVector) {
		return Vector3f(y * otherVector.z - otherVector.y * z,
			z * otherVector.x - otherVector.z * x,
			x * otherVector.y - otherVector.x * y);
	}
	
};

bool compareWithPrecision(float A, float B, float epsilon = 0.001f)
{
	return (fabs(A - B) < epsilon);
}

TEST_CASE("Vector3f Addition") {
	Vector3f myVector(1,1,1);
	Vector3f otherVector(1,2,3);
	Vector3f result = myVector.add(otherVector);

	REQUIRE(result.x == 2);
	REQUIRE(result.y == 3);
	REQUIRE(result.z == 4);
}

TEST_CASE("Vector3f Subtraction") {
	Vector3f myVector(1, 1, 1);
	Vector3f otherVector(1, 2, 3);
	Vector3f result = myVector.substract(otherVector);

	REQUIRE(result.x == 0);
	REQUIRE(result.y == -1);
	REQUIRE(result.z == -2);
}

TEST_CASE("Vector3f length") {
	Vector3f myVector(-5, -6, -8);
	REQUIRE(compareWithPrecision(myVector.length(), 11.18033f));
}

TEST_CASE("Vector3f multiplyScalar") {
	Vector3f myVector(5, 6, 8);
	Vector3f result = myVector.multiplyScalar(5);
	REQUIRE(result.x == 25);
	REQUIRE(result.y == 30);
	REQUIRE(result.z == 40);
}

TEST_CASE("Vector3f normalize") {
	Vector3f myVector(5, 6, 8);
	Vector3f result = myVector.normalize();
	REQUIRE(compareWithPrecision(result.x, 0.44721f));
	REQUIRE(compareWithPrecision(result.y, 0.5366f));
	REQUIRE(compareWithPrecision(result.z, 0.71554f));
}

TEST_CASE("Vector3f invert") {
	Vector3f myVector(5, 6, 8);
	Vector3f result = myVector.invert();
	REQUIRE(result.x == myVector.x*-1);
	REQUIRE(result.y == myVector.y*-1);
	REQUIRE(result.z == myVector.z*-1);
}

TEST_CASE("Vector3f crossProduct") {
	Vector3f myVector(1,2,3);
	Vector3f otherVector(1, 5, 7);
	Vector3f result = myVector.crossProduct(otherVector);

	REQUIRE(result.x == -1);
	REQUIRE(result.y == -4);
	REQUIRE(result.z == 3);
}

class Image {
	int width, height;
	float *values;

	Image(int width, int height) {
		this->width = width;
		this->height = height;

		int size = width * height * 3;
		values = new float[size];
	}

	void setValue(int x, int y, const Vector3f &color) {
		values[x + y] = color.x;
		values[x + y+1] = color.y;
		values[x + y+2] = color.z;
	}

	~Image() {
		delete[] values;
	}

};

int main(int argc, char* argv[]) {
	// global setup...

	/*int result = Catch::Session().run(argc, argv);

	// global clean-up...
	system("PAUSE");
	return result;*/

	// https://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries
	const int w = 100; /* Put here what ever width you want */
	const int h = 100; /* Put here what ever height you want */
	int red[w][h];
	int green[w][h];
	int blue[w][h];


	FILE *f;
	unsigned char *img = NULL;
	int filesize = 54 + 3 * w*h;  //w is your image width, h is image height, both int
	if (img)
		free(img);
	img = (unsigned char *)malloc(3 * w*h);
	memset(img, 0, sizeof(img));
	int x;
	int y;
	int r;
	int g;
	int b;

	for (int i = 0; i<w; i++)
	{
		for (int j = 0; j<h; j++)
		{
			x = i; y = (h - 1) - j;
			r = red[i][j] * 255;
			g = green[i][j] * 255;
			b = blue[i][j] * 255;
			if (r > 255) r = 255;
			if (g > 255) g = 255;
			if (b > 255) b = 255;
			img[(x + y*w) * 3 + 2] = (unsigned char)(r);
			img[(x + y*w) * 3 + 1] = (unsigned char)(g);
			img[(x + y*w) * 3 + 0] = (unsigned char)(b);
		}
	}

	unsigned char bmpfileheader[14] = { 'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0 };
	unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0 };
	unsigned char bmppad[3] = { 0,0,0 };

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);
	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	f = fopen("img.bmp", "wb");
	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);
	for (int i = 0; i<h; i++)
	{
		fwrite(img + (w*(h - i - 1) * 3), 3, w, f);
		fwrite(bmppad, 1, (4 - (w * 3) % 4) % 4, f);
	}
	fclose(f);

	return 0;
}