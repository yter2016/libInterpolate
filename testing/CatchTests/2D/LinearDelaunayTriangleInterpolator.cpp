#include "catch.hpp"

#include <libInterpolate/Interpolators/_2D/LinearDelaunayTriangleInterpolator.hpp>

TEMPLATE_TEST_CASE("2D LinearDelaunayTriangleInterpolator Tests", "[current]",double,float)
{
  _2D::LinearDelaunayTriangleInterpolator<TestType> interp;

  SECTION("Single Triangle")
  {
  std::vector<TestType> x(3), y(3), z(3);

    SECTION("Level")
    {
      // clang-format off
      x[0] = 0; y[0] = 0; z[0] = 1;
      x[1] = 1; y[1] = 0; z[1] = 1;
      x[2] = 0; y[2] = 1; z[2] = 1;
      // clang-format on

      interp.setData(x, y, z);

      CHECK(interp(0, 0) == Approx(1));
      CHECK(interp(0, 1) == Approx(1));
      CHECK(interp(1, 0) == Approx(1));
      CHECK(interp(0.1, 0.1) == Approx(1));

      CHECK(interp(0, -0.1) == Approx(0));
      CHECK(interp(1, 1) == Approx(0));
      CHECK(interp(-0.1, 0) == Approx(0));
    }

    SECTION("Angled")
    {
      // clang-format off
      x[0] = 0; y[0] = 1; z[0] = 0;
      x[1] = 0; y[1] =-1; z[1] = 0;
      x[2] = 1; y[2] = 0; z[2] = 1;
      // clang-format on

      interp.setData(x, y, z);

      CHECK(interp(0, 0) == Approx(0).scale(1));
      CHECK(interp(0.5, 0) == Approx(0.5));
      CHECK(interp(0.5, 0.1) == Approx(0.5));
      CHECK(interp(0.5, 1) == Approx(0));
      CHECK(interp(1, 0) == Approx(1));

    }
  }
  SECTION("Multiple Triangles")
  {
    std::vector<TestType> x(5), y(5), z(5);
    SECTION("Table Top")
    {
      // clang-format off
      x[0] = -1; y[0] = -1; z[0] = 3.14;
      x[1] = -1; y[1] =  1; z[1] = 3.14;
      x[2] =  1; y[2] = -1; z[2] = 3.14;
      x[3] =  1; y[3] =  1; z[3] = 3.14;
      x[4] =  0; y[4] =  0; z[4] = 3.14;
      // clang-format on
      
      interp.setData(x,y,z);


      CHECK( interp(0,0) == Approx(3.14) );
      CHECK( interp(2,0) == Approx(0).scale(1) );
      CHECK( interp(0,2) == Approx(0).scale(1) );
      CHECK( interp(0.5,0.5) == Approx(3.14) );

    }

    SECTION("Pyramid")
    {
      // clang-format off
      x[0] = -1; y[0] = -1; z[0] = 0;
      x[1] = -1; y[1] =  1; z[1] = 0;
      x[2] =  1; y[2] = -1; z[2] = 0;
      x[3] =  1; y[3] =  1; z[3] = 0;
      x[4] =  0; y[4] =  0; z[4] = 2;
      // clang-format on

      interp.setData(x,y,z);

      CHECK( interp(0,0) == Approx(2) );
      CHECK( interp(-1,0) == Approx(0).scale(1) );
      CHECK( interp(0,1) == Approx(0).scale(1) );

      CHECK( interp(0,0.5) == Approx(1) );
      CHECK( interp(0.5,0) == Approx(1) );
      CHECK( interp(0,-0.5) == Approx(1) );
      CHECK( interp(-0.5,0) == Approx(1) );
      CHECK( interp(0.5,0.5) == Approx(1) );

    }
  }
}