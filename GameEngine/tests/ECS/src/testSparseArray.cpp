//
// Created by kane on 14/01/24.
//

#include <gtest/gtest.h>
#include <rtype/Components/TransformComponent.hh>
#include <rtype/SparseArray.hpp>

TEST(SparseArray, add_component)
{
    rtype::SparseArray<rtype::TransformComponent> transforms;

    transforms.insert_at(0, {1, 1, 1, 1, 1, 1});
    transforms.insert_at(100, {1, 1, 1, 1, 1, 1});
    EXPECT_EQ(transforms[0]->position_x, 1);
    EXPECT_EQ(transforms[100]->position_x, 1);
    EXPECT_FALSE(transforms[50].has_value());
}

TEST(SparseArray, size)
{
    rtype::SparseArray<rtype::TransformComponent> transforms;

    transforms.insert_at(100, {1, 1, 1, 1, 1, 1});
    EXPECT_EQ(transforms.size(), 101);
}
