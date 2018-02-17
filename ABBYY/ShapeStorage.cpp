#include "ShapeStorage.h"
#include <cassert>


TShapeStorage& TShapeStorage::operator<<(TShape shape) {
    auto it = m_shapes.find(shape);
    if (it != m_shapes.end())
        throw std::logic_error("ERROR: Found collision of the shape's id.");

    m_shapes.insert(it, std::move(shape));
    m_storage[shape.type][shape.color].insert(shape);

    return *this;
}

bool TShapeStorage::Contain(TShape::Id_t id) const {
    return m_shapes.find(TShape(id)) != m_shapes.end();
}

const TShape & TShapeStorage::Get(TShape::Id_t id) const {
    auto it = m_shapes.find(TShape(id));
    if (it == m_shapes.end())
        throw std::logic_error("ERROR: An attempt to get the missing object.");

    return *it;
}

bool TShapeStorage::Remove(TShape::Id_t id) {
    auto it = m_shapes.find(TShape(id));
    if (it == m_shapes.end())
        return false;

    m_storage[it->type][it->color].erase(*it);
    m_shapes.erase(it);
    return true;
}

size_t TShapeStorage::HowMany() const {
    return m_shapes.size();
}

size_t TShapeStorage::HowMany(TShape::EType type) const {
    auto & colorBucket = m_storage[type];
    size_t size = 0;
    for (auto & shapeSet : colorBucket)
        size += shapeSet.size();
    return size;
}

size_t TShapeStorage::HowMany(TShape::EColor color) const {
    size_t size = 0;
    for(auto & colorBucket : m_storage)
        size += colorBucket[color].size();
    return size;
}

size_t TShapeStorage::HowMany(TShape::EType type, TShape::EColor color) const {
    return m_storage[type][color].size();
}

std::vector<TShape> TShapeStorage::GetAll() const {
    return {m_shapes.begin(), m_shapes.end()};
}

std::vector<TShape> TShapeStorage::GetAll(TShape::EType type) const {
    std::vector<TShape> ret;
    ret.reserve(HowMany(type));
    auto & colorBucket = m_storage[type];
    for (auto & shapeSet : colorBucket)
        std::copy(shapeSet.begin(), shapeSet.end(), std::back_inserter(ret));
    assert(ret.capacity() == ret.size());
    return ret;
}

std::vector<TShape> TShapeStorage::GetAll(TShape::EColor color) const {
    std::vector<TShape> ret;
    ret.reserve(HowMany(color));
    for (auto &colorBucket : m_storage) {
        auto & shapeSet = colorBucket[color];
        std::copy(shapeSet.begin(), shapeSet.end(), std::back_inserter(ret));
    }
    assert(ret.capacity() == ret.size());
    return ret;
}

std::vector<TShape> TShapeStorage::GetAll(TShape::EType type, TShape::EColor color) const {
    auto shapeSet = m_storage[type][color];
    return {shapeSet.begin(), shapeSet.end()};
}
