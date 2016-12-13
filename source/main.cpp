/*
Title: Matrix Mathematics
File Name: main.cpp
Copyright © 2016
Author: Andrew Litfin
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// The primary objects of study in linear algebra are matrices.
// This tutorial series will explore the applications of matrices to computer games and simulation,
//  especially in the realm of physical transformations.
// The exposition follows that of Eric Lengyel in "Foundations of Game Engine Development" (Volume 1).
// We have included the Vector structs from the previous series, and introduced Matrix structs that act similarly.
// These structs are based upon and largely follow code samples given in FGED.
//  As before, Matrix2D is heavily annotated, with other structs being annotated in places of difference.

// This tutorial gives special consideration to scaling matrices.

#include "../header/Matrix4D.h"
#include "../header/tests.h"
#include "../header/helpers.h"

#include <iostream>
#include <ctime>

int main()
{
	// Required for some helper functions
	srand((unsigned)time(0));

	// We've already seen one kind of scaling that applies to vectors and matrices, namely that of the uniform scale:
	//  where an element of the underlying field is multiplied into every element.
	// This can be represented as a uniform diagonal matrix, e.g.
	Matrix2D ScaleBy2(2, 0, 0, 2);

	// However, this will have the same effect on vectors and matrices as
	//  just multiplying by a scalar.
	// For example:

	Matrix2D testm(randIntF(-10, 10), randIntF(-10, 10), randIntF(-10, 10), randIntF(-10, 10));
	Vector2D testv(randIntF(-10, 10), randIntF(-10, 10));

	std::cout << "testm =\n" << testm
		<< "ScaleBy2 * testm =\n" << ScaleBy2 * testm
		<< "2 * testm =\n" << 2 * testm
		<< "testv = " << testv << "\n"
		<< "ScaleBy2 * testv = " << ScaleBy2 * testv << "\n"
		<< "2 * testv = " << 2 * testv << "\n";

	// What if instead we want to only scale along one axis?

	// This can be done with matrices, and is called a non-uniform scaling.
	// Say I want to scale along just the x-axis by 2:
	Matrix2D ScaleXby2 = Scale(2, 1);
	std::cout << "ScaleXby2 =\n" << ScaleXby2
		<< "ScaleXby2 * testm =\n" << ScaleXby2 * testm
		<< "ScaleXby2 * testv = " << ScaleXby2 * testv << "\n";

	// We can even mix multiple non-uniform scales into one matrix:
	Matrix3D CrazyScale = Scale(2, -3, 4);

	Matrix3D test3m(randIntF(-10, 10), randIntF(-10, 10), randIntF(-10, 10),
		randIntF(-10, 10), randIntF(-10, 10), randIntF(-10, 10),
		randIntF(-10, 10), randIntF(-10, 10), randIntF(-10, 10));

	Vector3D test3v(randIntF(-10, 10), randIntF(-10, 10), randIntF(-10, 10));

	std::cout << "test3m =\n" << test3m
		<< "CrazyScale * test3m =\n" << CrazyScale * test3m
		<< "test3v = " << test3v << "\n"
		<< "CrazyScale * test3v = " << CrazyScale * test3v << "\n";

	// Alternatively, non-uniform scaling can be realized as a specific case of the Hadamard product.
	// (See [the wikipedia article](<https://en.wikipedia.org/wiki/Hadamard_product_(matrices)>) for more.)

	Vector3D CrazyScaleV(2, -3, 4);
	std::cout << "CrazyScaleV * test3v = " << CrazyScaleV * test3v << "\n";


	// We can even scale along an arbitrary axis not aligned with any basis vector!

	// Consider the resulting vector after a scaling along an arbitrary axis.
	// Let the initial vector be v, the vector we want to scale along be a, the result be v', and the scale factor be s.
	// Then v' = s*Project(v, a) + Reject(v, a)
	// That is, the part of v orthogonal to a should remain unchanged, and the projection of v onto a should be stretched by the scale factor.
	// For example,

	Vector2D v(1, 0);
	Vector2D a(1, 1);
	float s = 2;

	// Then

	std::cout << "Scale(s, a) * v = " << Scale(s, a) * v << "\n";

	std::cout << "\nPress Enter to exit . . . ";
	std::cin.get();
	return 0;
}
