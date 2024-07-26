#include "move.h"

Move::Move() {}

Move::Move(int r1, int c1, int r2, int c2) :
	r1(r1), c1(c1), r2(r2), c2(c2), castle(false), promotion(NONE) {}

Move::Move(int r1, int c1, int r2, int c2, bool enPassant) :
	r1(r1), c1(c1), r2(r2), c2(c2), castle(false), enPassant(enPassant), promotion(NONE) {}

Move::Move(int r1, int c1, int r2, int c2, int promotion) :
	r1(r1), c1(c1), r2(r2), c2(c2), castle(false), promotion(promotion) {}

Move::Move(int r1, int c1, int r2, int c2, int r3, int c3, int r4, int c4) :
	r1(r1), c1(c1), r2(r2), c2(c2), r3(r3), c3(c3), r4(r4), c4(c4), castle(true), promotion(NONE) {}

