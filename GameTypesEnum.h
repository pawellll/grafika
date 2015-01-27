#ifndef GAMETYPESENUM_H
#define GAMETYPESENUM_H

enum GameTypesEnum{
    type1_3t, // type 1, 3x3, t-time
    type1_4t,
    type1_5t,
    type1_6t,
    type2_3t, // type 2, 3x3
    type2_4t,
    type2_5t,
    type2_6t,
    type1_3m, // type 1, 3x3, m-moves
    type1_4m,
    type1_5m,
    type1_6m,
    type2_3m,
    type2_4m,
    type2_5m,
    type2_6m,
    guard // needed for iterating through enum
};

enum SortEnum{
    sortTime,
    sortMoves
};

#endif // GAMETYPESENUM_H
