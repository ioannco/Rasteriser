#ifndef MATRIX3HPP
#define MATRIX3HPP

#include "geometry.hpp"
#include "sse_vector4f.hpp"

template<class T, int sizeX, int sizeY>
struct matrix {
	T *operator[](int i)
	{
		return data[i];
	}

	const T *operator[](int i) const
	{
		return data[i];
	}

	void fill(T d)
	{
		for (auto y = 0u; y < sizeY; y++)
			for (auto x = 0u; y < sizeX; x++)
				data[y][x] = d;
	}

	T data[sizeY][sizeX];
};

typedef matrix<float, 3, 3> mat3f;

vector3f normalize(const vector3f &v)
{
    sse_vector4f sv(v.x, v.y, v.z, 0);
    sv = sv.norm ();

    return vector3f{sv.x, sv.y, sv.z};

}

vector3f operator*(const mat3f &m, const vector3f &v)
{
	vector3f out = {0.f, 0.f, 0.f};
	for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
			out[i] += m[i][j] * v[j];

	return out;
}

mat3f rotate(const vector3f &dir, const vector3f &_up)
{
	vector3f right = normalize(cross(_up, dir));
	vector3f up = cross(dir, right);
	return mat3f{
	right.x, right.y, right.z,
	up.x, up.y, up.z,
	dir.x, dir.y, dir.z};
}

#endif //MATRIXHPP
