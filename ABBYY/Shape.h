#pragma once
#include <functional>


struct TShape {
    using Id_t = unsigned int;
    enum EType {
        SQUARE = 0,
        RECTANGLE,
        RHOMBUS,
        PARALLELOGRAM,
        UNDEFINED_TYPE // Attention!! This element should be in the end.
    };
    enum EColor {
        RED = 0,
        GREEN,
        BLUE,
        UNDEFINED_COLOR // Attention!! This element should be in the end.
    };

public:
    Id_t id;
    EType type;
    EColor color;

public:
    TShape(Id_t id, EType type = EType::UNDEFINED_TYPE, EColor color = EColor::UNDEFINED_COLOR);
};


namespace std
{
    template<>
    struct hash<TShape>
    {
        size_t operator()(const TShape & obj) const {
            return hash<TShape::Id_t>()(obj.id);
        }
    };

    template<>
    struct equal_to<TShape>
    {
        size_t operator()(const TShape& lhs, const TShape& rhs) const
        {
            return equal_to<TShape::Id_t>()(lhs.id, rhs.id);
        }
    };
}
