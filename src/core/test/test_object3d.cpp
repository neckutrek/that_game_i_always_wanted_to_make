#include "gtest/gtest.h"

#include "core/object3d.h"
#include "core/test/object3d_fixture.h"

typedef ::testing::Types<tg::Object3D> object3d_types;
INSTANTIATE_TYPED_TEST_SUITE_P(core__object3d, core__object3d_fixture, object3d_types);
