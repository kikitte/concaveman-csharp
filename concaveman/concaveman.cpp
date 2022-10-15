//
// Author: Stanislaw Adaszewski, 2019
//
#include "concaveman.h"

extern "C" {
	__declspec(dllexport)	int __cdecl pyconcaveman2d(double *points_c, int num_points,
		int *hull_points_c, int num_hull_points,
		double concavity, double lengthThreshold,
		double *concave_points_c);
}

__declspec(dllexport) int __cdecl pyconcaveman2d(double *points_c, int num_points,
    int *hull_points_c, int num_hull_points,
    double concavity, double lengthThreshold,
    double *concave_points_c) {

    typedef double T;
    typedef std::array<T, 2> point_type;

    std::vector<point_type> points(num_points);
    for (auto i = 0; i < num_points; i++) {
        points[i] = { points_c[i << 1], points_c[(i << 1) + 1] };
    }

    std::vector<int> hull(num_hull_points);
    for (auto i = 0; i < num_hull_points; i++) {
        hull[i] = hull_points_c[i];
    }

    auto concave_points = concaveman<T, 16>(points, hull, concavity, lengthThreshold);

    for (auto i = 0; i < concave_points.size(); i++) {
        concave_points_c[i << 1] = concave_points[i][0];
        concave_points_c[(i << 1) + 1] = concave_points[i][1];
    }

    return static_cast<int>(concave_points.size());
}
