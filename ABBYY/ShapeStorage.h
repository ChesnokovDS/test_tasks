#pragma once
#include "Shape.h"
#include <vector>
#include <array>
#include <unordered_set>


class TShapeStorage {
    using TShapeSet = std::unordered_set<TShape>;
    using TColorBucket = std::array<TShapeSet, TShape::EColor::UNDEFINED_COLOR + 1>;
    using TTypeBucket = std::array<TColorBucket, TShape::EType::UNDEFINED_TYPE + 1>;

public:
    TShapeStorage() = default;
    TShapeStorage(const TShapeStorage&) = default;
    TShapeStorage& operator=(const TShapeStorage&) = default;
    TShapeStorage(TShapeStorage &&) = default;
    TShapeStorage& operator=(TShapeStorage&&) = default;

    TShapeStorage& operator <<(TShape shape);
    bool Contain(TShape::Id_t) const;
    const TShape & Get(TShape::Id_t) const;
    bool Remove(TShape::Id_t);

    size_t HowMany() const;
    size_t HowMany(TShape::EType) const;
    size_t HowMany(TShape::EColor) const;
    size_t HowMany(TShape::EType, TShape::EColor) const;

    std::vector<TShape> GetAll() const;
    std::vector<TShape> GetAll(TShape::EType) const;
    std::vector<TShape> GetAll(TShape::EColor) const;
    std::vector<TShape> GetAll(TShape::EType, TShape::EColor) const;

private:
    TShapeSet m_shapes;
    TTypeBucket m_storage;
};
