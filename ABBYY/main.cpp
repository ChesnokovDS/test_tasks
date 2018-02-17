#include <iostream>
#include "ShapeStorage.h"
#include <cassert>


int main() {
    TShapeStorage storage;
    typedef TShape::EType EType;
    typedef TShape::EColor EColor;
    storage << TShape(0         , EType::PARALLELOGRAM , EColor::RED            )
            << TShape(4000000000, EType::PARALLELOGRAM , EColor::BLUE           )
            << TShape(3         , EType::RHOMBUS       , EColor::GREEN          )
            << TShape(17        , EType::SQUARE        , EColor::GREEN          )
            << TShape(155       , EType::RECTANGLE     , EColor::RED            )
            << TShape(555       , EType::SQUARE        , EColor::GREEN          )
            << TShape(4         , EType::SQUARE        , EColor::UNDEFINED_COLOR)
            << TShape(13        , EType::RHOMBUS       , EColor::BLUE           )
            << TShape(9         , EType::UNDEFINED_TYPE, EColor::GREEN          )
            << TShape(300       , EType::RHOMBUS       , EColor::UNDEFINED_COLOR)
            << TShape(45        , EType::UNDEFINED_TYPE, EColor::GREEN          )
            << TShape(777       , EType::SQUARE        , EColor::BLUE           )
            << TShape(789       , EType::RECTANGLE     , EColor::BLUE           )
            ;

    assert(storage.HowMany() == 13);

    assert(storage.HowMany(EType::SQUARE        ) == 4);
    assert(storage.HowMany(EType::RECTANGLE     ) == 2);
    assert(storage.HowMany(EType::UNDEFINED_TYPE) == 2);
    assert(storage.HowMany(EType::RHOMBUS       ) == 3);
    assert(storage.HowMany(EType::PARALLELOGRAM ) == 2);

    assert(storage.HowMany(EColor::RED            ) == 2);
    assert(storage.HowMany(EColor::BLUE           ) == 4);
    assert(storage.HowMany(EColor::GREEN          ) == 5);
    assert(storage.HowMany(EColor::UNDEFINED_COLOR) == 2);

    assert(storage.HowMany(EType::SQUARE   , EColor::RED  ) == 0);
    assert(storage.HowMany(EType::RHOMBUS  , EColor::GREEN) == 1);
    assert(storage.HowMany(EType::RECTANGLE, EColor::BLUE ) == 1);

    assert(storage.HowMany() == storage.GetAll().size());

    assert(storage.HowMany(EType::SQUARE        ) == storage.GetAll(EType::SQUARE        ).size());
    assert(storage.HowMany(EType::RECTANGLE     ) == storage.GetAll(EType::RECTANGLE     ).size());
    assert(storage.HowMany(EType::UNDEFINED_TYPE) == storage.GetAll(EType::UNDEFINED_TYPE).size());
    assert(storage.HowMany(EType::RHOMBUS       ) == storage.GetAll(EType::RHOMBUS       ).size());
    assert(storage.HowMany(EType::PARALLELOGRAM ) == storage.GetAll(EType::PARALLELOGRAM ).size());

    assert(storage.HowMany(EColor::RED            ) == storage.GetAll(EColor::RED            ).size());
    assert(storage.HowMany(EColor::BLUE           ) == storage.GetAll(EColor::BLUE           ).size());
    assert(storage.HowMany(EColor::GREEN          ) == storage.GetAll(EColor::GREEN          ).size());
    assert(storage.HowMany(EColor::UNDEFINED_COLOR) == storage.GetAll(EColor::UNDEFINED_COLOR).size());

    for (int it = 0; it <= EType::UNDEFINED_TYPE; ++it)
        for (int ic = 0; ic <= EColor::UNDEFINED_COLOR; ++ic) {
            EType  t = static_cast<EType >(it);
            EColor c = static_cast<EColor>(ic);
            assert(storage.HowMany(t, c) == storage.GetAll(t, c).size());
        }

    TShape::Id_t testedId = 111;
    assert(!storage.Contain(testedId));
    assert(!storage.Remove(testedId));
    storage << TShape(testedId);
    assert(storage.Contain(testedId));
    assert(storage.Remove(testedId));
    assert(!storage.Contain(testedId));

    bool collisionAppear = false, gotMissingItem = false;
    try {
        storage << TShape(789);
    }
    catch (std::logic_error) {
        collisionAppear = true;
    }
    assert(collisionAppear);
    try {
        storage.Get(testedId);
    }
    catch (std::logic_error) {
        gotMissingItem = true;
    }
    assert(gotMissingItem);

    std::cout << std::endl << "All tests have been passed, good job!" << std::endl;
    return 0;
}
