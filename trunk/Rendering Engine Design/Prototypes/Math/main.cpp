#include "ArgonVector2.h"
#include "ArgonVector3.h"
#include "ArgonMatrix4.h"

int main()
{
	Argon::Vector2<float> asd(27.054698798798645647f, -83.321546654321365462f);

	asd = asd.Normalise();
	float dummy = asd.Length();

	Argon::Vector3<float> asdf(27.054698798798645647f, -83.321546654321365462f, 27436.3287613245576f);

	asdf = asdf.Normalise();
	dummy = asdf.Length();
	
	asdf = asdf.Cross(Argon::Vector3<float>(asd.x, asd.y, 1));

	Argon::Matrix4<float> asdfg;
	asdfg = Argon::Matrix4<float>::Identity;
	asdfg.m[0][3] = 13246;
	asdfg.Transpose();

	return 0;
}