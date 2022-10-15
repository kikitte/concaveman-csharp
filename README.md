# concaveman

A C# concaveman wrapper to the [concaveman-cpp](https://github.com/sadaszewski/concaveman-cpp). We use the platform invocation mechanism to achieve the interoperability between C# and C++, you may refer this [guide](https://mark-borg.github.io/blog/2017/interop/). To use this project, the first step is generating dll file.

### Code example

```C#
using System;
using System.Runtime.InteropServices;

namespace ConsoleApp1 {
    class Program {
        [DllImport("concaveman.dll", EntryPoint = "pyconcaveman2d", CallingConvention = CallingConvention.Cdecl)]
        static extern int pyconcaveman2d(double[] points_c, int num_points, int[] hull_points_c, int num_hull_points, double concavity, double lengthThreshold, double[] concave_points_c);


        static void Main(string[] args) {
            // There are three points: {0, 0}, {1, 0}, {0.25, 0.15}, {1, 1}
            // 共三个点：{0, 0}, {1, 0}, {0.25, 0.15}, {1, 1}
            double[] points = { 0, 0, 1, 0, 0.25, 0.15, 1, 1 };
            // Points 0: {0, 0}, 1: {1, 0}, 3:{1, 1} make the converx hull
            // 构成凸包的点：0: {0, 0}, 1: {1, 0}, 3:{1, 1}
            int[] hull = { 0, 1, 3 };
            // An array holes the concave hull points, and its size should be the same as the points array
            // 存储凹包点坐标的数字，其大小应当与输入的点数组相等
            double[] out_points = new double[8];
            // The real number of points of the concave hull.
            // 构成凹包的点的真实数量
            int out_points_num = pyconcaveman2d(points, 4, hull, 3, 2, 1, out_points);

            // Print the concave hull coordinates
            // 打印凹包坐标
            for (int i = 0; i != out_points_num; ++i) {
                Console.WriteLine($"{i}: x={out_points[i << 1]}, y={out_points[(i << 1) + 1]}");
            }

            Console.ReadKey();
        }
    }
}
```

